import random as rd
import numpy as np
from matplotlib import pyplot as plt

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
m = np.empty([N,N], dtype=int) # empty N*N matrix
for i in range(N):
    y = 1 if np.random.random() < px else -1 # Dale's Principle (A number with values 1 or -1)
    m[i] = [y if np.random.random() < pc else 0 for i in range(N)] # N*N matrix (each row has values 0,1 or 0,-1)

for a in range(reps): # Loop for repetition
    v = np.random.randint(2,size = N) # random vector of node states (N array with values 0,1)
    x_freq, y_freq, x_spike, y_spike = [], [], [], [] # x,y axis for frequency and spikes
    uniques, repeats = [], []
    for t in range(dur): # Simulation: 1 run of DUR time steps from a single starting vector (out of 2^N possible start vectors)
        k = v.tolist()
        if k not in uniques:
            uniques.append(k)
        else: 
            if k not in repeats:
                repeats.append(k)
                x_freq.append(t)
                y_freq.append(sum(k))

        v_next = np.dot(m.transpose(),v) #the next v through matrix multiplication
        for i in range(N): # Renew v
            if v_next[i] >= 0:
                v[i] = 1 # 1 if the sum is over 0
                x_spike.append(t)
                y_spike.append(i) #record spike
            else:
                v[i] = 0 # 0 if the sum is negative
    
    # top graph:
    # black dots are a raster plot showing spikes in each of N nerve cells (y axis) as a function of time (x axis)
    # blue line is a plot of network firing frequency versus time
    # bottom graph (red line) is a plot of the distribution of network firing rates

    #Plotting
    plt.scatter(x_spike, y_spike) # scatter plot for spike
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