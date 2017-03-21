from sympy import *

x = Symbol('x')
I = integrate(x**2 + x**3, (x, 0, 1))
print('Definite integral of function x**2 + x**3 = ' + str(I))

I = integrate(x**2 + x**3, x)
print('Indefinite integral of function x**2 + x**3 = ' + str(I))