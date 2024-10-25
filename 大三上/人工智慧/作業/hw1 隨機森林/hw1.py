import pandas as pd
import numpy as np
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
import matplotlib.pyplot as plt
from sklearn.tree import plot_tree

order = pd.read_csv("order_train.csv")

label_encoder = preprocessing.LabelEncoder()

order['pat'] = label_encoder.fit_transform(order['pat'])
order['price'] = label_encoder.fit_transform(order['price'])
order['type'] = label_encoder.fit_transform(order['type'])
order['est'] = label_encoder.fit_transform(order['est'])
# 去掉答案跟編號
X = order.drop(['willWait', 'costunerId'], axis=1)
# 答案
y = order['willWait']

# 訓練
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=0)
clf = DecisionTreeClassifier(random_state=0)
clf.fit(X_train, y_train)
print("準確率:", clf.score(X_test, y_test))

# 畫出圖表
plt.figure(figsize=(20, 10))
plot_tree(clf, filled=True, feature_names=X.columns, class_names=['won\'t wait', 'willwait'])
plt.show()