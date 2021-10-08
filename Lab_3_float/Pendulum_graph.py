import matplotlib.pyplot as plt
import numpy as np

t1, phi1, vel1, energy1 = np.loadtxt('data_first_sol.txt', unpack = True)
t2, phi2, vel2, energy2 = np.loadtxt('data_second_sol.txt', unpack = True)


plt.figure(figsize=(10,7))
plt.grid(True)
plt.plot(vel1, phi1)
plt.title(r'$Зависимость \: \phi_1 \: от \: vel_1 \: при \: dt=10^{-7}$', size = 20)
plt.xlabel(r'vel', fontsize = 16)
plt.ylabel(r'phi', fontsize = 16)
plt.savefig('phi_vel_1_10-7.png')
plt.show()


plt.figure(figsize=(10,7))
plt.grid(True)
plt.plot(t1, energy1)
plt.title(r'$Зависимость  \: energy1 \: от \: t \: при \: dt=10^{-7}$', size = 20)
plt.xlabel(r't', fontsize = 16)
plt.ylabel(r'phi', fontsize = 16)
plt.savefig('energy_t_1_10-7.png')
plt.show()


#second part


plt.figure(figsize=(10,7))
plt.grid(True)
plt.plot(vel2, phi2)
plt.title(r'$Зависимость \: \phi_2 \: от \: vel_2 \: при \: dt=10^{-7}$', size = 20)
plt.xlabel(r'vel', fontsize = 16)
plt.ylabel(r'phi', fontsize = 16)
plt.savefig('phi_vel_2_10-7.png')
plt.show()


plt.figure(figsize=(10,7))
plt.grid(True)
plt.plot(t2, energy2)
plt.title(r'$Зависимость  \: energy_2 \: от \: t \: при \: dt=10^{-7}$', size = 20)
plt.xlabel(r't', fontsize = 16)
plt.ylabel(r'phi', fontsize = 16)
plt.savefig('energy_t_2_10-7.png')
plt.show()


