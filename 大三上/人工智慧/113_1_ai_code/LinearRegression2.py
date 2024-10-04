import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt

heights =np.array([147.9, 163.5, 159.8, 155.1, 163.3, \
                   158.7, 172.0, 161.2, 153.9, 161.6])
weights = np.array([41.7, 60.2, 47.0, 53.2, 48.3, 55.2, \
                    58.5, 49.0, 46.7, 52.5])

X = pd.DataFrame(heights, columns=["Height"])
target = pd.DataFrame(weights, columns=["Weight"])
y = target["Weight"]

lm=LinearRegression()
lm.fit(X,y)

print("迴歸係數 : %f" % lm.coef_)
print(" 截距 : %f " % lm.intercept_)

#預測150, 160, 170的體重
new_heights =pd.DataFrame(np.array([150, 160, 170]))
predicted_weights = lm.predict(new_heights)
print(predicted_weights)

plt.scatter(heights, weights) #匯點
regression_weights =lm.predict(X)
plt.plot(heights, regression_weights,color="blue")
plt.plot(new_heights, predicted_weights, color="red",\
         marker="o", markersize=10)
plt.show()
