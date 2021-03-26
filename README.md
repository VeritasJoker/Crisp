# Simple Neural Network

## Definitions:
* **N:** number of neurons in the network
* **Categorization of a vector:**
    * if timestep given, calculates all previous states of the vector at given timestep
    * if not, calculates the final state or end cycle of the vector
* **Cycle:**
    * **id:** The biggest integer from all vectors in the cycle
    * **population:** The number of vectors that is categorized to the cycle)
    * **length:** number of unqiue vectors in the cycle\


## Models

#### Old Models (Python)
* **1.py**
    * inputs: *None*
    * parameters: *N, probability of connection, timestep*
    * outputs: *a graph that shows the categorization of a random vector in given timestep*

* **2.py**
    * new parameters: *number of trials*
    * new: *new random vector for each trial, cleaner code for each trial*
    * new outputs: *categorization of unique, transient, and repeating vectors for all vectors in all trials*

* **2_1.py**
    * new: *cleaner code for each trial*\

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
* **matrix.cpp**
    *outputs: (to txt) randomly generated adjacency matrix*

* **3.cpp**
    * new inputs: *(from txt) adjacency matrix*
    * new: *categorizes all possible random vector given a random matrix*
    * new outputs: *id and population for all cycles*

* **4.cpp**
    * new: *calculates the distance of each vector to its cycle*
    * unique outputs: *(to txt 1) id and population for all cycles    (to txt 2) distance of each vector to its cycle*

* **4+matrix.cpp**
    * unique: *combines 4.cpp and matrix.cpp*

* **5.cpp**
    * unique: *given a set matrix, apply noise with probability to one trial given a random starting vector*
    * unique outputs: *transition matrix between cycles*

* **6.cpp**
    * unique: *noise is randomized*

* **7.cpp**
    * new outputs: *(to txt 1) id and population for all cycles    (to txt 2) categorization of all vectors*


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
