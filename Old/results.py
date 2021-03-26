import numpy as np
from matplotlib import pyplot as plt

with open('results_good.txt') as f:
    results = f.readlines()
f.close()

i = 0
while i < len(results)-1:
    x_spikes = results[i].split()
    x_spikes = list(map(int, x_spikes))
    y_spikes = results[i+1].split()
    y_spikes = list(map(int, y_spikes))
    i = i + 2
    plt.scatter(x_spikes,y_spikes)
    # # plt.plot(x_freq,y_freq,color="red")
    plt.show()