def getLinkListInput():
    listMsg = raw_input()
    startId, num, step = listMsg.strip().split()
    num = int(num)
    step = int(step)
    dLinkList = dict()
    for dummy_i in xrange(num):
        thisInput = raw_input()
        thisAddress, thisValue, nextAddress = thisInput.strip().split()
        dLinkList[thisAddress] = {'address': thisAddress,
                                  'value': thisValue,
                                  'next': nextAddress}
    
    currentId = startId
    resList = list()
    while(currentId != '-1'):
        resList.append((dLinkList[currentId]['address'], 
                    dLinkList[currentId]['value']))
        currentId = dLinkList[currentId]['next']
    return resList, step

def reverseList(inputList, reverseStep):
    thisIdx = 0
    length = len(inputList)
    while(thisIdx + reverseStep <= length):
        start = thisIdx
        end = thisIdx + step - 1
        while(end > start):
            inputList[start], inputList[end] = inputList[end], inputList[start]
            start += 1
            end -= 1
        thisIdx += reverseStep

def printList(inputList):
    length = len(inputList)
    for idx in xrange(length):
        if idx != length - 1:
            print inputList[idx][0] + ' ' + inputList[idx][1] + ' ' +\
                  inputList[idx + 1][0]
        else:
            print inputList[idx][0] + ' ' + inputList[idx][1] + ' ' +\
                  '-1'    
if __name__ == '__main__':
    linkList, step = getLinkListInput()
    reverseList(linkList, step)
    printList(linkList)