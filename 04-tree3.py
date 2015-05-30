class Node:
    def __init__(self, value=None, parent=None, left=None, right=None):
        self._parent = parent
        self._left = left
        self._right = right
        self._value = value




def rotateRight(node):
    if node == node._parent._left:
        tmpParent = node._parent
        tmpChild = node._right
        node._right = tmpChild._left
        if tmpChild._left != None:
            tmpChild._left._parent = node
        tmpChild._left = node
        node._parent = tmpChild
        tmpParent._left = tmpChild
        tmpChild._parent = tmpParent
    else:
        tmpPP = node._parent._parent
        tmpParent = node._parent
        tmpChild = node._left
        tmpParent._right = tmpChild
        if tmpChild != None:
            tmpChild._parent = tmpParent
        node._left = tmpParent
        tmpParent._parent = node
        node._parent = tmpPP
        if tmpPP == None:
            return
        elif tmpPP._right == tmpParent:
            tmpPP._right = node
        else:
            tmpPP._left = node


def rotateLeft(node):
    if node == node._parent._right:
        tmpParent = node._parent
        tmpChild = node._left
        node._left = tmpChild._right
        if tmpChild._right != None:
            tmpChild._right._parent = node
        tmpChild._right = node
        node._parent = tmpChild
        tmpChild._parent = tmpParent
        tmpParent._right = tmpChild
    else:
        tmpPP = node._parent._parent
        tmpParent = node._parent
        tmpChild = node._right
        tmpParent._left = tmpChild
        if tmpChild != None:
            tmpChild._parent = tmpParent
        node._right = tmpParent
        tmpParent._parent = node
        node._parent = tmpPP
        if tmpPP == None:
            return
        elif tmpPP._left == tmpParent:
            tmpPP._left = node
        else:
            tmpPP._right = node

def depth(node):
    if node == None:
        return 0
    else:
        return max(depth(node._left), depth(node._right)) + 1

def balanceFactor(node):
    return depth(node._left) - depth(node._right)

def getInput():
    numOfNodes = int(raw_input())
    data = raw_input()
    data = data.strip().split()
    data = map(int, data)
    return data

def buildTree(data):
    root = None
    for item in data:
        thisNode = Node(item)
        if root != None:
            tmpNode = root
            lastNode = None
            while tmpNode != None:
                lastNode = tmpNode
                if tmpNode._value > item:
                    tmpNode = tmpNode._left
                else:
                    tmpNode = tmpNode._right
            
            if item <= lastNode._value:
                lastNode._left = thisNode
                thisNode._parent = lastNode
            else:
                lastNode._right = thisNode
                thisNode._parent = lastNode
            
            tmpNode = lastNode
            while tmpNode != None:
                if balanceFactor(tmpNode) == 2:
                    if balanceFactor(tmpNode._left) == 1:
                        rotateLeft(tmpNode._left)
                    elif balanceFactor(tmpNode._left) == -1:
                        rotateRight(tmpNode._left)
                        rotateLeft(tmpNode._left)
                elif balanceFactor(tmpNode) == -2:
                    if balanceFactor(tmpNode._right) == 1:
                        rotateLeft(tmpNode._right)
                        rotateRight(tmpNode._right)
                    elif balanceFactor(tmpNode._right) == -1:
                        rotateRight(tmpNode._right)
                if root._parent != None:
                    root = root._parent
                tmpNode = tmpNode._parent
        else:
            root = thisNode
    return root

def printTree(root):
    if root == None:
        print "None"
    else:
        print root._value
        printTree(root._left)
        printTree(root._right)


def main():
    data = getInput()
    rootOfTree = buildTree(data)
    print rootOfTree._value
    # printTree(rootOfTree)

if __name__ == "__main__":
    main()