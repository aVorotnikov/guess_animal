class Guesser:
	class Question:
		def __init__(self, question, yesNode, noNode):
			self.question = question
			self.yes = yesNode
			self.no = noNode


	def __init__(self, initialAnimal):
		self.root = initialAnimal
		self.curNode = self.root
		self.father = None
		self.trace = ""

	def Request(self):
		if hasattr(self.curNode, "question"):
			return ("question", self.curNode.question)
		return ("animal", self.curNode)

	def Yes(self):
		self.father = self.curNode
		if hasattr(self.curNode, "yes"):
			self.curNode = self.curNode.yes
			self.trace = "yes"
		else:
			self.curNode = self.root

	def No(self):
		if hasattr(self.curNode, "no"):
			self.father = self.curNode
			self.curNode = self.curNode.no
			self.trace = "no"    		

	def AddDef(self, question, animal):
		newQuestion = Guesser.Question(question, animal, self.curNode)
		if hasattr(self.root, "question"):
			setattr(self.father, self.trace, newQuestion)
		else:                                      
			self.root = newQuestion
		self.father = self.curNode
		self.curNode = self.root


if __name__ == "__main__":
	guesser = Guesser(input("Input initial animal: "))
	while True:
		(type, question) = guesser.Request()
		print(question + "?")
		answer = input("[Y/N]")
		answer = answer.lower()
		if answer == "y" or answer == "yes":
			guesser.Yes()
			if (type == "animal"):
				print("Guessed")
		elif answer == "n" or answer == "no":
			guesser.No()
			if (type == "animal"):
				animal = input("Input new animal: ")
				question = input("Input new definition: ")
				guesser.AddDef(question, animal)
		elif answer == "":
			break
		else:
			print("Incorrect input")
