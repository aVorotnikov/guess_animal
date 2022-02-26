import math
from random import shuffle

numOfAnimals = 90
numOfAttribs = math.floor(math.log2(numOfAnimals - 1)) + 1

attrib = []

for i in range(0, numOfAttribs):	
	attrib.append("attrib" + str(i + 1))

with open("attribs.txt", "w") as attrFile:
	for i in range(0, numOfAttribs):	
		attrFile.write(attrib[i] + "\n")

num = []
for i in range(0, numOfAnimals):	
	num.append(i)
shuffle(num)

with open("animals.txt", "w") as animalFile:
	for i in range(0, numOfAnimals):	
		animalFile.write("animal" + str(i + 1) + "")
		val = num[i]       
		for j in range(0, numOfAttribs):
			if val % 2 == 1:
				animalFile.write(" " + attrib[j])
			val //= 2
		animalFile.write("\n")
