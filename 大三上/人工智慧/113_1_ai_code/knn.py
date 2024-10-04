import pandas as pd
import numpy as np
from sklearn import neighbors

#計算新產品與資料集的距離面紙廠問卷調查客戶的好惡 2個屬性耐酸性durability 、強度strength
X=pd.DataFrame({"durability":[7, 7, 3, 1],
                "strength": [7, 4, 4, 4]})
#分類 好1壞0
y=np.array([0, 0, 1, 1])
k=3


knn=neighbors.KNeighborsClassifier(n_neighbors=k)
knn.fit(X,y)

#新產品 參數 [DUR,STR]
new_tissue =pd.DataFrame(np.array([[3,7]]))
pred =knn.predict(new_tissue)
print("產品特性 :", new_tissue)
print("產品評價:",pred)