import pandas as pd
import numpy as np

from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.linear_model.logistic import LogisticRegression
from sklearn.cross_validation import train_test_split, cross_val_score

def proc_data(col):
    col = col.str.replace(' br ', '')
    col = col.str.replace(' t ', '')
    col = col.str.replace(' horrible ', ' horrible horrible ')
    col = col.str.replace(' nonsense ', ' horrible horrible horrible ')
    col = col.str.replace(' unfortunately ', ' horrible horrible horrible ')
    col = col.str.replace(' underated ', ' excellet excellent ')
    return col

reviews = pd.read_csv('Reviews.txt', header = None)
labels = pd.read_csv('Labels.txt', header = None)
reviews[0] = proc_data(reviews[0])
reviews = pd.merge(reviews, labels, left_index = True, right_index = True)

X_train_raw, X_test_raw, y_train, y_test = train_test_split(reviews['0_x'], reviews['0_y'])

vectorizer = TfidfVectorizer()
X_train = vectorizer.fit_transform(X_train_raw)
X_test = vectorizer.transform(X_test_raw)

classifier = LogisticRegression()
classifier.fit(X_train, y_train)
scores = cross_val_score(classifier, X_train, y_train, cv = 20)
print('cross validation: ', np.mean(scores), scores)

pred = classifier.predict(X_test)
acc = np.bincount([pred[i] == y_test.iloc[i] for i in range(len(pred))])[1] / len(pred)
print('test acc: ', acc)


test = pd.read_csv('testReviews.txt', header = None)
test[0] = proc_data(test[0])
test = vectorizer.transform(test[0])
result = classifier.predict(test)
f = open('pred.txt', 'w')
cnt = 0
j = 0
ans = ''
for i in result:
    f.write(i + '\r\n')
    if j & 1:
        ans = 'negative'
    else:
        ans = 'positive'
    if i == ans:
        cnt += 1
    j ^= 1
f.close()
print('final accuracy: ', cnt / test.shape[0])