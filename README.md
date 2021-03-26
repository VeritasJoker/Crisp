# Simple Neural Network

## Files

#### Old Models (Python)
* **1.py**
    * inputs: *None*
    * parameters: *N, probability of connection, timesteps*
    * outputs: *a graph that shows the end cylce of a random vector*

* **2.py**
    * new parameters: *number of trials*
    * new: *new random vector for each trial, cleaner code for each trial*
    * new outputs: *categorization of unique, transient, and repeating vectors for all vectors in all trials*

* **2_1.py**
    * new: *cleaner code for each trial*
\
#### Old Models (C++)
* **1.cpp**
    * new: *C++ version of 1.py*
    * new outputs: *(to txt) [timesteps, on neuron] coordinates for graphing*

* **2.cpp**
    * new: *clearner code*

* **results.py**
    * inputs: *(from txt) [timesteps, on neuron] coordinates for graphing*
    * outputs: *a graph that shows the desired end cycle of a random vector*
\
#### Used Models
* **3.cpp**
    * new: *categorizes all possible random vector given a random matrix*
    * new outputs: *id (biggest vector in the cycle) and population (number of vectors that go into 
    the cycle) for all cycles*

* **4.cpp**
    * new: *calculates the distance of each vector to its cycle
    * unique outputs: *(to txt 1) id and population for all cycles*
    *(to txt 2) distance of each vector to its cycle*




bifiltration.py\
input: degree and distance\
parameters: number of points\
output: distance matrix, sorted distance matrix, a graph of the rips complex\
(Enter a negative degree and distance to quit)

\
bifiltration2.py\
input: none\
parameters: number of points\
output: distance matrix. sorted edge lengths, sorted distance matrix, a graph of rips complexes at all critical points

\
bifiltration3.py\
input: none\
parameters: number of points\
output: distance matrix, sorted edge lengths, edge dictionary, sorted distance matrix, sorted edge matrix, the distribution of number of critical points, a graph of the distribution

\
bifiltration4.py\
input: none\
parameters: number of points, number of trials\
output: (to csv) distribution of the number of critical-bigrades for edges

\
bifiltration5.py\
input: none\
parameters: number of points\
output: (to console) connectivity matrix for all critial-bigrades

\
bifiltration6.py\
input: none\
parameters: number of points, number of trials\
output: (to csv and txt) connectivity matrix, sum of connectivity matrix
