# Simple Neural Network

## Definitions
* **N:** number of neurons in the network
* **Categorization of a vector:**
    * if timestep given, calculates all the states of the vector in given timestep
    * if not, calculates the final state or end cycle of the vector
* **Vectors:**
    * Number formt: 3
    * Bitset format: 0000000000000000000000011
    * Vector format: [23,24]
* **Cycle:**
    * **id:** The biggest vector (number format) in the cycle
    * **population:** The number of vectors that is categorized to the cycle
    * **length:** number of unqiue vectors in the cycle

## Models Overview
### Core Model
* 10_mod1.cpp
* 3.cpp

### Variation Models
* Permanently Excite or Inhibit a Neuron
    * 10_mod5.cpp
    * 10_mod3.cpp
    
* Random Walk
    * 9.cpp
    * 8.cpp
    * 7_mod2.cpp (not used)
    * 6.cpp (not used)
    * 5.cpp

* Detailed
    * 7_mod1.cpp (categorization)
    * 4+matrix.cpp (distance)
    * 4 (distance)

### Helpers
* 11.py
* 10_mod6.cpp
* 10_mod4.cpp
* 10_mod2.cpp
* matrix.cpp
* results.py

### Old Models
* 2.cpp
* 2_1.py
* 2.py
* 1.cpp
* 1.py


# Models Detailed

## Old Models
* **1.py**
    * inputs: *None*
    * parameters: *N, probability of connection, timestep*
    * outputs: *a graph that shows the categorization of a random vector in given timestep*

* **2.py**
    * new parameters: *number of trials*
    * new: *new random vector for each trial, cleaner code for each trial*
    * new outputs: *categorization of unique, transient, and repeating vectors for all vectors in all trials*

* **2_1.py**
    * new: *cleaner code for each trial*

* **1.cpp**
    * new: *C++ version of 1.py*
    * new outputs: *(to txt) [timesteps, on neuron] coordinates for graphing*

* **2.cpp**
    * new: *clearner code*

## Models
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

* **6.cpp (not used)**
    * unique: *noise is randomized*

* **7_mod1.cpp**
    * new outputs: *(to txt 1) id and population for all cycles    (to txt 2) categorization of all vectors*

* **7_mod2.cpp (not used)**
    * unique inputs: *(from txt 1) id and population for all cycles    (from txt 2) categorization of all vectors*
    * unique: *apply noise (excite or inhibit a neuron) after reaching an end cycle*

* **8.cpp**
    * unique inputs: *(from txt 1) id and population for all cycles    (from txt 2) categorization of all vectors*
    * unique: *cleaner and faster code for 5.cpp, using bitsets*

* **9.cpp**
    * unique: *noise only happens after reaching an end cycle*

* **10.mod1.cpp**
    * same as 3.cpp

* **10_mod2.cpp**
    * new inputs: *(from txt 2) results from 10.mod1*
    * new: get all vectors in stable cycle and get common on neurons
    * new outputs: on neurons that are common in all vectors of a stable cycle for all stable cycles

* **10.mod3.cpp**
    * new parameters: *fixed neuron*
    * new: *same as 10.mod1 besides an always excited neuron*

* **10.mod4.cpp**
    * new: *same as 10.mod2 besides taking the always excited neuron into consideration*

* **10.mod5.cpp**
    * new parameters: *inhib neuron*
    * new: *same as 10.mod1 besides an always inhibited neuron*

* **10.mod6.cpp**
    * new: *same as 10.mod2 besides taking the always inhibited neuron into consideration*

* **11.py**
    * new: *explores the characteristics of the network graph*

## Helper Files
* **results.py**
    * inputs: *(from txt) [timesteps, on neuron] coordinates for graphing*
    * outputs: *a graph that shows the desired end cycle of a random vector*

* **matrix.cpp**
    * outputs: *(to txt) randomly generated adjacency matrix*