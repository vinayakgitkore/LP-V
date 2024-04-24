#!/usr/bin/env python
# coding: utf-8

# In[8]:


from sklearn.datasets import load_boston
import pandas as pd

boston_dataset = load_boston()

df = pd.DataFrame(boston_dataset.data,columns=boston_dataset.feature_names)
df['MEDV'] = boston_dataset.target

df.head(n=10)


# In[9]:


from sklearn.model_selection import train_test_split

X = df.loc[:, df.columns != 'MEDV']
y = df.loc[:, df.columns == 'MEDV']
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=123)


# In[12]:


from keras.models import Sequential
from keras.layers import Dense

model = Sequential()

model.add(Dense(128, input_shape=(13, ), activation='relu', name='dense_1'))
model.add(Dense(64, activation='relu', name='dense_2'))
model.add(Dense(1, activation='linear', name='dense_output'))

model.compile(optimizer='adam', loss='mse', metrics=['mae'])
model.summary()


# In[13]:


history = model.fit(X_train, y_train, epochs=2, validation_split=0.05, verbose = 1)


# In[14]:


mse_nn, mae_nn = model.evaluate(X_test, y_test)

print('Mean squared error on test data is: ', mse_nn)
print('Mean absolute error on test data is: ', mae_nn)


# In[ ]:




