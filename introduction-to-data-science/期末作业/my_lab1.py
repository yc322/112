import pandas as pd
import numpy as np
import nltk
import math
import string
from nltk.corpus import stopwords
from collections import Counter
from nltk.stem.porter import *
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.linear_model.logistic import LogisticRegression
from sklearn.cross_validation import train_test_split, cross_val_score

def proc_data(col):
    col=col.str.replace('br','')
    col=col.str.replace('t','')
    col = col.str.replace(' horrible ', ' horrible horrible ')
    col = col.str.replace(' nonsense ', ' horrible horrible horrible ')
    col = col.str.replace(' unfortunately ', ' horrible horrible horrible ')
    col = col.str.replace(' underated ', ' excellet excellent ')
    return col

def get_tokens(text):
    lowers = text.lower()
    #remove the punctuation using the character deletion step of translate
    remove_punctuation_map = dict((ord(char), None) for char in string.punctuation)
    no_punctuation = lowers.translate(remove_punctuation_map)
    tokens = nltk.word_tokenize(no_punctuation)
    return tokens

#import test data and train data
reviews = pd.read_csv('Reviews.txt',header = None)
reviews[0]=proc_data(reviews[0])
labels = pd.read_csv('Labels.txt', header = None)
reviews = pd.merge(reviews, labels, left_index = True, right_index = True)
#reviews.columns=["emotion"]
def stem_tokens(tokens, stemmer):
    stemmed = []
    for item in tokens:
        stemmed.append(stemmer.stem(item))
    return stemmed

for item in reviews["0_x"]:
    # print(item)
    tokens = get_tokens(item)
    filtered = [w for w in tokens if not w in stopwords.words('english')]
    stemmer = PorterStemmer()
    stemmed = stem_tokens(filtered, stemmer)
    count = Counter(stemmed)
    # print(count.most_common(10))
    # print(item)

X_train_raw, X_test_raw, y_train, y_test = train_test_split(reviews['0_x'], reviews['0_y'])
vectorizer = TfidfVectorizer(min_df=2,ngram_range=(1,3))
X_train = vectorizer.fit_transform(X_train_raw)
X_test = vectorizer.transform(X_test_raw)


classifier = LogisticRegression(C=30.0,penalty='l2',dual=True)
classifier.fit(X_train, y_train)

scores = cross_val_score(classifier, X_train, y_train, cv = 20)
print('cross validation: ', np.mean(scores), scores)
pred = classifier.predict(X_test)
acc = np.bincount([pred[i] == y_test.iloc[i] for i in range(len(pred))])[1] / len(pred)
print('test acc: ', acc)

test = pd.read_csv('testReviews.txt', header = None)
test[0] = proc_data(test[0])

for item in test[0]:
    # print(item)
    tokens = get_tokens(item)
    filtered = [w for w in tokens if not w in stopwords.words('english')]
    stemmer = PorterStemmer()
    stemmed = stem_tokens(filtered, stemmer)
    # print(stemmed)
    count = Counter(stemmed)
    # print (count.most_common(10))
    item=" ".join(stemmed)
    # print(item+'\n\n')

test = vectorizer.transform(test[0])
result = classifier.predict(test)

f = open('pred3.txt', 'w')
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
    print(cnt)
    j ^= 1
f.close()
print('final accuracy: ', cnt / test.shape[0])
