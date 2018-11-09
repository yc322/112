# -*- coding:utf-8 -*-
import random

from sklearn import datasets
from sklearn import tree

from sklearn.linear_model import LogisticRegression
def get_acc(predict,target):
    totle = len(predict)
    trueCount = 0
    for i in range(totle):
        if predict[i] == target[i]:
            trueCount += 1
    return  float(trueCount) / float(totle)



# 加载数据集
iris =datasets.load_iris()
#分割训练集，测试集
# 前120个训练集，后30个测试集

index = list(range(len(iris.data)))
random.seed(1)
random.shuffle(index)
trainIndex =index[:120]
testIndex = index[120:]




x_train = iris.data[trainIndex,:]
y_train = iris.target[trainIndex]

x_test = iris.data[testIndex,:]
y_test = iris.target[testIndex]


featureList = [2,3]
#clf = tree.DecisionTreeClassifier()
clf=LogisticRegression()
clf.fit(x_train[:,featureList],y_train)
answer = clf.predict(x_test[:,featureList])
print(get_acc(answer,y_test))


