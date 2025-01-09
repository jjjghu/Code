import cv2
import mediapipe as mp
import pyautogui
import numpy as np
import time
import threading
import tkinter as tk

class GestureDetector:
    def __init__(self, action_cooldown=1, threshold_trigger=0.08, threshold_release=0.2, gesture_timeout=2):
        self.action_cooldown = action_cooldown
        self.threshold_trigger = threshold_trigger
        self.threshold_release = threshold_release
        self.gesture_timeout = gesture_timeout
        self.last_action_time = time.time()
        self.triggered = False
        self.last_seen_time = time.time()
        self.mp_hands = mp.solutions.hands
        self.hands = self.mp_hands.Hands()
        self.mp_draw = mp.solutions.drawing_utils

    def detect_gestures(self, frame, hand_landmarks):
        current_time = time.time()
        gesture_result = None

        # 沒有檢測到手，超時檢查
        if not hand_landmarks:
            if current_time - self.last_seen_time > self.gesture_timeout:
                self.triggered = False  # 重置觸發狀態
            return

        # 更新手最後一次被檢測到的時間
        self.last_seen_time = current_time

        # 指尖座標, 計算距離
        thumb_tip = hand_landmarks.landmark[self.mp_hands.HandLandmark.THUMB_TIP]
        index_finger_tip = hand_landmarks.landmark[self.mp_hands.HandLandmark.INDEX_FINGER_TIP]
        middle_finger_tip = hand_landmarks.landmark[self.mp_hands.HandLandmark.MIDDLE_FINGER_TIP]

        thumb_index_distance = np.sqrt(
            (thumb_tip.x - index_finger_tip.x) ** 2 +
            (thumb_tip.y - index_finger_tip.y) ** 2 +
            (thumb_tip.z - index_finger_tip.z) ** 2
        )

        thumb_middle_distance = np.sqrt(
            (thumb_tip.x - middle_finger_tip.x) ** 2 +
            (thumb_tip.y - middle_finger_tip.y) ** 2 +
            (thumb_tip.z - middle_finger_tip.z) ** 2
        )

        # 判斷手勢觸發條件
        if not self.triggered and thumb_index_distance < self.threshold_trigger :  # 距離小於觸發閾值
            if current_time - self.last_action_time > self.action_cooldown:
                gesture_result = 0
                self.triggered = True
                self.last_action_time = current_time
                
        if not self.triggered and thumb_middle_distance < self.threshold_trigger:
            if current_time - self.last_action_time > self.action_cooldown:
                gesture_result = 1
                self.triggered = True  # 標記為已觸發
                self.last_action_time = current_time
                        
        if self.triggered and thumb_index_distance > self.threshold_release and thumb_middle_distance > self.threshold_release:  # 距離大於釋放閾值
            self.triggered = False

        # 顯示距離與觸發狀態
        cv2.putText(frame, f'Distance: {thumb_index_distance:.2f} Triggered: {self.triggered}', (30, 110),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2, cv2.LINE_AA)
        return gesture_result

class EyeBlinkDetector:
    def __init__(self):
        # MediaPipe Face Mesh 初始化
        self.mp_face_mesh = mp.solutions.face_mesh
        self.mp_drawing = mp.solutions.drawing_utils
        self.face_mesh = self.mp_face_mesh.FaceMesh(
            max_num_faces=1,
            refine_landmarks=True,
            min_detection_confidence=0.5,
            min_tracking_confidence=0.5
        )
        # 預設的眼睛比例值
        self.original_eye = 0.48
        # 偵測眨眼時的比例值
        self.rate = 0.45
        # 變數來儲存是否偵測到眨眼
        self.is_blink = False
        self.lock = threading.Lock() # 其實只有一個變數不用到lock，但都用thread的了 再用lock感覺更專業 也向蕭老師致敬
        self.elapsed_time = None  # 用來儲存眨眼長度
    def reset_eye(self, frame):
        # 轉換 BGR 到 RGB
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        # 處理影像
        results = self.face_mesh.process(rgb_frame)
        if results.multi_face_landmarks:
            for face_landmarks in results.multi_face_landmarks:
                # 左眼和右眼的索引 (mediapipe有把人臉上的關鍵點做統一的編號)
                left_eye_indices = [33, 160, 158, 133, 153, 144]
                right_eye_indices = [362, 385, 387, 263, 373, 380]
                
                landmarks = face_landmarks.landmark
                # 計算左右眼的 EAR（眼睛外觀比例）
                left_eye = self.calculate_eye(landmarks, left_eye_indices)
                right_eye = self.calculate_eye(landmarks, right_eye_indices)
                
                # 平均 eye 左右眼平均，避免大小眼
                eye = (left_eye + right_eye) / 2
                self.original_eye = eye
                print("left_eye" + str(left_eye) + ", right_eye" + str(right_eye))
            return True
        else:
            return False
    def calculate_eye(self, landmarks, eye_indices):
        vertical1 = np.array([landmarks[eye_indices[1]].x, landmarks[eye_indices[1]].y])
        vertical2 = np.array([landmarks[eye_indices[5]].x, landmarks[eye_indices[5]].y])

        horizontal1 = np.array([landmarks[eye_indices[0]].x, landmarks[eye_indices[0]].y])
        horizontal2 = np.array([landmarks[eye_indices[4]].x, landmarks[eye_indices[4]].y])

        ear = np.linalg.norm(vertical1 - vertical2) / np.linalg.norm(horizontal1 - horizontal2)
        return ear # 簡單來說，就是眼睛垂直長度除以水平長度，如果有人眼睛本來就很小是不是就不能用了XDDD

    def detect_blink(self, frame):
        # 轉換 BGR 到 RGB
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        
        # 處理影像
        results = self.face_mesh.process(rgb_frame)
        
        # 預設未偵測到眨眼
        blink_detected = False
        
        if results.multi_face_landmarks:
            for face_landmarks in results.multi_face_landmarks:
                # 左眼和右眼的索引 (mediapipe有把人臉上的關鍵點做統一的編號)
                left_eye_indices = [33, 160, 158, 133, 153, 144]
                right_eye_indices = [362, 385, 387, 263, 373, 380]
                
                landmarks = face_landmarks.landmark
                # 計算左右眼的 EAR（眼睛外觀比例）
                left_eye = self.calculate_eye(landmarks, left_eye_indices)
                right_eye = self.calculate_eye(landmarks, right_eye_indices)
                # print("left_eye" + str(left_eye) + ", right_eye" + str(right_eye))
                # 平均 eye 左右眼平均，避免大小眼
                eye = (left_eye + right_eye) / 2
                print("self.original_eye" + str(self.original_eye) + ", self.rate" + str(self.rate))
                # 眨眼閾值 越低代表眼睛要越扁才會被認定是閉起來的
                if eye/self.original_eye < self.rate:
                    blink_detected = True
        
        # 更新 is_blink 的值
        with self.lock:
            self.is_blink = blink_detected
        return blink_detected

    def detect_edge(self):
        # 初始狀態
        last_state = False
        start_time = None
        
        while True:
            with self.lock:
                current_state = self.is_blink
            
            # 偵測到 rising edge (由低到高)-代表開始眨眼
            if current_state and not last_state:
                # 開始計時
                start_time = time.time()
                # print("偵測到 rising edge，開始計時...")
            
            # 偵測到 falling edge (由高到低) - 代表睜開眼睛
            if not current_state and last_state:
                if start_time is not None:
                    # 結束計時並回傳時間
                    end_time = time.time()
                    elapsed_time = end_time - start_time
                        
                    # 更新共享的 elapsed_time 變數
                    with self.lock:
                        self.elapsed_time = elapsed_time
                    
                    start_time = None
            
            # 更新最後狀態
            last_state = current_state

            # 模擬 10 毫秒的輪詢間隔，如果沒有的話，辨識時會有些遲緩，我猜是平行運算的時候，如果都高頻率運作會彼此影響效率
            # 所以讓這個thread的頻率不要這麼高，把剩下的運算資源留給main()，當然不曉得會不會是我電腦本身的效能問題
            time.sleep(0.01)

    def get_elapsed_time(self):
        # 返回共享的 elapsed_time 變數，並重設為0避免重複讀取造成重複指令(因為程式是不間段的在請求秒數)
        with self.lock:
            re = self.elapsed_time
            self.elapsed_time = 0
            return re
    def update_rate(self, val):
        self.rate = val / 100.0  # Slider range 0 to 100 mapped to 0.1 to 0.9

class KeyAction:
    def __init__(self):
        self.end_annotation = "end"
        # 0, 1, 2, 3
        # 0: 食指
        # 1: 中指
        # 3: 短閉眼
        # 4: 長閉眼
        self.trie = self.make_trie('0', '1', '00', '11')
        self.mapping = {
            "0": "space", 
            "1": "F", 
            "00": "shift+n", 
            "11": "alt+tab+tab"
        }
    # 建立字典樹
    def make_trie(self, *numbers):
        root = dict()
        for number in numbers:
            current_dict = root
            for i in number:
                current_dict = current_dict.setdefault(i, {})
            current_dict[self.end_annotation] = self.end_annotation
        return root
    
    # 查找字典樹
    def in_trie(self, order):
        current_trie = self.trie
        for i in order:
            if str(i) not in current_trie:
                return False
            current_trie = current_trie[str(i)]
        return self.end_annotation in current_trie
    
    # 拆分組合按鍵
    def perform_action(self, order):
        key = "".join(map(str, order))
        if key in self.mapping:
            action = self.mapping[key]
            if '+' in action:
                keys = action.split('+')
                pyautogui.hotkey(*keys)
            else:
                pyautogui.press(action)
            print(f"Action: Press '{action}', Sequence: '{order}'")
        else:
            print(f"No action mapped for the sequence '{order}' .")

    def execute(self, order):
        ans = "".join(map(str, order))
        if self.in_trie(order):
            self.perform_action(order)
            return True
        else:
            print(f"The sequence '{ans}' is not found in the trie.")
            return False

def main():
    # 開啟攝影機
    cap = cv2.VideoCapture(0)
    blink_detector = EyeBlinkDetector()
    gesture_detector = GestureDetector()
    order_executor = KeyAction()
    
    # 初始化 MediaPipe Hands
    mp_hands = mp.solutions.hands
    hands = mp_hands.Hands()
    mp_draw = mp.solutions.drawing_utils
    
    # 重設眼睛大小比例
    def reset_eye():
        ret, frame = cap.read()
        frame = cv2.flip(frame, 1)
        blink_detector.reset_eye(frame)
    reset_eye()
    # 啟動偵測邊緣的線程 daemon代表當主程式強制結束時，此線程也會一併被強制結束
    edge_thread = threading.Thread(target=blink_detector.detect_edge, daemon=True)
    edge_thread.start()
    
    # Create a window and slider to adjust the `rate`
    cv2.namedWindow("Settings", cv2.WINDOW_NORMAL | cv2.WINDOW_FREERATIO)
    cv2.resizeWindow("Settings", (300, 50))
    # make window adjustable 

    cv2.createTrackbar("Threshold", "Settings", int(blink_detector.rate * 100), 100, 
                       lambda val: blink_detector.update_rate(val))
    # cv2.createButton("Reset Eye", reset_eye, None, cv2.QT_PUSH_BUTTON, 0)
    # 指令順序和編碼
    order = []
    order_mapping = {0: "index", 1: "middle", 2: "Short", 3: "Long"}
    showed_time = 0 
    while True:
        ret, frame = cap.read()
        if not ret:
            break
        
        frame = cv2.flip(frame, 1)
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        
        # 手勢檢測
        results = hands.process(frame_rgb)
            
        # 偵測眨眼
        blink_detector.detect_blink(frame)
        
        # 讀取從 edge 偵測執行緒傳回的經過時間
        elapsed_time = blink_detector.get_elapsed_time()
        
        # 顯示經過的時間（如果有）
        if elapsed_time is not None and elapsed_time > 0.3:
            #超過0.3秒才更新顯示時間
            showed_time = elapsed_time
            if 0.3 < elapsed_time < 1.5: # short
                # 短閉眼執行指令
                order_executor.execute(order)
            if elapsed_time > 1.5: # long
                # 長閉眼 reset 指令
                 order = []
                
        # 只偵測第一隻手
        if results.multi_hand_landmarks:
            # 取得第一隻手的關鍵點
            first_hand_landmarks = results.multi_hand_landmarks[0]  
            # 劃出骨架
            mp_draw.draw_landmarks(frame, first_hand_landmarks, mp_hands.HAND_CONNECTIONS)
            # 偵測然後執行動作
            command = gesture_detector.detect_gestures(frame, first_hand_landmarks)
            if command == 0: 
                # 拇指中指相碰
                order.append(0) 
            elif command == 1:
                # 拇指中指相碰 
                order.append(1)
        
        # 顯示畫面
        cv2.putText(frame, f"0.3~1.5:Short, >1.5:Long", (10, 30), 
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2)
        cv2.putText(frame, f"Time: {showed_time:.2f}sec", (10, 60), 
                        cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2)
        order_string = ""
        for s in order:
            order_string = order_string + order_mapping[s] + ","
        cv2.putText(frame, order_string, (10, 110), 
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2)  
        cv2.namedWindow('Eye Blink Detection', cv2.WND_PROP_TOPMOST | cv2.WINDOW_NORMAL | cv2.WND_PROP_ASPECT_RATIO)  
        cv2.setWindowProperty('Eye Blink Detection', cv2.WND_PROP_TOPMOST, 1)
        cv2.imshow('Eye Blink Detection', frame)
        
        # 按 'q' 結束
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        # 按Esc退出
        if cv2.waitKey(5) & 0xFF == 27:  
            break
    # 釋放資源
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
