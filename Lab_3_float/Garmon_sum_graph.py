import matplotlib.pyplot as plt
import numpy as np

x1, x2, direct_sum, indirect_sum = np.loadtxt('./data_garmon_sum.txt', unpack = True)

plt.figure(figsize=(15,10))
plt.grid(True)
plt.plot(x1, direct_sum)
plt.title(r'$Direct sum 1/x$', size = 20)
plt.xlabel(r'x', fontsize = 16)
plt.ylabel(r'sum', fontsize = 16)
plt.savefig('Direct_sum.png')
plt.show()

plt.figure(figsize=(15,10))
plt.grid(True)
plt.plot(x1, indirect_sum)
plt.title(r'$Indirect sum 1/x$', size = 20)
plt.xlabel(r'x', fontsize = 16)
plt.ylabel(r'sum', fontsize = 16)
plt.savefig('Indirect_sum.png')
plt.show()