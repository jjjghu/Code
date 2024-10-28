import cv2
import matplotlib.pyplot as plt
import numpy as np
def dilation(image, kSize = 5):
    norm_Image = image / 255.0
    pad = kSize // 2
    padded_image = np.pad(norm_Image, pad, mode="reflect")
    result_image = np.zeros_like(norm_Image)
    # 灰階影像, 使用 numpy 填補邊緣
    # 只要能處碰到 1 的點, 這個點就可以被標示為 1
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            if np.sum(padded_image[i:i+kSize, j:j+kSize]) > 0: 
                result_image[i, j] = 1
            else:
                result_image[i, j] = 0
    return (result_image * 255).astype(np.uint8)
def erosion(image, kSize = 5):
    norm_Image = image / 255.0
    pad = kSize // 2
    padded_image = np.pad(norm_Image, pad, mode="reflect")
    result_image = np.zeros_like(norm_Image)
    # 灰階影像, 使用 numpy 填補邊緣
    # 假如 kernel 能完整的放進圖片當中, 所有點全部都觸碰到 1, 就表示這個點可以留下來 設為 1 , 其他情況就刪掉, 設為 0 
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            if np.sum(padded_image[i:i+kSize, j:j+kSize]) == kSize ** 2:
                result_image[i, j] = 1
            else:
                result_image[i, j] = 0
    return (result_image * 255).astype(np.uint8)
# Opening : 先 erosion 再 dilation
# Closing: 先 dilation 再 erosion 

image = cv2.imread('binary.png', cv2.IMREAD_GRAYSCALE) 
erosion_image = erosion(image, 5)
dilation_image = dilation(image, 5)
opening_image = dilation(erosion(image, 5))
closing_image = erosion(dilation(image, 5))

images = [image, erosion_image, dilation_image, opening_image, closing_image]
labels = ['Original', 'Erosion', 'Dilation', 'Opening', 'Closing']
fig, axs = plt.subplots(1, 5, figsize=(10, 5))
axs = axs.flatten()
for i in range(images.__len__()):
    axs[i].axis('off')
    axs[i].imshow(images[i], cmap='gray')
    axs[i].set_title(labels[i])
plt.show()
# cv2.imwrite('erosion.png', erosion_image)
# cv2.imwrite('dilation.png', dilation_image)
# cv2.imwrite('opening.png', opening_image)
# cv2.imwrite('closing.png', closing_image)