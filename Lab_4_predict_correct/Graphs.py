import matplotlib.pyplot as plt
import numpy as np


plt.figure(figsize=(20,14))
plt.grid(True)

t1, phi1, vel1 = np.loadtxt('Eiler_sol_1.txt', unpack = True)
plt.plot(phi1, vel1)

t1, phi1, vel1 = np.loadtxt('Eiler_sol_1_5.txt', unpack = True)
plt.plot(phi1, vel1)

t1, phi1, vel1 = np.loadtxt('Eiler_sol_1_6.txt', unpack = True)
plt.plot(phi1, vel1)

t1, phi1, vel1 = np.loadtxt('Eiler_sol_2.txt', unpack = True)
plt.plot(phi1, vel1)

t1, phi1, vel1 = np.loadtxt('Eiler_sol_2_3.txt', unpack = True)
plt.plot(phi1, vel1)

plt.title(r'$Зависимость \: vel \: от \: \phi (Eiler)$', size = 20)
plt.xlabel(r'$\phi$', fontsize = 16)
plt.ylabel(r'vel', fontsize = 16)
plt.savefig('Eiler.png')
plt.show()

plt.figure(figsize=(20,14))
plt.grid(True)

t2, phi2, vel2 = np.loadtxt('Khoin_sol_1.txt', unpack = True)
plt.plot(phi2, vel2)

t2, phi2, vel2 = np.loadtxt('Khoin_sol_1_5.txt', unpack = True)
plt.plot(phi2, vel2)

t2, phi2, vel2 = np.loadtxt('Khoin_sol_1_5.txt', unpack = True)
plt.plot(phi2, vel2)

t2, phi2, vel2 = np.loadtxt('Khoin_sol_1_6.txt', unpack = True)
plt.plot(phi2, vel2)

t2, phi2, vel2 = np.loadtxt('Khoin_sol_2.txt', unpack = True)
plt.plot(phi2, vel2)

t2, phi2, vel2 = np.loadtxt('Khoin_sol_2_3.txt', unpack = True)
plt.plot(phi2, vel2)

plt.title(r'$Зависимость \: vel \: от \: \phi (Khoin)$', size = 20)
plt.xlabel(r'$\phi$', fontsize = 16)
plt.ylabel(r'vel', fontsize = 16)
plt.savefig('Khoin.png')
plt.show()