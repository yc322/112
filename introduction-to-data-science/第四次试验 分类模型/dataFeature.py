# -*- coding:utf-8 -*-
import random
import numpy as np
from sklearn import datasets
from matplotlib import colors as c
from sklearn.linear_model import LogisticRegression
from matplotlib import colors as c

# 加载数据集
iris =datasets.load_iris()
print(iris.target_names)
print(iris.feature_names)
print(iris.data)
print(iris.target)
#
# print(iris.data.shape)  #150个样本   4个特征

#分割训练集，测试集
# 前120个训练集，后30个测试集

index = list(range(len(iris.data)))
# print(index)
random.seed(1)
random.shuffle(index)
# print(index)
trainIndex =index[:120]
testIndex = index[120:]

x_train = iris.data[trainIndex,:]
y_train = iris.target[trainIndex]

x_test = iris.data[testIndex,:]
y_test = iris.target[testIndex]


import matplotlib.pyplot as plt
data = iris.data

def get_acc(predict,target):
    totle = len(predict)
    trueCount = 0
    for i in range(totle):
        if predict[i] == target[i]:
            trueCount += 1
    return  float(trueCount) / float(totle)

def draw_bonderay(x_max,x_min,y_max,y_min,model):
    cMap = c.ListedColormap(['#c7dcfd', '#b0ea96', '#ffffba'])
    h = .02
    x_max = x_max + .5
    x_min = x_min - .5
    y_max = y_max + .5
    y_min = y_min - .5

    # x_min, x_max = X[:, 0].min() - .5, X[:, 0].max() + .5
    # y_min, y_max = X[:, 1].min() - .5, X[:, 1].max() + .5

    print(x_min)
    print(x_max)

    xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))
    # print(xx)
    # print(yy)
    # Z = logreg.predict(np.c_[xx.ravel(), yy.ravel()])
    Z = model.predict(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)
    plt.pcolormesh(xx, yy, Z, cmap=cMap)

#from sklearn import tree
#clf =LogisticRegression()
from sklearn.naive_bayes import GaussianNB
clf = GaussianNB()

#0,1
plt.subplot(2,3,1)
feature = [0,1]
clf.fit(x_train[:,feature],y_train)
draw_bonderay(data[:,0].max(),data[:,0].min(),data[:,1].max(),data[:,1].min(),clf)
plt.scatter(data[:50,0],data[:50,1],color="red",marker="o",label="setosa")
plt.scatter(data[50:100,0],data[50:100,1],color="blue",marker="x",label="versicolor")
plt.scatter(data[100:,0],data[100:,1],color="green",marker="+",label="virginica")
plt.xlabel("10161511322  sepal length(cm)")
plt.ylabel("10161511322  sepal width(cm)")
plt.legend()
answer = clf.predict(x_test[:,feature])
acc = get_acc(answer,y_test)
plt.title("TestSet Acc:" + str(int(acc *100)) + "%")
# plt.show()




#0,2
plt.subplot(2,3,2)
feature = [0,2]
clf.fit(x_train[:,feature],y_train)
draw_bonderay(data[:,0].max(),data[:,0].min(),data[:,2].max(),data[:,2].min(),clf)
plt.scatter(data[:50,0],data[:50,2],color="red",marker="o",label="setosa")
plt.scatter(data[50:100,0],data[50:100,2],color="blue",marker="x",label="versicolor")
plt.scatter(data[100:,0],data[100:,2],color="green",marker="+",label="virginica")
plt.xlabel("10161511322  sepal length(cm)")
plt.ylabel("10161511322  petal length (cm)")
plt.legend()
answer = clf.predict(x_test[:,feature])
acc = get_acc(answer,y_test)
plt.title("TestSet Acc:" + str(int(acc *100)) + "%")
# plt.show()




#0,3
plt.subplot(2,3,3)
feature = [0,3]
clf.fit(x_train[:,feature],y_train)
draw_bonderay(data[:,0].max(),data[:,0].min(),data[:,3].max(),data[:,3].min(),clf)
plt.scatter(data[:50,0],data[:50,3],color="red",marker="o",label="setosa")
plt.scatter(data[50:100,0],data[50:100,3],color="blue",marker="x",label="versicolor")
plt.scatter(data[100:,0],data[100:,3],color="green",marker="+",label="virginica")
plt.xlabel("10161511322  sepal length(cm)")
plt.ylabel("10161511322  petal width (cm) ")
plt.legend()
answer = clf.predict(x_test[:,feature])
acc = get_acc(answer,y_test)
plt.title("TestSet Acc:" + str(int(acc *100)) + "%")
#plt.show()


#1,2
plt.subplot(2,3,4)
feature = [1,2]
clf.fit(x_train[:,feature],y_train)
draw_bonderay(data[:,1].max(),data[:,1].min(),data[:,2].max(),data[:,2].min(),clf)
plt.scatter(data[:50,1],data[:50,2],color="red",marker="o",label="setosa")
plt.scatter(data[50:100,1],data[50:100,2],color="blue",marker="x",label="versicolor")
plt.scatter(data[100:,1],data[100:,2],color="green",marker="+",label="virginica")
plt.xlabel("10161511322  sepal width (cm)")
plt.ylabel("10161511322  petal length (cm)")
plt.legend()
answer = clf.predict(x_test[:,feature])
acc = get_acc(answer,y_test)
plt.title("TestSet Acc:" + str(int(acc *100)) + "%")
#plt.show()


#1,3
plt.subplot(2,3,5)
feature = [1,3]
clf.fit(x_train[:,feature],y_train)
draw_bonderay(data[:,1].max(),data[:,1].min(),data[:,3].max(),data[:,3].min(),clf)
plt.scatter(data[:50,1],data[:50,3],color="red",marker="o",label="setosa")
plt.scatter(data[50:100,1],data[50:100,3],color="blue",marker="x",label="versicolor")
plt.scatter(data[100:,1],data[100:,3],color="green",marker="+",label="virginica")
plt.xlabel("10161511322  sepal width (cm)")
plt.ylabel("10161511322  petal width (cm)")
plt.legend()
answer = clf.predict(x_test[:,feature])
acc = get_acc(answer,y_test)
plt.title("TestSet Acc:" + str(int(acc *100)) + "%")
#plt.show()




#2,3
plt.subplot(2,3,6)
feature = [2,3]
clf.fit(x_train[:,feature],y_train)
draw_bonderay(data[:,2].max(),data[:,2].min(),data[:,3].max(),data[:,3].min(),clf)
plt.scatter(data[:50,2],data[:50,3],color="red",marker="o",label="setosa")
plt.scatter(data[50:100,2],data[50:100,3],color="blue",marker="x",label="versicolor")
plt.scatter(data[100:,2],data[100:,3],color="green",marker="+",label="virginica")
plt.xlabel("10161511322  petal length (cm)")
plt.ylabel("10161511322  petal width (cm)")
plt.legend()
answer = clf.predict(x_test[:,feature])
acc = get_acc(answer,y_test)
plt.title("TestSet Acc:" + str(int(acc *100)) + "%")
plt.show()
