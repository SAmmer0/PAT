def getInput():
    nodeNum = raw_input()
    nodeNum = int(nodeNum)
    nodeList = list()
    for dummy_i in xrange(nodeNum):
        thisNode = raw_input()
        thisNode = thisNode.strip().split()
        newThisNode = list()
        for c in thisNode:
            if c == '-':
                newThisNode.append(None)
            else:
                newThisNode.append(int(c))
        nodeList.append(newThisNode)
    return nodeList

def getRootIdx(nodeList):
    allNode = set(range(len(nodeList)))
    nodes = list()
    for node in nodeList:
        nodes += node
    nodes = set(nodes)
    nodes = allNode.intersection(nodes)
    rootNode = allNode.difference(nodes).pop()
    return rootNode

def isLeaves(node):
    if node[0] == None and node[1] == None:
        return True
    else:
        return False

def getLeaves(nodeList):
    res = list()
    rootNodeIdx = getRootIdx(nodeList)
    queue = list()
    queue.append(rootNodeIdx)
    while len(queue) != 0:
        thisNodeIdx = queue.pop(0)
        # print "pop ", thisNodeIdx
        thisNode = nodeList[thisNodeIdx]
        if isLeaves(thisNode):
            res.append(thisNodeIdx)
            continue
        leftIdx = thisNode[0]
        rightIdx = thisNode[1]
        if leftIdx != None:
            queue.append(leftIdx)
            # print "append left child ", leftIdx
        if rightIdx != None:
            queue.append(rightIdx)
            # print "append right child ", rightIdx
    return res

if __name__ == "__main__":
    nodes = getInput()
    result = getLeaves(nodes)
    result = map(str, result)
    result = ' '.join(result)
    print result
