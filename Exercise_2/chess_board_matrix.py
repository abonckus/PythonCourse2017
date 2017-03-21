import numpy as np

a = np.zeros(64).reshape(8,8)
a[1::2,::2] = 1
a[::2,1::2] = 1

print(a)
