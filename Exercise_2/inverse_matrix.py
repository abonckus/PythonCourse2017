import numpy as np

print('Enter n:')
n = int(input());

a = np.random.rand(n,n)
print('\nGenerated matrix:')
print(a.reshape(n,n))

a = np.linalg.inv(a)
print('\nInverse matrix:')
print(a.reshape(n,n))