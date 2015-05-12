class FixStack:

    def __init__(self, fullNum):
        self._num = fullNum
        self._data = list()
    
    def isFull(self):
        return len(self._data) > self._num

    def isEmpty(self):
        return len(self._data) == 0

    def push(self, item):
        self._data.append(item)

    def pop(self):
        if len(self._data) <= 0:
            # print "the stack is empty\n"
            return
        else:
            return self._data.pop()


def startPop(seq, idx):
    if idx == 0 or seq[idx] > seq[idx - 1]:
        return True
    return False

def stopPop(seq, idx, length):
    if idx == length - 1 or seq[idx] < seq[idx + 1]:
        return True
    return False

def popSeqSimu(seq, length, cap):
    simuStack = FixStack(cap)
    pushNum = 1
    popNum = None
    popRes = list()
    for idx in xrange(length):
        if startPop(seq, idx):
            while pushNum <= seq[idx]:
                simuStack.push(pushNum)
                if simuStack.isFull():
                    #print "Out of capacity"
                    return False
                pushNum += 1
        if stopPop(seq, idx, length):
            while True:
                popNum = simuStack.pop()
                popRes.append(popNum)
                if popNum <= seq[idx] or simuStack.isEmpty():
                    break
    # assert len(popRes) == length, "Error, the simu pop seq is not the same length"
    # print "the initial sequence is: ", seq
    # print "the simulation sequence is: ", popRes
    return popRes == seq

def getInput():
    config = raw_input()
    config = config.strip().split()
    config = map(int, config)
    capacity = config[0]
    length = config[1]
    seqNum = config[2]
    seqList = list()
    for dummy_i in xrange(seqNum):
        thisSeq = raw_input()
        thisSeq = thisSeq.strip().split()
        thisSeq = map(int, thisSeq)
        seqList.append(thisSeq)
    return seqList, capacity, length, seqNum

if __name__ == "__main__":
    seqList, cap, length, seqNum = getInput()
    for idx in xrange(seqNum):
        # print "Loop", idx + 1
        thisSeq = seqList[idx]
        if popSeqSimu(thisSeq, length, cap):
            print "YES"
        else:
            print "NO"
        # print "\n"
                