import numpy as np

a = np.random.rand(3,5)

print('Array sum:')
print(a.sum())

print('\nColumn sum:')
print(a.sum(axis=0))

print('\nRow sum:')
print(a.sum(axis=1))
