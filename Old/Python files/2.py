import random as rd
import numpy as np
from matplotlib import pyplot as plt

m = [] # matrix of edges (connection weights)
N = 25 # number of nodes
px = 0.5 # probability of excitatory connection
pc = 0.5 # probability of connection
#pf = 0.5 # probability a node is active at time = 0
dur = 100 # time steps
reps = 1

unique_patterns = [] # these are unique states of activity, that repeat or persist over time
transients = [] # these are states that don't repeat, but eventually give rise to repeating states
regen = [] # these are states that regenerate, ie play a role in repetetitive patterns

# initialize matrix, starting vector
for i in range(N):
    y, row = -1, []
    if rd.random() < px:
        y = -y # Dale's Principle
    for j in range(N):
        z = 0
        if rd.random() < pc:
            z = y
        row.append(z)
    m.append(row)
print(m)

for a in range(reps):
    v = [] # vector of node states (binary)
    pf = rd.random()
    for i in range(N):
        y = 0
        if rd.random() < pf:
            y = 1
        v.append(y)
    print(v)
    # simulation: 1 run of DUR time steps from a single starting vector (out of 2^N possible start vectors)
    x_spike ,y_spike, x_freq, y_freq = [],[],[],[]
    uniques, repeats = [], []
    for t in range(dur):
        v_next = []
        #ex, ih = 0,0
        for i in range(N):
            r = 0
            for j in range(N):
                r += v[j]*m[j][i]
            if r >= 0: 
                v_next.append(1)
                x_spike.append(t)
                y_spike.append(i)
            else: v_next.append(0)
        #counts.append(sum(v))
    
        if v not in uniques:
            uniques.append(v)
        else: 
            if v not in repeats: 
                repeats.append(v)
                x_freq.append(t)
                y_freq.append(sum(v))
        v = v_next
    
    # top graph:
    # black dots are a raster plot showing spikes in each of N nerve cells (y axis) as a function of time (x axis)
    # blue line is a plot of network firing frequency versus time
    # bottom graph (red line) is a plot of the distribution of network firing rates

    #Plotting
    plt.scatter(x_spike,y_spike)
    plt.plot(x_freq,y_freq,color="red")
    plt.show()

    tmp = []
    for i in repeats:
        x = 0
        for j in range(N): x += 2*x + i[j]
        tmp.append(x)
    tmp.sort()
    
    if tmp not in unique_patterns: unique_patterns.append(tmp)
    
    for i in uniques:
        if i not in repeats: transients.append(i)
    
    for i in repeats:
        if i not in regen: regen.append(i)
    
p = len(unique_patterns)
t = len(transients)
r = len(regen)
tot = t+r

print("total number of unique repeating patterns = ",p)
print("total number of transient vectors = ",t,"...",t/tot*100,"%")
print("total number of regenerative vectors (in repeating vectors)= ",r,"...",r/tot*100,"%")
print("total number of unique vectors observed = ",tot)

        
    