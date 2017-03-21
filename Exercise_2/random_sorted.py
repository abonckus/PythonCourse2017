import numpy as np

a = np.random.rand(5, 5)
print(a.reshape(5,5))
a = a[a[:, 1].argsort()]

print(a.reshape(5, 5))
