from numpy import *
from math import log
import operator


def calcShannonEnt(dataset):
    numdataset = len(dataset)
    labelCount = {}
    for data in dataset:
        curlabel = data[-1]
        if curlabel not in labelCount.keys():
            labelCount[curlabel] = 0
        labelCount[curlabel] += 1
    shannonEnt = 0.0
    for key in labelCount:
        prob = float(labelCount[key]) / numdataset
        shannonEnt -= prob * log(prob, 2)
    return shannonEnt


def creatDataSet():
    dataset = [['1', '1', '1', '1', '3'],
               ['1', '1', '1', '2', '2'],
               ['1', '1', '2', '1', '3'],
               ['1', '1', '2', '2', '1'],
               ['1', '2', '1', '1', '3'],
               ['1', '2', '1', '2', '2'],
               ['1', '2', '2', '1', '3'],
               ['1', '2', '2', '2', '1'],
               ['2', '1', '1', '1', '3'],
               ['2', '1', '1', '2', '2'],
               ['2', '1', '2', '1', '3'],
               ['2', '1', '2', '2', '1'],
               ['2', '2', '1', '1', '3'],
               ['2', '2', '1', '2', '2'],
               ['2', '2', '2', '1', '3'],
               ['2', '2', '2', '2', '3'],
               ['3', '1', '1', '1', '3'],
               ['3', '1', '1', '2', '3'],
               ['3', '1', '2', '1', '3'],
               ['3', '1', '2', '2', '1'],
               ['3', '2', '1', '1', '3'],
               ['3', '2', '1', '2', '2'],
               ['3', '2', '2', '1', '3'],
               ['3', '2', '2', '2', '3']]
    label = ['age', 'prescript', 'astigmatic', 'tearRate']
    return dataset, label


def splitDataSet(dataSet, axis, value):
    retDataSet = []
    for featVec in dataSet:
        if featVec[axis] == value:
            redFeatVec = featVec[:axis]
            redFeatVec.extend(featVec[axis + 1:])
            retDataSet.append(redFeatVec)
    return retDataSet


def choosebestFeaturnToSplit(dataSet):
    numFeature = len(dataSet[0]) - 1
    baseEntropy = calcShannonEnt(dataSet)
    bestInfoGain = 0.0
    bestfeature = -1
    for i in range(numFeature):
        features = [example[i] for example in dataSet]
        uniqueVals = set(features)
        newEntropy = 0.0
        splitInfo = 0.0
        for value in uniqueVals:
            subdataSet = splitDataSet(dataSet, i, value)
            prob = len(subdataSet) / float(len(dataSet))
            newEntropy += prob * calcShannonEnt(subdataSet)
            splitInfo -= prob * log(prob, 2)
        InfoCain = (baseEntropy - newEntropy) / splitInfo
        if InfoCain > bestInfoGain:
            bestInfoGain = InfoCain
            bestfeature = i
    return bestfeature


def majority(classList):
    classcount = {}
    for vote in classList:
        if vote not in classcount.keys():
            classcount[vote] = 0
        # classcount = classcount + 1
    sortedclasscount = sorted(classcount, key=operator.itemgetter(1), reverse=True)
    return sortedclasscount[0][0]


def createTree(dataSet, labels):
    classList = [example[-1] for example in dataSet]
    if classList.count(classList[0]) == len(classList):
        return classList[0]
    if len(dataSet[0]) == 1:
        return majority(classList)
    bestfeat = choosebestFeaturnToSplit(dataSet)
    bestfeatlabel = labels[bestfeat]
    myTree = {bestfeatlabel: {}}
    del (labels[bestfeat])
    featValues = [example[bestfeat] for example in dataSet]
    uniqualVals = set(featValues)
    for value in uniqualVals:
        myTree[bestfeatlabel][value] = createTree(splitDataSet(dataSet, bestfeat, value), labels)
    return myTree


dataSet, labels = creatDataSet()
shannonEnt = calcShannonEnt(dataSet)
print(shannonEnt)
bestfeature = choosebestFeaturnToSplit(dataSet)
print(bestfeature)
mytree = createTree(dataSet, labels)
print(mytree)



