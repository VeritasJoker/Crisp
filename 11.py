import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

num = 25 # number of nodes
adj_mat = np.loadtxt("py_matrix_25.txt") # adjacency matrix

# build color map for nodes
v_color = [] # color map for nodes
for i in range(0,25):
    if -1 in adj_mat[i]:
        v_color.append("red") # inhib nodes
    else:
        v_color.append("blue") # exciting nodes

# build graph
G = nx.from_numpy_matrix(adj_mat, create_using = nx.DiGraph, parallel_edges = False) # create graph

# build color map for edges
e_weights = list(nx.get_edge_attributes(G,"weight").values()) # get the weights
e_color = []
for i in e_weights:
    if i == -1:
        e_color.append("red")
    else:
        e_color.append("blue")

# circ_pos = nx.circular_layout(G)
spring_pos = nx.spring_layout(G) # force directed layout
nx.draw(G, with_labels = True, node_color = v_color, edge_color = e_color, pos = spring_pos)
plt.show()

# Cycles for the graph
# cycles = nx.simple_cycles(G_0)
# print(len(cycles))
# print(cycles)


# ##### Page Rank for the redacted graph #####
# adj_mat_pos = adj_mat # adjacency matrix without netgative links
# adj_mat_pos[adj_mat_pos == -1] = 0 # change all -1 to 0
# G_r = nx.from_numpy_matrix(adj_mat_pos, create_using = nx.DiGraph, parallel_edges = False) # create graph
# # nx.draw(G_r, with_labels = True)
# # plt.show()
# pr_r = nx.pagerank(G_r, alpha = 0.85)

# for node in sorted(pr_r, key = pr_r.get):
#     print(node, pr_r[node])
# print("\n\n\n")

# ##### Page Rank for the reverse graph #####
# adj_mat_pos_t = np.transpose(adj_mat_pos) # transpose of adjacency matrix without negative links
# G_t = nx.from_numpy_matrix(adj_mat_pos_t, create_using = nx.DiGraph, parallel_edges = False) # create graph
# nx.draw(G_t, with_labels = True)
# plt.show()
# pr_t = nx.pagerank(G_t, alpha = 0.85)

# for node in sorted(pr_t, key = pr_t.get):
#     print(node, pr_t[node])