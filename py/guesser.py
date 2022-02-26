"""
����� ��� ���� "������ ��������".
"""
class Guesser:            
	def __init__(self, initialAnimal):
		"""
		�����������. �������� ������ ��������, ������� ����� �������.
		"""
		pass

	def Request(self):
		"""
		����� ��������� �������� ������� �������. ����� ���� ������ ��������� ��� ������ �� ��������� ������.
		������� ����� ���� ���� �����:
			1. ("question", <������ � ��������, ��� �� ��� ����� � �������>);
			2. ("animal", <������ � ��������, ��� ��� ���� ������� � �������>).
		"""
		pass

	def Yes(self):
		"""
		�� ������� ������ ������� ����� "��".
		���� Request() ���������� ������ � "animal", �� ��������� ������.
		"""
		pass

	def No(self):
		"""
		�� ������� ������ ������� ����� "���".
		"""
		pass

	def AddDef(self, question, animal):
		"""
		������ �����������, ���� ������� �� ������� ��������.
		��������� ������ � ��������. �������� �������� ������� "��" �� ������, � ������� "���" �������� ��������, ���������� Request().
		��������� ������.
		"""
		pass


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
