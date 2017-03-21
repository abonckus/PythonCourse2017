import scipy.misc as sc

def f(x):
    return x**2 + x

print('Derivative of function x^2 + x = ' + str(sc.derivative(f, 1.0, dx=1e-6)))