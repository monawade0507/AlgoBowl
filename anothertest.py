class subset:
	def __init__(self, weight, itemSet, size, setNum):
		self.weight = weight
		self.itemSet = itemSet
		self.size = size
		self.setNum = setNum


def findCover(base, arr):
	uniq = []
	uni = []
	inc = 0
	if len(base.itemSet) == rangeOfVal:
		print("COVER:", base.itemSet)
		return base

	# Search through arr to find all potential subsets
	for i in arr:
		# print("compare: ", i.itemSet)
		if base.itemSet.isdisjoint(i.itemSet) == True:
			# Unique array
			uniq.append(i)
			# print("uniq: ", len(uniq))
			addedSub = subset(base.weight + i.weight,
							base.itemSet.union(i.itemSet),
							base.size + i.size,
							str(base.setNum) + " " + str(i.setNum))
			# Union array
			uni.append(addedSub)
			# print("added:", addedSub.itemSet)
			if addedSub.size == rangeOfVal:
				print("COVER:", addedSub.itemSet)
				return addedSub
			findCover(addedSub, uniq)
	# print("_____________________________NONE_______________________________")		 
	return



fileName="Input_attempt4.txt"
f=open(fileName, "r")

rangeOfVal=int(f.readline())  # n
numOfSub=int(f.readline())  # m
num=0
minWeight=1001
minCover=[]
subsetList=set()
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
		subsetList.add(s)
	num += 1

print("---------------------------------------------")
for s in subsetList:
	print(s.itemSet)
print("---------------------------------------------")

covers=[]
for base in subsetList:
	print()
	print("base:", base.itemSet)
	o = findCover(base, subsetList)
	if (o != None):
		print(o.setNum)


# for cov in covers:
# 	print(cov.itemSet)

# # 