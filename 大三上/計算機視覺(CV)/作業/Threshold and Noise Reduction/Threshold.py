import cv2
import numpy as np
    
def mean_threshold(image, window_size, c):
    # 填充邊緣
    pad = window_size // 2
    padded_image = np.pad(image, pad, mode='reflect')
    threshold_image = np.zeros_like(image)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            # 遍歷所有像素點
            window = padded_image[i:i+window_size, j:j+window_size]
            # 計算平均, 將現在的點分為白或黑 (平均 - 常數)
            local_mean = np.mean(window)
            if image[i, j] > local_mean - c:
                threshold_image[i, j] = 255
            else:
                threshold_image[i, j] = 0
    return threshold_image

def niblack_threshold(image, window_size, k=-0.2):
    pad = window_size // 2
    padded_image = np.pad(image, pad, mode='reflect')
    threshold_image = np.zeros_like(image)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            window = padded_image[i:i+window_size, j:j+window_size]
            # 跟 mean 不同的地方
            local_mean = np.mean(window)
            local_std = np.std(window)
            threshold = local_mean + k * local_std
            
            if image[i, j] > threshold:
                threshold_image[i, j] = 255
            else:
                threshold_image[i, j] = 0
    return threshold_image

def sauvola_threshold(image, window_size, k=0.2, R=128):
    pad = window_size // 2
    padded_image = np.pad(image, pad, mode='reflect')
    threshold_image = np.zeros_like(image)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            window = padded_image[i:i+window_size, j:j+window_size]
            # 稍微不一樣的計算方式
            local_mean = np.mean(window)
            local_std = np.std(window)
            threshold = local_mean * (1 + k * (local_std / R - 1))
            
            if image[i, j] > threshold:
                threshold_image[i, j] = 255
            else:
                threshold_image[i, j] = 0
    return threshold_image

def otsu_threshold(image):    
    # 把圖案攤平, 計算 0 ~ 255 數字出現的次數, 紀錄為 histogram
    histogram = np.bincount(image.ravel(), minlength=256)
    pixel_count = image.size
    pixel_sum = np.sum(np.arange(256) * histogram)
    
    max_variance = 0
    best_threshold = 0
    sum_background = weight_background = 0
    
    # 試過所有的 threshold
    for threshold in range(256):
        # threshold 前面的所有像素點個數
        weight_background += histogram[threshold]
        if weight_background == 0:
            continue
        weight_foreground = pixel_count - weight_background
        if weight_foreground == 0:
            break
        # 背景的總和
        sum_background += threshold * histogram[threshold]
        mean_background = sum_background / weight_background
        mean_foreground = (pixel_sum - sum_background) / weight_foreground
        # 變異數
        variance = weight_background * weight_foreground * (mean_background - mean_foreground) ** 2
        # 找到更好的
        if variance > max_variance:
            max_variance = variance
            best_threshold = threshold
    # 圖片套用 threshold, 灰階
    return (image > best_threshold).astype(np.uint8) * 255

def variance_threshold(image):
    histogram = np.bincount(image.ravel(), minlength=256)
    pixel_count = image.size
    
    max_variance = 0
    best_threshold = 0
    
    for t in range(256):
        P1 = np.sum(histogram[:t]) / pixel_count
        P2 = 1 - P1
        
        if P1 == 0 or P2 == 0:
            continue
        m1 = np.sum(np.arange(t) * histogram[:t]) / (P1 * pixel_count) if P1 > 0 else 0
        m2 = np.sum(np.arange(t, 256) * histogram[t:]) / (P2 * pixel_count) if P2 > 0 else 0
        
        between_class_variance = P1 * P2 * (m1 - m2) ** 2
        
        if between_class_variance > max_variance:
            max_variance = between_class_variance
            best_threshold = t
    return (image > best_threshold).astype(np.uint8) * 255

def entropy_threshold(image):
    histogram = np.bincount(image.ravel(), minlength=256)
    pixel_count = image.size
    prob = histogram / pixel_count
    
    max_entropy = 0
    best_threshold = 0
    
    for t in range(256):
        P1 = np.sum(prob[:t + 1])
        P2 = np.sum(prob[t + 1:])
        if P1 > 0:
            H1 = -np.sum(prob[:t + 1] / P1 * np.log(prob[:t + 1] / P1 + 1e-10))  # 避免log為零
        else:
            H1 = 0
        if P2 > 0:
            H2 = -np.sum(prob[t + 1:] / P2 * np.log(prob[t + 1:] / P2 + 1e-10))  # 避免log為零
        else:
            H2 = 0
        total_entropy = H1 + H2
        if total_entropy > max_entropy:
            max_entropy = total_entropy
            best_threshold = t
    return (image > best_threshold).astype(np.uint8) * 255

image = cv2.imread('lena.bmp', cv2.IMREAD_GRAYSCALE)

window_size = 15
c = 2
mean_threshold_image = mean_threshold(image, window_size, c)
niblack_threshold_image = niblack_threshold(image, window_size)
sauvola_threshold_image = sauvola_threshold(image, window_size)
otsu_threshold_image = otsu_threshold(image)
entropy_threshold_image = entropy_threshold(image)

cv2.namedWindow('Original Image', cv2.WINDOW_NORMAL)
cv2.imshow('Original Image', image)

cv2.namedWindow('Mean Threshold Image', cv2.WINDOW_NORMAL)
cv2.imshow('Mean Threshold Image', mean_threshold_image)

cv2.namedWindow('Niblack Threshold Image', cv2.WINDOW_NORMAL)
cv2.imshow('Niblack Threshold Image', niblack_threshold_image)

cv2.namedWindow('Sauvola Threshold Image', cv2.WINDOW_NORMAL)
cv2.imshow('Sauvola Threshold Image', sauvola_threshold_image)

cv2.namedWindow('Otsu Threshold Image', cv2.WINDOW_NORMAL)
cv2.imshow('Otsu Threshold Image', otsu_threshold_image)


cv2.namedWindow('Entropy Threshold Image', cv2.WINDOW_NORMAL)
cv2.imshow('Entropy Threshold Image', entropy_threshold_image)

# cv2.imwrite("Mean Threshold Image.png", mean_threshold_image)
# cv2.imwrite("Niblack Threshold Image.png", niblack_threshold_image)
# cv2.imwrite("Sauvola Threshold Image.png", sauvola_threshold_image)
# cv2.imwrite("Otsu Threshold Image.png", otsu_threshold_image)
# cv2.imwrite("Entropy Threshold Image.png", entropy_threshold_image)

cv2.waitKey(0)
cv2.destroyAllWindows()