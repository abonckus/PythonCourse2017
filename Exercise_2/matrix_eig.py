import numpy as np

print('Enter n:')
N = int(input())

A = np.random.randint(0, 2*N, N**2).reshape(N, N)
print('\nGenerated matrix:')
print(A)

e_vals, e_vecs = np.linalg.eig(A)
print('Matrix eigenvalues:')
print(e_vals)

print('Matrix eigenvectors:')
print(e_vecs)
