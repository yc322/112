# -*- coding:utf-8 -*-
import random

import numpy as np
import time
import math
from sklearn import datasets
from numpy import *
from matplotlib import colors as c
import matplotlib.pyplot as plt

def euclDistance(vector1,vector2):
    return sqrt(sum(power(vector2-vector1,2)))

def initCentroids(dataSet,k):
    numSamples,dim=dataSet.shape
    centroids=zeros((k,dim))
    for i in range(k):
        index=int (random.uniform(0,numSamples))
        centroids[i,:]=dataSet[index,:]
    return centroids

def kmeans(dataSet,k):
    numSamples = dataSet.shape[0]
    clusterAssment = mat(zeros(numSamples,2))
    clusterChange = True


# 加载数据集
iris =datasets.load_iris()
print(iris.target_names)
print(iris.feature_names)
print(iris.data)
print(iris.target)

