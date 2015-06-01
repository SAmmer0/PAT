class Node:
    
    def __init__(self, value, left=None, right=None):
        self._value = value
        self._left = left
        self._right = right


def insertNode(root, value):
    lastNode = None
    tmpNode = root
    while tmpNode != None:
        if value <= tmpNode._value:
            lastNode = tmpNode
            tmpNode = tmpNode._left
        else:
            lastNode = tmpNode
            tmpNode = tmpNode._right
    newNode = Node(value)
    if value <= lastNode._value:
        lastNode._left = newNode
    else:
        lastNode._right = newNode
    return lastNode


def has2Child(node):
    return node._left != None and node._right != None


def isTraversalPath(dataList):
    root = None
    for item in dataList:
        lastNode = None
        if root == None:
            root = Node(item)
        else:
            lastNode = insertNode(root, item)
            if has2Child(lastNode):
                return False
    return True

def getInput():
    dataMsg = raw_input()
    dataMsg = dataMsg.strip().split()
    numOfRows = int(dataMsg[0])
    res = list()
    for row in xrange(numOfRows):
        thisRow = raw_input()
        thisRow = thisRow.strip().split()
        thisRow = map(int, thisRow)
        res.append(thisRow)
    return res

def main():
    treeData = getInput()
    for path in treeData:
        if isTraversalPath(path):
            print "YES"
        else:
            print "NO"

if __name__ == "__main__":
    main()

