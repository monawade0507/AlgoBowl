class subset:
	def __init__(self, weight, itemSet, size, setNum):
		self.weight = weight
		self.itemSet = itemSet
		self.size = size
		self.setNum = setNum


def findCover(base, arr):
	uniq = [] #array that can be union
	uni = []  #array has been unionized w/ base
	if len(base.itemSet) == rangeOfVal:
		# print("COVER:", base.itemSet)
		return base
	remain = rangeOfVal
	# Search through arr to find all potential subsets
	for i in arr:
		# print("compare: ", i.itemSet)
		if base.itemSet.isdisjoint(i.itemSet) == True:
			# Unique array
			uniq.append(i)
			remain = remain - len(i.itemSet)
			# print("uniq: ", len(uniq))
			addedSub = subset(base.weight + i.weight,
							base.itemSet.union(i.itemSet),
							base.size + i.size,
							str(base.setNum) + " " + str(i.setNum))
			# Union array
			uni.append(addedSub)
			print("added:", addedSub.itemSet)
			if addedSub.size == rangeOfVal:
				# print("COVER:", addedSub.itemSet)
				return addedSub
	print()
	for j in uni:
		# print(j.setNum)
		if remain == len(base.itemSet):
			findCover(j, uniq)
	# print("_____________________________NONE_______________________________")		 
	return



# fileName="./inputs/input_group115.txt"
fileName="Input_attempt3.txt"
f=open(fileName, "r")

rangeOfVal=int(f.readline())  # n
numOfSub=int(f.readline())  # m
num=0
minWeight=500001
minCover=[]
subsetList=[]
# Loop to read through file and set up the data structures
# to hold all the values
while True:
	itemSet=f.readline()
	if itemSet == "":
		break
	else:
		weight=int(f.readline())
		arrItems=itemSet.split(" ")
		i=0
		# Convert each item into an int and delete any \n
		for item in arrItems:
			if item != "\n":
				arrItems[i]=int(item)
				i += 1
			else:
				arrItems.remove("\n")
		arrItems.sort()
		s=subset(weight, set(arrItems), len(arrItems), num)
		subsetList.append(s)
	num += 1

# print("---------------------------------------------")
# for s in subsetList:
# 	print(s.itemSet)
# print("---------------------------------------------")

covers = []
inc = 1
for base in subsetList:
	# print()
	print("base:", base.setNum)
	o = findCover(base, subsetList[inc:len(subsetList)])
	if o != None:
		print("here!")
		covers.append(o)
		# print(o.setNum)
	inc += 1
for w in covers:
	if w.weight < minWeight:
		minWeight = w.weight
		# if type(s.setNum) == int: continue
		# else: minCover = (s.setNum).split(" ").sort()
		minCover = w.setNum

print(minWeight)
print(minCover)


# for cov in covers:
# 	print(cov.itemSet)

# # 
