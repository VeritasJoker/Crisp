import random as rd
import numpy as np

m = [] # matrix of edges (connection weights)
v = [] # vector of node states (binary)
N = 25 # number of nodes
px = 0.5 # probability of excitatory connection
pc = 0.5 # probability of connection
pf = 0.5 # probability a node is active at time = 0
dur = 250 # time steps

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
    y = 0
    if rd.random() < pf:
        y = 1
    v.append(y)

# simulation: 1 run of DUR time steps from a single starting vector (out of 2^N possible start vectors)
spikes, states = [],[]
uniques, repeats = [],[] # uniques is a set of all states, repeats is a set of states that occur more than once
for t in range(dur):
    v_next = []
    for i in range(N):
        r = 0
        for j in range(N):
            r += v[j]*m[j][i]
        if r >= 0: 
            v_next.append(1)
            spikes.append([t,i])
        else: v_next.append(0)
    v = v_next
    x = 0
    for i in range(N):
        x += v[i]*(2**i)
    states.append([t,x])
    if x not in uniques: uniques.append(x)
    if x in uniques:
        if x not in repeats: repeats.append(x)

print(spikes)
print(states)

# graphs
# top (black dots) is a raster plot showing spikes in each of N nerve cells (y axis) as a function of time (x axis)
# lower middle graph (blue line) is a plot of states (vector->integer) of network over time
# bottom graph (red line) is a plot of state at time t+1 as a function of state at time t for the repeating (non-unique) vector states
# g = graph()
# sp = gdots(color = color.black)
# sp.plot(spikes) # raster plot
# g = graph()
# st = series(color = color.blue)
# st.plot(states) # state versus time
# x,z = repeats[len(repeats)-1],[]
# for i in range(len(repeats)):
#     y = repeats[i]
#     z.append([x,y])
#     x = y
# z.append([x,repeats[0]])
# g = graph()
# p = series(color = color.red)
# p.plot(z) # state t+1 as a function of state t
    
    
    