import myextension as ex

n = int(input())

try:
	if ex.isprime(n):
		print(str(n)+' is not prime.')
	else:
		print(str(n)+' is prime.')
except ex.error:
	print(str(n) + ' is not valid!')

person = ex.Person()

person.firstName = "Vardas"
person.lastName = "Pavarde"

print(person.fullName())
