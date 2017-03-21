import numpy as np

print('Enter n > 0:')
n = int(input())

array = np.array([1, 2, 3])

print(np.tile(array, 3*n).reshape(3*n, len(array)))

