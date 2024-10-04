# Binary classification
# Kaggle Titanic提供的原始資料train dataset，

import pandas as pd
import numpy as np
from sklearn import preprocessing, linear_model

titanic = pd.read_csv("train.csv")
print(titanic.info())

'''RangeIndex: 891 entries, 0 to 890
Data columns (total 12 columns):
PassengerId    891 non-null int64
Survived       891 non-null int64
Pclass         891 non-null int64
Name           891 non-null object
Sex            891 non-null object
Age            714 non-null float64
SibSp          891 non-null int64
Parch          891 non-null int64
Ticket         891 non-null object
Fare           891 non-null float64
Cabin          204 non-null object
Embarked       889 non-null object
dtypes: float64(2), int64(5), object(5)
memory usage: 83.6+ KB
'''

#Age中有NaN資料
age_median = np.nanmedian(titanic["Age"]) #計算age中位數
print("年齡中位數", age_median)
new_age=np.where(titanic["Age"].isnull(), age_median, titanic["Age"])
 #若空以中位數取敗
titanic["Age"]=new_age

#PClass欄位為無\文字轉數字
label_encoder = preprocessing.LabelEncoder()
encoded_class = label_encoder.fit_transform(titanic["Pclass"])
 #姜滄等轉繩數字 1st, 2nd, ...

titanic["Sex"].replace(['female','male'],[0,1],inplace=True) 
#將female male 轉成 0, 1
X= pd.DataFrame([encoded_class, titanic["Sex"], titanic["Age"]]).T
 #Sex為string 
#X= pd.DataFrame([encoded_class,  titanic["Age"]]).T


y=titanic["Survived"]

logistic = linear_model.LogisticRegression()
logistic.fit(X,y)
print("迴歸係數:", logistic.coef_)
print("截距 ", logistic.intercept_)
preds =logistic.predict(X)
print(pd.crosstab(preds, titanic["Survived"]))
print(logistic.score(X,y))

