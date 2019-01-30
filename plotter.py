import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import sys
import re

color = ['blue', 'red', 'green', 'orange', 'black', 'purple', 'brown']
regx = ' |-|\n|\t'

if len(sys.argv) > 1:
    filename = sys.argv[1]
# f = open(filename)


# f = open('runs/prey_predator.txt')
# steps = []
# preys = []
# preds = []
# for line in f.readlines():
#     values = [int(x) for x in line.split() if x.isdigit()]
#     if len(values) == 3:
#         t, py, pd = values
#         steps.append(t)
#         preys.append(py)
#         preds.append(pd)
# plt.title('Phase Portrait')
# plt.xlabel('steps')
# plt.ylabel('p')
# plt.plot(steps, preys, color='b', label='prey')
# plt.plot(steps, preds, color='r', label='predator')
# plt.legend(loc='best')
# plt.show()



f = open(filename)
a = 0.1 * 1000
b = 0.1
h = 0.1 * 1000
k = 0.1
xs = []
ys = []
ts = []
for line in f.readlines():
    values = [int(x) for x in line.split() if x.isdigit()]
    if len(values) == 3:
        t, y, x = values
        xs.append(a*x-b*x*y)
        ys.append(-h*y+k*x*y)
# print(xs)
# print(ys)
plt.title('Phase Portrait')
plt.plot(xs[10:], ys[10:], color='black')
plt.show()
plt.savefig(filename[:-4]+".png")



# def get_lane_formation(name):
#     f = open(name)
#     ts = []
#     xs = []
#     for line in f.readlines():
#         if line[:4] == "Runn":
#             line = re.split(regx, line)
#             x = float(line[2])
#             xs.append(x)
#         if line[:4] == "lane":
#             line = re.split(regx, line)
#             x = int(line[1])
#             ts.append(x)
#     return [ts, xs]
# ts, xs = get_lane_formation('runs/lane_formation.txt')
# plt.plot(ts, xs, color='b', label='simple')
# ts, xs = get_lane_formation('runs/lane_formation_verlet.txt')
# plt.plot(ts, xs, color='r', label='verlet')
# plt.title('Lane Formation')
# plt.xlabel('Particles')
# plt.ylabel('Time (s)')
# plt.legend(loc='best')
# plt.savefig('runs/lane_formation.png')



# regx = ' |\n|\t'
# f = open('runs/ising.txt')
# ns = []
# ts = []
# ms = []
# hs = []
# es = []
# cs = []
# k = -1
# for line in f.readlines():
#     if line[:4] == "N_sp":
#         print(line)
#         line = re.split(regx, line)
#         x = int(line[2])
#         ns.append(x)
#         k += 1
#         ts.append([])
#         ms.append([])
#         hs.append([])
#         es.append([])
#         cs.append([])
#     if line[0] in "1234567890":
#         line = re.split(regx,line)
#         t, m, h, e, c = [float(x) for x in line if len(x)>1]
#         ts[k].append(t)
#         ms[k].append(m)
#         hs[k].append(h)
#         es[k].append(e)
#         cs[k].append(c)
# for i in range(k+1):
#     plt.plot(ts[i], ms[i], color=color[i], label="N_spin = "+str(ns[i]))
# plt.title('Ising - Magnetization')
# plt.xlabel('Magnetization')
# plt.ylabel('Timestep')
# plt.legend(loc='best')
# plt.savefig('runs/ising-magnetization.png')
# plt.clf()
# for i in range(k+1):
#     plt.plot(ts[i], hs[i], color=color[i], label="N_spin = "+str(ns[i]))
# plt.title('Ising - chi')
# plt.xlabel('chi')
# plt.ylabel('Timestep')
# plt.legend(loc='best')
# plt.savefig('runs/ising-chi.png')
# plt.clf()
# for i in range(k+1):
#     plt.plot(ts[i], es[i], color=color[i], label="N_spin = "+str(ns[i]))
# plt.title('Ising - Energy')
# plt.xlabel('Energy')
# plt.ylabel('Timestep')
# plt.legend(loc='best')
# plt.savefig('runs/ising-energy.png')
# plt.clf()
# for i in range(k+1):
#     plt.plot(ts[i], cs[i], color=color[i], label="N_spin = "+str(ns[i]))
# plt.title('Ising - CV')
# plt.xlabel('CV')
# plt.ylabel('Timestep')
# plt.legend(loc='best')
# plt.savefig('runs/ising-cv.png')
# plt.clf()



# f = open('runs/percolation.txt')
# Ns = []
# Ps = []
# ps = []
# cs = []
# ms = []
# k = -1
# for line in f.readlines():
#     print(line)
#     if line[:4] == "perc":
#         line = re.split(regx, line)
#         x = int(line[1])
#         Ns.append(x)
#         x = int(line[2])
#         Ps.append(x/100)
#         k += 1
#         ps.append([])
#         cs.append([])
#         ms.append([])
#     if line[0] in "0123456789":
#         line = re.split(regx,line)
#         p, c, m = [int(x) for x in line if len(x)>0]
#         ps[k].append(p)
#         cs[k].append(c)
#         ms[k].append(m)
# # for i in range(k):
# #     plt.plot(ps[i], cs[i], color=color[i], label="N_spin = "+str(Ps[i]))
# ps = [np.mean(x) for x in ps]
# cs = [np.mean(x) for x in cs]
# ms = [np.mean(x) for x in ms]
# plt.title('Percolation')
# plt.xlabel('Percent')
# plt.ylabel('Num Particles')
# plt.plot(Ps, ps, color='b')
# plt.savefig('runs/percolation-particles.png')
# plt.clf()
# plt.title('Percolation')
# plt.xlabel('Percent')
# plt.ylabel('Num Clusters')
# plt.plot(Ps, cs, color='b')
# plt.savefig('runs/percolation-clusters.png')
# plt.clf()
# plt.title('Percolation')
# plt.xlabel('Percent')
# plt.ylabel('Max Cluster Size')
# plt.plot(Ps, ms, color='b')
# plt.savefig('runs/percolation-maxsize.png')
# plt.clf()
# # plt.show()



# f = open('runs/dla_fractal.txt')
# Ps = []
# ts = []
# ps = []
# gs = []
# k = -1
# for line in f.readlines():
#     if line[:3] == "dla":
#         line = re.split(regx, line)
#         x = int(line[1])
#         Ps.append(x/100)
#         k += 1
#         ts.append([])
#         ps.append([])
#         gs.append([])
#     if line[0] in "0123456789":
#         line = re.split(regx,line)
#         p, c, m = [float(x) for x in line if len(x)>0]
#         ts[k].append(int(p))
#         ps[k].append(int(c))
#         gs[k].append(m)
# for i in range(k+1):
#     plt.plot(ts[i], ps[i], color=color[i], label="stick_prob = "+str(Ps[i]))
# plt.title('DLACrystal')
# plt.xlabel('Particles')
# plt.ylabel('Timestep')
# plt.legend(loc='best')
# plt.savefig('runs/dla_fractal-particles.png')
# plt.clf()
# for i in range(k+1):
#     plt.plot(ts[i], gs[i], color=color[i], label="stick_prob = "+str(Ps[i]))
# plt.title('DLACrystal')
# plt.xlabel('Gyration')
# plt.ylabel('Timestep')
# plt.legend(loc='best')
# plt.savefig('runs/dla_fractal-gyration.png')
# plt.clf()



# # f = open('runs/network/network-n100-l2000.txt')
# # f = open('runs/network/network-rand-n100-l2000.txt')
# Ps = []
# ts = []
# ps = []
# k = -1
# for line in f.readlines():
#     if line[:5] == "GRAPH":
#         break
#     if line[0] in "0123456789":
#         line = re.split(regx,line)
#         t, p = [int(x) for x in line if len(x)>0]
#         ts.append(t)
#         ps.append(p)
# plt.plot(ts, ps, color='b')
# plt.title('Network')
# plt.xlabel('Nodes')
# plt.ylabel('Links per Node')
# # plt.show()
# plt.savefig(filename[:-4]+".png")


