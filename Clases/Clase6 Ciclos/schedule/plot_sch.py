from sys import argv
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
rc('text',usetex=True)


script, filename, nthr = argv 
nthr = int(nthr)

in_file = open(filename, "r")
data = list(map(int, in_file.read().split()))
in_file.close()

#print(data)


###plot---------------------------------
fig = plt.figure(figsize=(30,nthr+1), dpi=30)
ax0 = fig.add_subplot(111)

for i in range(len(data)):
    ax0.plot([0.1*i], [data[i]], marker='*', markersize=30, color='b')
ax0.set_ylim([-1,nthr])
plt.axis("off")

outf = filename.split('.')[0]+".pdf"
plt.savefig(outf)
plt.draw()

plt.show()
