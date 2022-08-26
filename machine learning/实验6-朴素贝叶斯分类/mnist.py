import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

train_name="mnist_train.csv"
test_name="mnist_test.csv"
train_data = pd.read_csv(train_name, header = None)
test_data = pd.read_csv(test_name, header = None)
train_data.head()

x_train = train_data.drop(0, axis = 1)
y_train = train_data[0]
x_test = test_data.drop(0, axis = 1)
y_test = test_data[0]

x_train[x_train <= 128] = 0
x_train[x_train > 128] = 1
x_test[x_test <= 128] = 0
x_test[x_test > 128] = 1

label_counts = y_train.value_counts()
label_counts = label_counts.sort_index()
prior = (label_counts + 1) / (y_train.shape[0] + len(label_counts))
print("先验概率：")
print(prior)

print("条件概率：")
cond = dict()
for classify in label_counts.index:
    a = x_train[y_train == classify]
    for i in x_train.columns:
        b = [0, 1]
        for xi in b:
            c = a.loc[:, i][a.loc[:, i] == xi]
            P = (c.shape[0] + 1) / (a.shape[0] + 2)
            cond["p{}{}|{}".format(xi, i, classify)] = P
            print("p{}{}|{} = {}".format(xi, i, classify, P))


p_y_pred = []
for index, x in x_test.iterrows():
    cls = -1
    probility = -1
    for d in label_counts.index:
        p = 1
        for i, v in x.items():
            p *= cond["p{}{}|{}".format(v, i, d)]
        p *= prior[d]
        if p > probility:
            probility = p
            cls = d
    p_y_pred.append(cls)
    print("测试集样本{}分类结果:{}".format(index + 1, cls))
p_y_pred = np.array(p_y_pred)

y_test = np.array(y_test)
diff = y_test == p_y_pred
true_count = diff.sum()
accurancy = true_count / y_test.shape[0]
print(accurancy)

m_y_pred = []
SAMPLE_COUNT = 5000
idx = np.random.randint(0, x_train.shape[0], SAMPLE_COUNT)
print(idx.shape)
x_sample = x_train.iloc[idx, :]
y_sample = y_train[idx]

max_estimate = dict()  #
for classify in y_train.unique():
    a = x_sample[y_sample == classify]
    for i in x_sample.columns:
        b = [0, 1]
        for xi in b:
            c = a.loc[:, i][a.loc[:, i] == xi]
            P = (c.shape[0] + 1) / (a.shape[0] + 2)
            max_estimate["p{}{}|{}".format(xi, i, classify)] = P
            print("p{}{}|{} = {}".format(xi, i, classify, P))

m_y_pred = []
for index, x in x_test.iterrows():
    cls = -1
    probility = -1
    for c in label_counts.index:
        p = 1   #
        for i, v in x.items():
            p *= max_estimate["p{}{}|{}".format(v, i, c)]
        p *= prior[c]
        if p > probility:
            probility = p
            cls = c
    m_y_pred.append(cls)
    print("测试集样本{} 分类结果:{}".format(index + 1, cls))

m_y_pred = np.array(m_y_pred)

y_test = np.array(y_test)
diff = y_test == m_y_pred
true_count = diff.sum()
accurancy = true_count / y_test.shape[0]
print(accurancy)


