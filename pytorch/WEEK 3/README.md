## 1. 视频学习

### （1） 深度学习的数学基础

​      关于深度学习的数学原理包括线性代数，概率统计，微积分。~~数学原理好多没怎么听懂，后面会好好的再看一遍。~~

### （2） 卷积精神网络

#####  · CNN的基本结构

######  · 卷积

​     通过卷积操作对输入图像进行降维和特征抽取。卷积运算是线性操作，可以捕捉图像的局部、   细节信息，即输出图像每个像素。无论输入图片多大，卷积的参数都是固定的。

###### · 池化

​      池化是对图像的某一个区域用一个值代替，如最大值或平均值。如采用最大值就是max池化，如采用均值就是均值池化。池化可以降维，缩减模型大小，提高计算速度。池化也可以降低过拟合概率，提升特征提取鲁棒性。

######  · 全连接

​      全连接就是个矩阵乘法，相当于一个特征空间变换，可以把前面所有有用的信息提取整合。全连接的一个作用是维度变换，尤其是可以把高维变到低维，同时把有用的信息保留下来。全连接另一个作用是隐含语义的表达，把原始特征映射到各个隐语义节点。

##### · 典型网络结构

######  · AlexNet

​      AlexNet 包含八层前五层是卷积层，之后一些层[最大池化层，最后三层是全连接层。

######  · VGG

​      运用小卷积核，小池化核和全连接转卷积。

###### · GoogleNet

​      inception结构就是由多个这样的inception模块串联起来的。inception结构的主要贡献有两个：一是使用1x1的卷积来进行升降维；二是在多个尺寸上同时进行卷积再聚合。

###### · ResNet

​      ResNet是一种残差网络，咱们可以把它理解为一个子网络，这个子网络经过堆叠可以构成一个很深的网络。



## 2. 代码练习

### · MNIST 数据集分类

​      PyTorch里包含了 MNIST， CIFAR10 等常用数据集，调用 torchvision.datasets 即可把这些数据由远程下载到本地。

```python
input_size  = 28*28   # MNIST上的图像尺寸是 28x28
output_size = 10      # 类别为 0 到 9 的数字，因此为十类

train_loader = torch.utils.data.DataLoader(
    datasets.MNIST('./data', train=True, download=True,
        transform=transforms.Compose(
            [transforms.ToTensor(),
             transforms.Normalize((0.1307,), (0.3081,))])),
    batch_size=64, shuffle=True)

test_loader = torch.utils.data.DataLoader(
    datasets.MNIST('./data', train=False, transform=transforms.Compose([
             transforms.ToTensor(),
             transforms.Normalize((0.1307,), (0.3081,))])),
    batch_size=1000, shuffle=True)
```

​      显示数据集中的图像。

```python
plt.figure(figsize=(8, 5))
for i in range(20):
    plt.subplot(4, 5, i + 1)
    image, _ = train_loader.dataset.__getitem__(i)
    plt.imshow(image.squeeze().numpy(),'gray')
    plt.axis('off');
```

​      实验中每张图片大小是28*28像素，黑色像素值为0，白色像素值为1，数据集是长度为10的一维数组。将数据集输入神经网络，然后显示数据集中的图像。

### · CIFAR10 数据集分类

​       下面将使用CIFAR10数据集，它包含十个类别：‘airplane’, ‘automobile’, ‘bird’, ‘cat’, ‘deer’, ‘dog’, ‘frog’, ‘horse’, ‘ship’, ‘truck’。CIFAR-10 中的图像尺寸为3x32x32，也就是RGB的3层颜色通道，每层通道内的尺寸为32*32。

​      首先，加载并归一化 CIFAR10 使用 torchvision 。torchvision 数据集的输出是范围在[0,1]之间的 PILImage，我们将他们转换成归一化范围为[-1,1]之间的张量 Tensors。

```python
import torch
import torchvision
import torchvision.transforms as transforms
import matplotlib.pyplot as plt
import numpy as np
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

# 使用GPU训练，可以在菜单 "代码执行工具" -> "更改运行时类型" 里进行设置
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

transform = transforms.Compose(
    [transforms.ToTensor(),
     transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])

# 注意下面代码中：训练的 shuffle 是 True，测试的 shuffle 是 false
# 训练时可以打乱顺序增加多样性，测试是没有必要
trainset = torchvision.datasets.CIFAR10(root='./data', train=True,
                                        download=True, transform=transform)
trainloader = torch.utils.data.DataLoader(trainset, batch_size=64,
                                          shuffle=True, num_workers=2)

testset = torchvision.datasets.CIFAR10(root='./data', train=False,
                                       download=True, transform=transform)
testloader = torch.utils.data.DataLoader(testset, batch_size=8,
                                         shuffle=False, num_workers=2)

classes = ('plane', 'car', 'bird', 'cat',
           'deer', 'dog', 'frog', 'horse', 'ship', 'truck')
```

​      展示CIFAR10的图片

```python
def imshow(img):
    plt.figure(figsize=(8,8))
    img = img / 2 + 0.5     # 转换到 [0,1] 之间
    npimg = img.numpy()
    plt.imshow(np.transpose(npimg, (1, 2, 0)))
    plt.show()

# 得到一组图像
images, labels = iter(trainloader).next()
# 展示图像
imshow(torchvision.utils.make_grid(images))
# 展示第一行图像的标签
for j in range(8):
    print(classes[labels[j]])
```

​      定义网络，损失函数和优化器

```python
class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(3, 6, 5)
        self.pool = nn.MaxPool2d(2, 2)
        self.conv2 = nn.Conv2d(6, 16, 5)
        self.fc1 = nn.Linear(16 * 5 * 5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)

    def forward(self, x):
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        x = x.view(-1, 16 * 5 * 5)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x

# 网络放到GPU上
net = Net().to(device)
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(net.parameters(), lr=0.001)
```

​      训练网络

```python
for epoch in range(10):  # 重复多轮训练
    for i, (inputs, labels) in enumerate(trainloader):
        inputs = inputs.to(device)
        labels = labels.to(device)
        # 优化器梯度归零
        optimizer.zero_grad()
        # 正向传播 +　反向传播 + 优化 
        outputs = net(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()
        # 输出统计信息
        if i % 100 == 0:   
            print('Epoch: %d Minibatch: %5d loss: %.3f' %(epoch + 1, i + 1, loss.item()))

print('Finished Training')
```

```
Epoch: 1 Minibatch:     1 loss: 2.301
Epoch: 1 Minibatch:   101 loss: 1.736
Epoch: 1 Minibatch:   201 loss: 1.715
Epoch: 1 Minibatch:   301 loss: 1.528
Epoch: 1 Minibatch:   401 loss: 1.760
Epoch: 1 Minibatch:   501 loss: 1.489
Epoch: 1 Minibatch:   601 loss: 1.461
Epoch: 1 Minibatch:   701 loss: 1.448
Epoch: 2 Minibatch:     1 loss: 1.517
Epoch: 2 Minibatch:   101 loss: 1.212
Epoch: 2 Minibatch:   201 loss: 1.493
Epoch: 2 Minibatch:   301 loss: 1.225
Epoch: 2 Minibatch:   401 loss: 1.395
Epoch: 2 Minibatch:   501 loss: 1.470
Epoch: 2 Minibatch:   601 loss: 1.158
Epoch: 2 Minibatch:   701 loss: 1.041
Epoch: 3 Minibatch:     1 loss: 1.225
Epoch: 3 Minibatch:   101 loss: 1.157
Epoch: 3 Minibatch:   201 loss: 1.248
Epoch: 3 Minibatch:   301 loss: 1.205
Epoch: 3 Minibatch:   401 loss: 1.393
Epoch: 3 Minibatch:   501 loss: 1.234
Epoch: 3 Minibatch:   601 loss: 1.344
Epoch: 3 Minibatch:   701 loss: 1.163
Epoch: 4 Minibatch:     1 loss: 1.099
Epoch: 4 Minibatch:   101 loss: 1.243
Epoch: 4 Minibatch:   201 loss: 1.413
Epoch: 4 Minibatch:   301 loss: 1.206
Epoch: 4 Minibatch:   401 loss: 1.371
Epoch: 4 Minibatch:   501 loss: 1.251
Epoch: 4 Minibatch:   601 loss: 1.183
Epoch: 4 Minibatch:   701 loss: 1.012
Epoch: 5 Minibatch:     1 loss: 0.975
Epoch: 5 Minibatch:   101 loss: 1.119
Epoch: 5 Minibatch:   201 loss: 1.119
Epoch: 5 Minibatch:   301 loss: 1.233
Epoch: 5 Minibatch:   401 loss: 0.873
Epoch: 5 Minibatch:   501 loss: 0.997
Epoch: 5 Minibatch:   601 loss: 1.028
Epoch: 5 Minibatch:   701 loss: 0.788
Epoch: 6 Minibatch:     1 loss: 1.099
Epoch: 6 Minibatch:   101 loss: 1.001
Epoch: 6 Minibatch:   201 loss: 0.876
Epoch: 6 Minibatch:   301 loss: 1.037
Epoch: 6 Minibatch:   401 loss: 0.948
Epoch: 6 Minibatch:   501 loss: 0.882
Epoch: 6 Minibatch:   601 loss: 1.043
Epoch: 6 Minibatch:   701 loss: 1.092
Epoch: 7 Minibatch:     1 loss: 0.974
Epoch: 7 Minibatch:   101 loss: 0.847
Epoch: 7 Minibatch:   201 loss: 0.834
Epoch: 7 Minibatch:   301 loss: 0.795
Epoch: 7 Minibatch:   401 loss: 0.964
Epoch: 7 Minibatch:   501 loss: 1.221
Epoch: 7 Minibatch:   601 loss: 1.013
Epoch: 7 Minibatch:   701 loss: 0.964
Epoch: 8 Minibatch:     1 loss: 0.936
Epoch: 8 Minibatch:   101 loss: 0.992
Epoch: 8 Minibatch:   201 loss: 0.905
Epoch: 8 Minibatch:   301 loss: 0.927
Epoch: 8 Minibatch:   401 loss: 1.057
Epoch: 8 Minibatch:   501 loss: 0.898
Epoch: 8 Minibatch:   601 loss: 0.899
Epoch: 8 Minibatch:   701 loss: 0.778
Epoch: 9 Minibatch:     1 loss: 0.982
Epoch: 9 Minibatch:   101 loss: 0.925
Epoch: 9 Minibatch:   201 loss: 1.224
Epoch: 9 Minibatch:   301 loss: 0.544
Epoch: 9 Minibatch:   401 loss: 0.983
Epoch: 9 Minibatch:   501 loss: 0.961
Epoch: 9 Minibatch:   601 loss: 0.761
Epoch: 9 Minibatch:   701 loss: 0.981
Epoch: 10 Minibatch:     1 loss: 1.051
Epoch: 10 Minibatch:   101 loss: 0.761
Epoch: 10 Minibatch:   201 loss: 0.904
Epoch: 10 Minibatch:   301 loss: 1.213
Epoch: 10 Minibatch:   401 loss: 0.942
Epoch: 10 Minibatch:   501 loss: 0.804
Epoch: 10 Minibatch:   601 loss: 1.043
Epoch: 10 Minibatch:   701 loss: 0.804
Finished Training
```

​     取出测试集中的8张图片

```python
# 得到一组图像
images, labels = iter(testloader).next()
# 展示图像
imshow(torchvision.utils.make_grid(images))
# 展示图像的标签
for j in range(8):
    print(classes[labels[j]])
```

​      把图片输入模型，再看 CNN 将图像识别成什么

```python
outputs = net(images.to(device))
_, predicted = torch.max(outputs, 1)

# 展示预测的结果
for j in range(8):
    print(classes[predicted[j]])
```

​      看看网络在整个数据集的表现。

```python
correct = 0
total = 0

for data in testloader:
    images, labels = data
    images, labels = images.to(device), labels.to(device)
    outputs = net(images)
    _, predicted = torch.max(outputs.data, 1)
    total += labels.size(0)
    correct += (predicted == labels).sum().item()

print('Accuracy of the network on the 10000 test images: %d %%' % (
    100 * correct / total))
```

​      CIFAR10 数据集是用于识别物体的小型数据集，有10类 RGB 图像。通过训练网络来识别数据集中图像的种类。

### · VGG16对CIFAR10分类

##### 1. 定义 dataloader

```python
import torch
import torchvision
import torchvision.transforms as transforms
import matplotlib.pyplot as plt
import numpy as np
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

# 使用GPU训练，可以在菜单 "代码执行工具" -> "更改运行时类型" 里进行设置
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

transform_train = transforms.Compose([
    transforms.RandomCrop(32, padding=4),
    transforms.RandomHorizontalFlip(),
    transforms.ToTensor(),
    transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2010))])

transform_test = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2010))])

trainset = torchvision.datasets.CIFAR10(root='./data', train=True,  download=True, transform=transform_train)
testset  = torchvision.datasets.CIFAR10(root='./data', train=False, download=True, transform=transform_test)

trainloader = torch.utils.data.DataLoader(trainset, batch_size=128, shuffle=True, num_workers=2)
testloader = torch.utils.data.DataLoader(testset, batch_size=128, shuffle=False, num_workers=2)

classes = ('plane', 'car', 'bird', 'cat',
           'deer', 'dog', 'frog', 'horse', 'ship', 'truck')
```

##### 2. VGG 网络定义

```python
class VGG(nn.Module):
    def __init__(self):
        self.cfg = [64, 'M', 128, 'M', 256, 256, 'M', 512, 512, 'M', 512, 512, 'M']
        cfg = [64, 'M', 128, 'M', 256, 256, 'M', 512, 512, 'M', 512, 512, 'M']
        self.features = self._make_layers(cfg)
        self.classifier = nn.Linear(512, 10)
        # self.classifier = nn.Linear(2048, 10)
        
    def forward(self, x):
        out = self.features(x)
        out = out.view(out.size(0), -1)
        out = self.classifier(out)
        return out

    def _make_layers(self, cfg):
        layers = []
        in_channels = 3
        for x in cfg:
            if x == 'M':
                layers += [nn.MaxPool2d(kernel_size=2, stride=2)]
            else:
                layers += [nn.Conv2d(in_channels, x, kernel_size=3, padding=1),
                           nn.BatchNorm2d(x),
                           nn.ReLU(inplace=True)]
                in_channels = x
        layers += [nn.AvgPool2d(kernel_size=1, stride=1)]
        return nn.Sequential(*layers)
```

##### 3. 网络训练

```python
for epoch in range(10):  # 重复多轮训练
    for i, (inputs, labels) in enumerate(trainloader):
        inputs = inputs.to(device)
        labels = labels.to(device)
        # 优化器梯度归零
        optimizer.zero_grad()
        # 正向传播 +　反向传播 + 优化 
        outputs = net(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()
        # 输出统计信息
        if i % 100 == 0:   
            print('Epoch: %d Minibatch: %5d loss: %.3f' %(epoch + 1, i + 1, loss.item()))

print('Finished Training')
```

```
Epoch: 1 Minibatch:     1 loss: 2.391
Epoch: 1 Minibatch:   101 loss: 1.397
Epoch: 1 Minibatch:   201 loss: 1.511
Epoch: 1 Minibatch:   301 loss: 1.057
Epoch: 2 Minibatch:     1 loss: 1.110
Epoch: 2 Minibatch:   101 loss: 0.884
Epoch: 2 Minibatch:   201 loss: 0.878
Epoch: 2 Minibatch:   301 loss: 0.749
Epoch: 3 Minibatch:     1 loss: 0.821
Epoch: 3 Minibatch:   101 loss: 0.764
Epoch: 3 Minibatch:   201 loss: 0.742
Epoch: 3 Minibatch:   301 loss: 0.854
Epoch: 4 Minibatch:     1 loss: 0.726
Epoch: 4 Minibatch:   101 loss: 0.671
Epoch: 4 Minibatch:   201 loss: 0.605
Epoch: 4 Minibatch:   301 loss: 0.508
Epoch: 5 Minibatch:     1 loss: 0.575
Epoch: 5 Minibatch:   101 loss: 0.656
Epoch: 5 Minibatch:   201 loss: 0.570
Epoch: 5 Minibatch:   301 loss: 0.555
Epoch: 6 Minibatch:     1 loss: 0.624
Epoch: 6 Minibatch:   101 loss: 0.623
Epoch: 6 Minibatch:   201 loss: 0.792
Epoch: 6 Minibatch:   301 loss: 0.551
Epoch: 7 Minibatch:     1 loss: 0.510
Epoch: 7 Minibatch:   101 loss: 0.528
Epoch: 7 Minibatch:   201 loss: 0.431
Epoch: 7 Minibatch:   301 loss: 0.483
Epoch: 8 Minibatch:     1 loss: 0.446
Epoch: 8 Minibatch:   101 loss: 0.511
Epoch: 8 Minibatch:   201 loss: 0.551
Epoch: 8 Minibatch:   301 loss: 0.489
Epoch: 9 Minibatch:     1 loss: 0.434
Epoch: 9 Minibatch:   101 loss: 0.621
Epoch: 9 Minibatch:   201 loss: 0.443
Epoch: 9 Minibatch:   301 loss: 0.368
Epoch: 10 Minibatch:     1 loss: 0.378
Epoch: 10 Minibatch:   101 loss: 0.357
Epoch: 10 Minibatch:   201 loss: 0.551
Epoch: 10 Minibatch:   301 loss: 0.413
Finished Training
```

##### 4. 测试验证准确率

```python
correct = 0
total = 0

for data in testloader:
    images, labels = data
    images, labels = images.to(device), labels.to(device)
    outputs = net(images)
    _, predicted = torch.max(outputs.data, 1)
    total += labels.size(0)
    correct += (predicted == labels).sum().item()

print('Accuracy of the network on the 10000 test images: %.2f %%' % (
    100 * correct / total))
```

​      VGG 用连续 3*3 小卷积来代替较大卷积核，提升了网络的深度，带来了较大程度的增益，但参数量需要更大的存储空间来存储。



​      这次学习了深度学习的数学原理，还有一些没有怎么弄明白，之后还要在好好看看，还学习了各种深度学习的模型，了解了深度学习相关的代码。从现在开始就开始慢慢的学习深度学习的相关知识了。

