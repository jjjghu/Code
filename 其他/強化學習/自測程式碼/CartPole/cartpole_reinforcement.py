import gymnasium as gym
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.distributions import Categorical 
import numpy as np
from tqdm import tqdm
import matplotlib.pyplot as plt  # 新增：用於繪圖

class Policy(nn.Module):
    """ MLP 結構，輸入四維狀態，輸出兩維動作機率，就是指 pi(a|s, theta) """
    def __init__(self):
        super(Policy, self).__init__()
        self.fc1 = nn.Linear(4, 128)
        self.fc2 = nn.Linear(128, 128)
        self.fc3 = nn.Linear(128, 2)

    def forward(self, x):
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        return F.log_softmax(self.fc3(x), dim=-1) # dim 表示在最後一個維度上做 softmax

class REINFORCE:
    def __init__(self):
        # 超參數
        self.lr = 1e-3 # 學習率
        self.gamma = 0.99 # 折扣因子
        self.episodes = 500 # 訓練回合數（遊玩幾局）
        self.max_step = 500 # 每一局最大步數
        self.entropy_coef = 0.01 # 熵正則化係數，鼓勵探索
        self.FLOAT32_MIN = np.finfo(np.float32).eps.item() # float32 的最小正數，防止除以 0 或標準差 = 0的情況
        
        self.policy = Policy()
        
        # 優化器，用來更新 MLP 參數
        self.optimizer = optim.Adam(self.policy.parameters(), lr = self.lr) 
        
        # 建立 CartPole 環境
        self.env = gym.make('CartPole-v1')
        
        # 紀錄獎勵歷史
        self.reward_history = []
        self.best_avg_reward = -float('inf')
        
    def train(self):
        print("開始訓練 REINFORCE...")
        pbar = tqdm(range(self.episodes), desc="Training")
        """ 實際走過，紀錄狀態跟獎勵 """
        for episode in pbar:
        # for _ in range(self.episodes):
            # 紀錄初始狀態（env.reset 會回傳觀察空間的初始狀態）
            state = self.env.reset()[0]
            rewards, log_probs, entropies = [], [], [] # 紀錄每一步、選擇該動作的機率、熵
            for _ in range(self.max_step + 1):
                # 需要先將狀態轉換為 Tensor，才能輸入到 MLP 中
                state_tensor = torch.from_numpy(state)
                
                m = Categorical(logits=self.policy.forward(state_tensor)) # 將狀態輸入，取得最後一層的機率分布
                action = m.sample() # 根據機率分佈選擇動作
                log_probs.append(m.log_prob(action)) # 紀錄選擇該動作的 log 機率，對應到公式的 log π_theta(a|s)
                entropies.append(m.entropy()) # 紀錄熵
                
                # https://gymnasium.farama.org/api/env/，紀錄有關 env.step 的回傳值
                next_state, reward, terminated, truncated, _ = self.env.step(action.item())
                rewards.append(reward)
                state = next_state
                
                if terminated or truncated:  # 遇到邊界條件
                    break

            
            # 紀錄這一局的總獎勵到歷史清單中
            self.reward_history.append(sum(rewards))
            
            #  --- 計算 G_t ---
            G = []
            curG = 0
            for r in rewards[::-1]: # 從最後一個獎勵往前計算
                curG = r + self.gamma * curG
                G.append(curG)
            G = G[::-1] # 反轉回正確順序
            G = torch.Tensor(G) # 轉為 Tensor
            G = (G - G.mean()) / (G.std() + self.FLOAT32_MIN) # 標準化，讓訓練更穩定
            
            # --- 計算 loss ---
            loss = 0
            for log_prob, Gt, entropy in zip(log_probs, G, entropies):
                # 當混亂程度提高（比如 0.5, 0.5 相比 1, 1 來說比較混亂），熵會更大，算出來的 loss 就更小
                # 能避免模型過於固執，往錯誤的深淵前進。
                loss += -log_prob * Gt - self.entropy_coef * entropy
                
            self.optimizer.zero_grad()
            loss.backward() # 因為上面 parameters() 已經指定了要更新的參數 ，這裡會自動計算 loss 對 theta 的梯度
            self.optimizer.step() # 更新 Policy 權重
            
            # --- cmd 輸出與存檔 --- 
            avg_reward = np.mean(self.reward_history[-50:])
            pbar.set_postfix({"Avg 50 Reward": avg_reward, "Loss": f"{loss.item():.2f}"})
            if avg_reward > self.best_avg_reward:
                self.best_avg_reward = avg_reward
                torch.save(self.policy.state_dict(), 'reinforce_cartpole.pth')
            
        print(f"訓練完成！歷史最高平均分: {self.best_avg_reward}")
        self.plot_rewards() # 訓練結束後畫圖

    def plot_rewards(self):
        """ 繪製訓練曲線 """
        plt.figure(figsize=(10, 5))
        plt.plot(self.reward_history, label="Episode Reward", color='lightblue', alpha=0.6)
        
        # 計算移動平均線 (Moving Average) 讓趨勢更明顯
        if len(self.reward_history) >= 10:
            moving_avg = np.convolve(self.reward_history, np.ones(50)/50, mode='valid')
            plt.plot(range(49, len(self.reward_history)), moving_avg, label="Moving Average (50)", color='red')
            
        plt.title("REINFORCE Training Curve on CartPole-v1")
        plt.xlabel("Episode")
        plt.ylabel("Total Reward")
        plt.legend()
        plt.grid(True, linestyle='--', alpha=0.5)
        plt.show()

    def test(self):
        """ 測試訓練好的模型，看看它在環境中的表現 """
        print("開始測試訓練好的模型...")
        self.policy.load_state_dict(torch.load('reinforce_cartpole.pth')) # 加載訓練好的模型權重
        self.policy.eval() # 設置為評估模式，關閉 dropout 等訓練專用功能
        
        testEnv = gym.make('CartPole-v1', render_mode='human') # 創建一個新的環境，並啟用渲染模式
        state = testEnv.reset()[0]
        total_reward = 0
        
        # for _ in range(self.MXStep + 1):
        while True:
            state_tensor = torch.from_numpy(state)
            with torch.no_grad(): # 測試時不需要計算梯度
                action_probs = self.policy.forward(state_tensor).exp()
            action = torch.argmax(action_probs).item() # 選擇機率最高的動作
            
            next_state, reward, terminated, truncated, _ = testEnv.step(action)
            total_reward += reward
            state = next_state
            
            if terminated:
                print("倒了或是衝出邊界了！")
            if truncated:
                print("恭喜！撐滿 500 步，遊戲時間截止。")
            if terminated or truncated:
                break
        
        print(f"測試完成！總獎勵: {total_reward}")
        
if __name__ == "__main__":
    reinforce = REINFORCE()
    reinforce.train()
    reinforce.test()