import numpy as np
import pandas as pd
#線性回歸模組
from sklearn.linear_model import LinearRegression

#溫度
temperatures =np.array([29, 28, 34, 31, 25, 29, 32, \
                        31, 24,33, 25, 31, 26, 30])
#飲料銷售
drink_sales = np.array([7.7, 6.2, 9.3, 8.4, 5.9, 6.4, \
                        8.0, 7.5, 5.8, 9.1, 5.1, 7.3, 6.5, 8.4])
#轉成DataFrame格式
X = pd.DataFrame(temperatures, columns=["Temperture"])
target = pd.DataFrame(drink_sales, columns=["Drink_sales"])
y = target["Drink_sales"]

lm=LinearRegression() #建立物件
lm.fit(X,y)  #訓練模型
print("迴歸係數 : %f" % lm.coef_)
print(" 截距 : %f " % lm.intercept_)

#預測氣溫26, 30 度的業績
new_temperatures =pd.DataFrame(np.array([26, 30]))
predicted_sales = lm.predict(new_temperatures)
print(predicted_sales)

import matplotlib.pyplot as plt
plt.scatter(temperatures, drink_sales) 
#繪出原始資料
regression_sales =lm.predict(X)
#繪出預測資料
plt.plot(temperatures, regression_sales, color="blue")
plt.plot(new_temperatures, predicted_sales, color="red", \
         marker="o", markersize=10)
plt.show()

