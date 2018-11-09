#-*-coding:utf-8-*-
import numpy as np
import random
import time
a = []
b = []
for i in range(300000):
    a.append(random.randint(1,100))
    b.append(random.randint(1,100))
# print(a,b)
aArray = np.array(a)
bArray = np.array(b)
z = 0
time1 = time.time()
for i in range(300000):
    z += a[i] * b[i]
print(z)
print("for循环：" + str(float(time.time()-time1)*1000))

time2 = time.time()
zArray = np.dot(aArray,bArray)
print(zArray)
print("向量化："+ str(float(time.time()-time2)*1000))
