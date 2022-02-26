from guesser import Guesser

class Animal:
	def __init__(self, name, attribs):
		self.name = name
		self.attribs = attribs

	def match(self, str):
		question = str.split(" ")
		if len(question) == 0 or len(question) > 2:
			raise Exception("", "")             
		val = question[-1] in self.attribs
		return val if len(question) == 1 else not val

	def get_diff(self, animal):
		for attr in self.attribs:
			if not attr in animal.attribs:
				return attr
		for attr in animal.attribs:
			if not attr in self.attribs:
				return "Not " + attr
		return None
		

def add_animal(guesser, animal, animals):
	while True:
		(type, str) = guesser.Request()
		if type == "question":
			if animal.match(str):
				guesser.Yes()
			else:
				guesser.No()
		else:
			if str == animal.name:
				guesser.Yes()
				return False
			else:                    
				for an in animals:
					if str == an.name:
						guesser.No()
						guesser.AddDef(animal.get_diff(an), animal.name)
						return True
				return False


def check_animal(guesser, animal, animals):
	while True:
		(type, str) = guesser.Request()
		if type == "question":
			if animal.match(str):
				guesser.Yes()
			else:
				guesser.No()
		else:
			if str == animal.name:
				guesser.Yes()
				return True
			else:                    
				for an in animals:
					if str == an.name:
						guesser.No()
						guesser.AddDef(animal.get_diff(an), animal.name)
						return False
				return False


animals = []
with open("../animals.txt", "r") as animalFile:
	for line in animalFile:
		if line:
			animalInfo = line.strip().split(" ")
			animals.append(Animal(animalInfo[0], animalInfo[1:]))

score = 0
guesser = Guesser(animals[0].name)
score += check_animal(guesser, animals[0], animals)

for i in range(1, 11):
	add_animal(guesser, animals[i], animals)

score += check_animal(guesser, animals[0], animals)
score += check_animal(guesser, animals[8], animals)
score += check_animal(guesser, animals[5], animals)

for i in range(11, len(animals)):
	add_animal(guesser, animals[i], animals)

score += check_animal(guesser, animals[0], animals)
score += check_animal(guesser, animals[8], animals)
score += check_animal(guesser, animals[86], animals)
score += check_animal(guesser, animals[51], animals)
score += check_animal(guesser, animals[16], animals)
score += check_animal(guesser, animals[43], animals)

print(score)