import socket
import threading
import pickle
import time
import json

class NetworkMessage:
    """傳遞的網路訊息"""
    GAME_STATE = "game_state"   # 遊戲狀態
    CELL_REVEAL = "cell_reveal"  # 開圖
    CELL_FLAG = "cell_flag"    # 標旗子
    MINE_HIT = "mine_hit"      # 玩家踩到地雷
    PLAYER_READY = "player_ready"  # 玩家準備完畢
    GAME_START = "game_start"  # 遊戲開始
    GAME_OVER = "game_over"    # 遊戲結束
    GAME_WIN = "game_win"      # 玩家獲勝

class NetworkManager:
    """處理玩家之間的網路通訊"""
    def __init__(self, is_host=False, host_ip="localhost", port=5555):
        self.is_host = is_host
        self.host_ip = host_ip
        self.port = port
        self.socket = None
        self.connection = None
        self.connected = False
        self.callback = None
        self.running = False
        self.thread = None
    
    def set_callback(self, callback):
        """收到訊息過後的回調函數"""
        self.callback = callback
    
    def start_server(self):
        """創建一個 server, 開遊戲房間"""
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.bind((self.host_ip, self.port))
            self.socket.listen(1)
            print(f"目前Server: {self.host_ip}:{self.port}")
            print("等待對手連接...")
            
            # 接受連接, 用一個 thread 去跑
            def accept_connection():
                self.connection, addr = self.socket.accept()
                print(f"連接到: {addr}")
                self.connected = True
                self.start_receiving()
                
            threading.Thread(target=accept_connection, daemon=True).start()
            return True
        except Exception as e:
            print(f"連接到伺服器時發生錯誤: {e}")
            return False
    
    def connect_to_server(self):
        """連接到 server"""
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.host_ip, self.port))
            self.connection = self.socket
            self.connected = True
            print(f"連接到位於: {self.host_ip}:{self.port} 的伺服器")
            self.start_receiving()
            return True
        except Exception as e:
            print(f"連接到伺服器時發生錯誤: {e}")
            return False
    
    def start_receiving(self):
        """用一個獨立的 thread 接收資料"""
        self.running = True
        self.thread = threading.Thread(target=self._receive_loop, daemon=True)
        self.thread.start()
    
    def _receive_loop(self):
        """不斷的接收資料"""
        while self.running and self.connected:
            try:
                # 先接收訊息長度 (4 byte)
                msg_len_bytes = self.connection.recv(4)
                if not msg_len_bytes:
                    self.connected = False
                    break
                
                msg_len = int.from_bytes(msg_len_bytes, byteorder='big')
                
                # 再接收實際資料
                chunks = []
                bytes_received = 0
                while bytes_received < msg_len:
                    chunk = self.connection.recv(min(4096, msg_len - bytes_received))
                    if not chunk:
                        self.connected = False
                        break
                    chunks.append(chunk)
                    bytes_received += len(chunk)
                
                if not self.connected:
                    break
                    
                data = b''.join(chunks)
                message = pickle.loads(data)
                
                # 在主要的 thread 處理資料
                if self.callback:
                    self.callback(message)
            except Exception as e:
                print(f"接收訊息時發生錯誤: {e}")
                self.connected = False
                break
        
        print("關閉連接")
    
    def send_message(self, message_type, data):
        """將訊息發送給另一個玩家"""
        if not self.connected:
            return False
        
        try:
            message = {
                "type": message_type,
                "data": data,
                "timestamp": time.time()
            }
            
            # 序列化資料
            serialized = pickle.dumps(message)
            
            # 先傳訊息的長度
            msg_len = len(serialized)
            self.connection.sendall(msg_len.to_bytes(4, byteorder='big'))
            
            # 再傳實際的訊息
            self.connection.sendall(serialized)
            return True
        except Exception as e:
            print(f"傳送訊息時發生錯誤: {e}")
            self.connected = False
            return False
    
    def close(self):
        """連線關閉"""
        self.running = False
        if self.socket:
            try:
                self.socket.close()
            except:
                pass
        if self.connection and self.connection != self.socket:
            try:
                self.connection.close()
            except:
                pass
        self.connected = False
