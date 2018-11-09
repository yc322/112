# -*- coding: UTF-8 -*-
import numpy as np
import pandas as pd
import string
import re

# from sklearn.linear_model import LogisticRegression as LR
from sklearn.feature_extraction.text import TfidfVectorizer as TFIDF

def proc_data(col):
    col=col.replace('br','')
    col=col.replace('t','')
    col =col.replace('excellent','good good')
    col=col.replace('amazing','good good good')
    col = col.replace(' horrible ', ' horrible horrible ')
    col = col.replace(' nonsense ', ' horrible horrible horrible ')
    col = col.replace(' unfortunately ', ' horrible horrible horrible ')
    col = col.replace(' underated ', ' excellet excellent ')
    return col

txt = open('C:/Users/17621/Desktop/final/Reviews.txt')
readl = txt.readline()
readl = re.sub("[.,\n]", " ", readl)
train_data = []

while readl:
    ff = str(readl)
    ff=proc_data(ff)
    words = ff.lower().split()
    train_data.append(' '.join(words))
    readl = txt.readline()
    readl = re.sub("[.,\n]", " ", readl)
txt.close()
print(train_data[1])

txt = open('C:/Users/17621/Desktop/final/testReviews.txt')
readl = txt.readline()
readl = re.sub("[.,\n]", " ", readl)

test_data = []

while readl:
    ff = str(readl)
    ff=proc_data(ff)
    words = ff.lower().split()
    test_data.append(' '.join(words))
    readl = txt.readline()
    readl = re.sub("[.,\n]", " ", readl)
txt.close()

txt = open('C:/Users/17621/Desktop/final/Labels.txt')
readl = txt.readline()
train_label = []

while readl:
    readl = re.sub("[.,\n]", "", readl)
    ff = str(readl)
    train_label.append(''.join(ff))
    readl = txt.readline()
txt.close()

print(train_label)
label = []
for la in train_label:
    if la == "positive":
        label.append(1)
    else:
        label.append(0)

print(label)


tfidf = TFIDF(min_df=2, # 最小支持度为2
           max_features=None,
           strip_accents='unicode',
           analyzer='word',
           token_pattern=r'\w{1,}',
           ngram_range=(1, 3),  # 二元文法模型
           use_idf=1,
           smooth_idf=1,
           sublinear_tf=1,
           stop_words = 'english') # 去掉英文停用词

# 合并训练和测试集以便进行TFIDF向量化操作
data_all = train_data + test_data
len_train = len(train_data)

tfidf.fit(data_all)
data_all = tfidf.transform(data_all)

train_x = data_all[:len_train]
test_x = data_all[len_train:]
print(train_x)

from sklearn.linear_model import LogisticRegression as LR
from sklearn.model_selection import GridSearchCV



# 设定grid search的参数
grid_values = {'C':[30]}
# 设定打分为roc_auc
model_LR = GridSearchCV(LR(random_state = 0), grid_values, scoring = 'roc_auc', cv = 20)
model_LR.fit(train_x, label)
GridSearchCV(cv=20, estimator=LR(C=1.0, class_weight=None, dual=True,
             fit_intercept=True, intercept_scaling=1, penalty='L2', random_state=0, tol=0.0001),
        fit_params={}, iid=True, n_jobs=1,
        param_grid={'C': [30]}, pre_dispatch='2*n_jobs', refit=True,
        scoring='roc_auc', verbose=0)
print model_LR.grid_scores_
test_predicted = np.array(model_LR.predict(test_x))
print(test_predicted)

fl = open('C:/Users/17621/Desktop/final/result.txt', 'w')
for elem in test_predicted:
    if elem == 1:
        fl.write("positive")
        fl.write("\n")
    else:
        fl.write("negative")
        fl.write("\n")


