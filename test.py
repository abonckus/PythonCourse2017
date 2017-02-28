import myextension as ex

n = int(input())

if ex.isprime(n):
	print(str(n)+' is not prime.')
else:
	print(str(n)+' is prime.')

person = ex.Person()

person.firstName = "Vardas"
person.lastName = "Pavarde"

print(person.fullName())
