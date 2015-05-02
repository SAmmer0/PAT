class LinkList:
	def __init__(self, data, start, end):
		self._data = data
		self._start = start
		self._end = end
		self._count = len(data)
	
	def reverseLinkList(self):
		tmpData = dict()
		currentNode = self._end
		lastNode = None
		while True:
			tmpDict = {'address': currentNode,
						'value': self._data[currentNode]['value'],
						'last': lastNode,
						'next': self._data[currentNode]['last']}
			tmpData[currentNode] = tmpDict
			if currentNode == self._start:
				break
			lastNode = currentNode
			currentNode = self._data[currentNode]['last']
		self._data = tmpData
		self._start, self._end = self._end, self._start
	
	def joinLinkList(self, nextLinkList):
		self._data.update(nextLinkList.getData())
		self._data[self._end]['next'] = nextLinkList.getStart()
		self._end = nextLinkList.getEnd()
		self._count += nextLinkList.getCount()
	
	def getStart(self):
		return self._start
	
	def getEnd(self):
		return self._end
	
	def getData(self):
		return self._data
	
	def getCount(self):
		return self._count
	
	def printLinkList(self):
		currentNode = self._start
		data = self._data
		while True:
			print data[currentNode]['address'] + ' ' +\
				  data[currentNode]['value'] + ' ' +\
				  data[currentNode]['next'] + '\n '
		
		
def getInput():
	# get initial input message
	inputStr = raw_input()
	startNode, num, step = inputStr.strip().split()
	num = int(num)
	step = int(step)
	
	# convert input into link list
	linkList = dict()
	for dummy_i in xrange(num):
		thisInput = raw_input()
		thisInput = thisInput.strip().split()
		thisNode = {'address': thisInput[0], 'value': int(thisInput[1]), 'next': thisInput[2]}
		linkList[thisInput[0]] = thisNode
	
	
	
			