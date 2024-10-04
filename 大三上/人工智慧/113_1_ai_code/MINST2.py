import keras
keras.__version__

from keras.datasets import mnist  #從 keras 的 datasets 匯入 mnist 資料集

(train_images, train_labels), (test_images, test_labels) = mnist.load_data()
#用 mnist.load_data() 取得 mnist 資料集, 並存 (打包) 成 tuple (Python 語法是：只要有逗號, 沒有小括號也會被看成是 tuple, 所以 (train_images, train_labels), (test_images, test_labels) 等同於 ((train_images, train_labels), (test_images, test_labels)), 此 tuple 又內含兩個 tuple

print(train_images.shape)
#train_image 為 NumPy 的 ndarray 物件
#train_image 的 shape 屬性為 3 軸, 60000 維 x28 維 x28 維
                    
print(len(train_labels))
#標籤也有 60000 個
                    
print(train_labels)
#標籤是 0-9 之間的數字, 資料型別為 uint8

print(test_images.shape)
                    #shape 為 3 軸, 10000 維 x28 維 x28 維
                    
print(len(test_labels))
                    #標籤也有 10000 個

print(test_labels)
                    #標籤是 0-9 之間的數字, 資料型別為 uint8
                    
from keras import models
from keras import layers

network = models.Sequential()
network.add(layers.Dense(512, activation='relu', input_shape=(28 * 28,)))
network.add(layers.Dense(10, activation='softmax'))   

network.compile(optimizer='rmsprop',
                loss='categorical_crossentropy',
                metrics=['accuracy'])                 

train_images = train_images.reshape((60000, 28 * 28))  #reshape 是 NumPy 陣列的 method
train_images = train_images.astype('float32') / 255

test_images = test_images.reshape((10000, 28 * 28))
test_images = test_images.astype('float32') / 255

from keras.utils import to_categorical

train_labels = to_categorical(train_labels)
test_labels = to_categorical(test_labels)

network.fit(train_images, train_labels, epochs=5, batch_size=128)

test_loss, test_acc = network.evaluate(test_images, test_labels)
print('test_acc:', test_acc)
