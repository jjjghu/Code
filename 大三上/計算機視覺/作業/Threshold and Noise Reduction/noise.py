import cv2
import numpy as np

def bgr_to_hsv(image): 
    # 將 RGB 值轉換到 [0, 1]
    image = image.astype('float32') / 255.0
    B, G, R = image[..., 0], image[..., 1], image[..., 2]
    
    # V (Value)
    Cmax = np.max(image, axis=-1)
    
    # C (Chroma)``
    C = Cmax - np.min(image, axis=-1)
    
    # S (Saturation)
    S = np.where(Cmax == 0, 0, C / Cmax)
    
    # H (Hue)
    H = np.zeros_like(Cmax)
    
    # 只有當 S > 0 時才計算 H
    mask_r = (Cmax == R) & (S > 0)
    mask_g = (Cmax == G) & (S > 0)
    mask_b = (Cmax == B) & (S > 0)
    
    H[mask_r] = 60 * ((G[mask_r] - B[mask_r]) / C[mask_r])
    H[mask_g] = 60 * ((B[mask_g] - R[mask_g]) / C[mask_g]) + 120
    H[mask_b] = 60 * ((R[mask_b] - G[mask_b]) / C[mask_b]) + 240
    
    # 當 S = 0 時，H 也應該設為 0
    H[S == 0] = 0
    
    # 將 H 限制在 [0, 360] 範圍內
    H = np.mod(H, 360)
    
    # 將 H 的範圍轉換到 [0 ~ 179] (符合 OpenCV 標準)
    H = (H / 360.0) * 179
    
    # 將 S 和 V 的範圍轉換到 [0 ~ 255]
    S = S * 255
    V = Cmax * 255
    
    # 將結果合併並轉換為 uint8 類型
    hsv_image = np.stack((H, S, V), axis=-1)
    return hsv_image.astype(np.uint8)

def hsv_to_bgr(hsv_image):
    # OpenCV HSV 值範圍: H: 0-180, S: 0-255, V: 0-255
    # 確保輸入正確
    hsv_image = np.array(hsv_image).astype(np.float32)
    
    # 提取 H, S, V 通道並轉換到標準範圍
    h = hsv_image[:,:,0] * 2.0  # 0-180 -> 0-360
    s = hsv_image[:,:,1] / 255.0  # 0-255 -> 0-1
    v = hsv_image[:,:,2] / 255.0  # 0-255 -> 0-1
    
    # 將 H 轉換到 0-6 範圍
    h_div = h / 60.0
    
    # 計算中間值
    c = v * s
    x = c * (1 - abs(h_div % 2 - 1))
    m = v - c
    
    # 初始化 RGB 矩陣
    rgb = np.zeros_like(hsv_image)
    
    # 根據 H 值的範圍決定 RGB 值
    mask = (0 <= h_div) & (h_div < 1)
    rgb[mask] = np.array([c[mask], x[mask], np.zeros_like(c[mask])]).T
    
    mask = (1 <= h_div) & (h_div < 2)
    rgb[mask] = np.array([x[mask], c[mask], np.zeros_like(c[mask])]).T
    
    mask = (2 <= h_div) & (h_div < 3)
    rgb[mask] = np.array([np.zeros_like(c[mask]), c[mask], x[mask]]).T
    
    mask = (3 <= h_div) & (h_div < 4)
    rgb[mask] = np.array([np.zeros_like(c[mask]), x[mask], c[mask]]).T
    
    mask = (4 <= h_div) & (h_div < 5)
    rgb[mask] = np.array([x[mask], np.zeros_like(c[mask]), c[mask]]).T
    
    mask = (5 <= h_div) & (h_div < 6)
    rgb[mask] = np.array([c[mask], np.zeros_like(c[mask]), x[mask]]).T
    
    # 加入 m 值
    rgb += m[:,:,np.newaxis]
    
    # 將值範圍轉換到 0-255
    rgb = np.clip(rgb * 255, 0, 255)
    
    # 將 RGB 轉換為 BGR（交換第一個和第三個通道）
    bgr = np.zeros_like(rgb)
    bgr[:,:,0] = rgb[:,:,2]  # B = R
    bgr[:,:,1] = rgb[:,:,1]  # G = G
    bgr[:,:,2] = rgb[:,:,0]  # R = B
    
    # 轉換為整數型態
    bgr = bgr.astype(np.uint8)
    
    return bgr

def gaussian_kernel(size, sigma):
    k = size // 2
    x = np.linspace(-k, k, size)
    gauss_kernel = np.exp(-(x**2) / (2 * sigma**2))
    gauss_kernel /= gauss_kernel.sum()  # normalized
    return gauss_kernel

def apply_kernel(image, kernel):
    kernel_size = kernel.shape[0]
    pad_size = kernel_size // 2
    # 不能連 channel 都一起填充
    # padded_image = np.pad(image, pad_size, mode='reflect')
    padded_image = np.pad(image, ((pad_size, pad_size), (pad_size, pad_size), (0, 0)), mode='reflect')
    blurred_image = np.zeros_like(image)

    # image.shape = 長, 寬, channel
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            # 取出當前區域
            region = padded_image[i:i + kernel_size, j:j + kernel_size]
            # 針對每一個 channe 套用 kernel 
            for c in range(image.shape[2]): 
                blurred_image[i, j, c] = np.sum(region[..., c] * kernel)

    return blurred_image

def gaussian_blur(image, kernel_size=5, sigma=1.0):
    # kernel 是奇數
    if kernel_size % 2 == 0:
        kernel_size += 1
    # 產生 kernel 
    kernel = gaussian_kernel(kernel_size, sigma)
    # 2D 版本
    kernel = np.outer(kernel, kernel)
    # 套用
    blurred_image = apply_kernel(image, kernel)
    return blurred_image

def vector_median_filter(image, kernel_size):
    if kernel_size % 2 == 0:
        raise ValueError("Kernel size must be odd.")
    # 長寬
    H, W, C = image.shape
    pad_size = kernel_size // 2
    
    # 擴大圖片, 避免邊界出事
    padded_image = np.pad(image, ((pad_size, pad_size), (pad_size, pad_size), (0, 0)), mode='reflect')
    
    # init
    filtered_image = np.zeros_like(image)

    # 每個 pixel 都用一遍
    for i in range(H):
        for j in range(W):
            neighborhood = padded_image[i:i + kernel_size, j:j + kernel_size]
            neighborhood_vectors = neighborhood.reshape(-1, C)
            # 中間
            filtered_image[i, j] = np.median(neighborhood_vectors, axis=0)

    return filtered_image

image = cv2.imread('noise.bmp', cv2.IMREAD_COLOR)

# 用這個方法會出錯, 就算全部都用 opencv 出來的圖片也長這樣
# hsv_image = bgr_to_hsv(image);
# gaussian_image = gaussian_blur(hsv_image)
# result = hsv_to_bgr(gaussian_image)

result = gaussian_blur(image)
vector_image = vector_median_filter(image, 5)

cv2.namedWindow('Original Image', cv2.WINDOW_NORMAL)
cv2.imshow('Original Image', image)

cv2.namedWindow('Gaussian Image', cv2.WINDOW_NORMAL)
cv2.imshow('Gaussian Image', result)

cv2.namedWindow('vector_median Image', cv2.WINDOW_NORMAL)
cv2.imshow('vector_median Image', vector_image);

cv2.imwrite("Gaussian Image.png", result);
cv2.imwrite("vector_median Image.png", vector_image);

cv2.waitKey(0)
cv2.destroyAllWindows()