import numpy as np

a = np.zeros(100).reshape(10, 10)
a[0, :] = 1
a[:, 0] = 1
a[:, -1] = 1
a[-1 ,:] = 1

print(a)
