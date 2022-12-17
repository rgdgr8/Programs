import pandas as pd
import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt
import nltk
from nltk.stem import PorterStemmer
from nltk.stem.wordnet import WordNetLemmatizer
import string
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score
from sklearn.model_selection import train_test_split

nltk.download('stopwords')
nltk.download('wordnet')
nltk.download('omw-1.4')

df = pd.read_csv("https://raw.githubusercontent.com/rgdgr8/Programs/master/DL_assignment/Dataset.csv", index_col='tweet_id')

"""# Pre-processing(overall)"""

# Class wise distribution ---- Highly skewed.
df['airline_sentiment'].value_counts()

# Column wise null value counts
df.isna().sum()

# entries containing both hashtags and mentions
# df.loc[570239632807370753,'text']

# texts = df['text']
# without_mention = texts.str.replace(r'(@\w+)',"")
# without_mention

# removed mentions and hashtags
# df['text'] = df['text'].str.replace(r'(@\w+)',"")
# df['text'] = df['text'].str.replace(r'(#\w+)',"")

df = df.iloc[:, [9,0]]

X = df['text']
Y = df['airline_sentiment']

x_train, x_test, y_train, y_test = train_test_split(X,Y,test_size=0.2, random_state= 453,stratify = Y)

print("X_train shape: ",x_train.shape)
print("Y_train shape: ",y_train.shape)
print(y_train.value_counts())

print("X_test shape: ",x_test.shape)
print("Y_test shape: ",y_test.shape)
print(y_test.value_counts())

"""#Text cleaning and character embedding"""

import re

def clean_string(text, stem="None"):

    final_string = ""

    # Make lower
    text = text.lower()

    # Remove line breaks
    text = re.sub(r'\n', '', text)

    # Remove puncuation
    # translator = str.maketrans('', '', string.punctuation)
    # text = text.translate(translator)

    # Remove stop words
    text = text.split()
    useless_words = nltk.corpus.stopwords.words("english")
    useless_words = useless_words + ['hi', 'im']

    text_filtered = [word for word in text if not word in useless_words]

    # # Remove numbers
    # text_filtered = [re.sub(r'\w*\d\w*', '', w) for w in text_filtered]

    # Stem or Lemmatize
    if stem == 'Stem':
        stemmer = PorterStemmer() 
        text_stemmed = [stemmer.stem(y) for y in text_filtered]
    elif stem == 'Lem':
        lem = WordNetLemmatizer()
        text_stemmed = [lem.lemmatize(y) for y in text_filtered]
    else:
        text_stemmed = text_filtered

    final_string = ' '.join(text_stemmed)

    return final_string

x_train = x_train.apply(lambda x: clean_string(x))
x_test = x_test.apply(lambda x: clean_string(x))

"""##padding with space"""

def pad_string(st:string):
    z = 160 - len(st)
    st = st + (' '*z)
    return st

x_train = x_train.apply(lambda x: pad_string(x))
x_test = x_test.apply(lambda x: pad_string(x))

"""##embedding"""

def string_vectorizer(strng, alphabet=string.ascii_lowercase + string.digits + string.punctuation):
    vector = [[0 if char != letter else 1 for char in alphabet] 
                  for letter in strng]
    return vector

embedded_train = []
for t in x_train:
    v = string_vectorizer(t)
    embedded_train.append(v)
embedded_train = np.array(embedded_train)

embedded_test = []
for t in x_test:
    v = string_vectorizer(t)
    embedded_test.append(v)
embedded_test = np.array(embedded_test)

embedded_train=embedded_train.astype('float64')
embedded_test=embedded_test.astype('float64')

train_feat = embedded_train
test_feat = embedded_test

"""#Encode labels"""

train_labels = np.array(pd.get_dummies(y_train))
test_labels = y_test

val_labels = np.array(pd.get_dummies(y_test))

"""#model"""

model = tf.keras.models.Sequential(
    [
        tf.keras.layers.Conv1D(32, 3, activation='relu'),
        tf.keras.layers.MaxPool1D(strides=2),
        tf.keras.layers.Conv1D(64, 3, activation='relu'),
        tf.keras.layers.MaxPool1D(strides=2),
        tf.keras.layers.Conv1D(128, 3, activation='relu'),
        tf.keras.layers.MaxPool1D(strides=2),
        # tf.keras.layers.Conv1D(64, 3, activation='relu'),
        # tf.keras.layers.MaxPool1D(strides=2),
        tf.keras.layers.Flatten(),
        # tf.keras.layers.Dropout(0.25),
        # tf.keras.layers.Dense(512, activation='relu'),
        tf.keras.layers.Dropout(0.20),
        tf.keras.layers.Dense(256, activation='relu'),
        tf.keras.layers.Dropout(0.25),
        tf.keras.layers.Dense(128, activation='relu'),
        tf.keras.layers.Dense(3, activation='softmax')
    ]
)

model.compile(loss=tf.keras.losses.CategoricalCrossentropy(), optimizer='adam', metrics='accuracy')

callback = tf.keras.callbacks.EarlyStopping(monitor='val_accuracy', patience= 3)

history = model.fit(train_feat, train_labels, epochs= 8, batch_size = 256, validation_data=(test_feat, val_labels),callbacks = callback)

# summarize history for accuracy
plt.figure(figsize = (9,4))
plt.plot(history.history['accuracy'],linewidth = 2.5)
plt.plot(history.history['val_accuracy'],linewidth = 2.5)
plt.title('Model Accuracy')
plt.ylabel('Accuracy')
plt.xlabel('Epoch')
plt.legend(['train', 'test'], loc='upper left')
plt.show()

# summarize history for loss
plt.figure(figsize = (9,4))
plt.plot(history.history['loss'],linewidth = 2.5)
plt.plot(history.history['val_loss'],linewidth = 2.5)
plt.title('Model Loss')
plt.ylabel('Loss')
plt.xlabel('Epoch')
plt.legend(['train', 'test'], loc='upper left')
plt.show()

pred = model.predict(test_feat)

model.summary()

prediction=[]
for p in pred:
    xx = np.argmax(p)
    if xx==2:
        prediction.append('positive')
    elif xx==1:
        prediction.append('neutral')
    else:
        prediction.append('negative')

print("Accuracy: ", accuracy_score(test_labels, prediction))
print("Precision: ", precision_score(test_labels, prediction, average='macro'))
print("Recall: ", recall_score(test_labels, prediction, average='macro'))
print("F1: ", f1_score(test_labels, prediction, average='macro'))