class Node:
    def __init__(self, data, left=None, right=None):
        self._data = data
        self._left = left
        self._right = right

class Tree:
    def __init__(self, root):
        self._root = root


def getInput():
    nodeNum = int(raw_input())
    res = list()
    for dummy_i in xrange(2*nodeNum):
        thisAction = raw_input()
        thisAction = thisAction.split()
        if thisAction[0] == "Push":
            thisAction[1] = int(thisAction[1])
        else:
            thisAction.append(None)
        res.append(thisAction)
    return res

def buildTree(stackLog):
    root = None
    stack = list()
    lastAction = "Pop"
    lastNode = None
    for idx in xrange(len(stackLog)):
        thisAction = stackLog[idx][0]
        if thisAction == "Push" and lastAction == "Pop":
            thisNode = Node(stackLog[idx][1])
            stack.append(thisNode)
            if lastNode == None:
                root = thisNode
                lastNode = thisNode
            else:
                addRightChild(lastNode, thisNode)
                lastNode = thisNode
            lastAction = "Push"
        elif thisAction == "Push":
            thisNode = Node(stackLog[idx][1])
            stack.append(thisNode)
            addLeftChild(lastNode, thisNode)
            lastNode = thisNode
        else:
            lastNode = stack.pop()
            lastAction = "Pop"
    resTree = Tree(root)
    return resTree

def postOrderTraversal(node):
    thisNode = node
    res = list()
    lastNode = None
    stack = list()
    while len(stack) != 0 or thisNode != None:
        # print len(stack)
        # print "In while"
        if thisNode != None:
            stack.append(thisNode)
            thisNode = thisNode._left
        else:
            peekNode = stack[-1]
            if peekNode._right != None and lastNode != peekNode._right:
                thisNode = peekNode._right
            else:
                tmpNode = stack.pop()
                res.append(str(tmpNode._data))
                lastNode = tmpNode
    return res


def addLeftChild(father, child):
    father._left = child

def addRightChild(father, child):
    father._right = child

if __name__ == "__main__":
    log = getInput()
    # print log
    tree = buildTree(log)
    postOrderNodes = postOrderTraversal(tree._root)
    postOrderNodes = ' '.join(postOrderNodes)
    print postOrderNodes