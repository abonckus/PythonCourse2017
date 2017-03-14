import numpy as np

print("Input n:")
n = int(input())

a = np.array([[i+j for i in range(n)] for j in range(n)]).reshape(n, n)

print(a)
