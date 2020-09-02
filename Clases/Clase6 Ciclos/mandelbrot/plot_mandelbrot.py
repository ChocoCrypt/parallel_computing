import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
rc('text',usetex=True)



A = []

In = open("mandelbrot.dat", "r")
for line in In:
    v = list(map(int, line.split()))
    A.append(v);
In.close()
A = np.matrix(A);

fig = plt.figure(figsize=(30,23), dpi=30)
ax0 = fig.add_subplot(111)

ax0.matshow(A)

plt.show()
