#include <random>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
 
double rand_gen(){ //genreates random number in [0,1)
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1.0);
    return dis(gen);
}

int* matrix_gen(int N, double px, double pc){ //generates matrix
    int* matrix = new int [N * N];
    for(int i = 0; i < N; i++){ //initializing matrix
        int y = -1;
        if(rand_gen() < px){
            y = 1; //Dale's Principle
        }
        for(int j = 0; j < N; j++){
            if(rand_gen() < pc){
                matrix[i * N + j] = y;
            }
            else{
                matrix[i * N * j] = 0;
            }
        }
    }
    return matrix;
}

int* vector_gen(int N){ //generates vector (need to check every possibility for actual runs)
    int* vect = new int [N];
    double pf = rand_gen();
    for(int i = 0; i < N; i++){
        if(rand_gen() < pf){
            vect[i] = 1;
        }
        else{
            vect[i] = 0;
        }
    }
    return vect;
}

// void print_digit(int num){ //prints out a digit
//     if(num < 10 && num >= 0){
//         cout << " " << num;
//     }
//     else{
//         cout << num;
//     }
// }

// void check_matrix(int* matrix, int N){ //prints out a matrix
//     cout << endl << "Matrix" << endl << "    ";
//     for(int i = 0; i < N; i++){
//         print_digit(i);
//         cout << " ";
//     }
//     cout << endl << endl;
//     for(int i = 0; i < N; i++){
//         print_digit(i);
//         cout << "| ";
//         for(int j = 0 ; j < N; j++){
//             print_digit(matrix[i * N + j]);
//             cout << " ";
//         }
//         cout << endl;
//     }
// }

// void check_vector(int* vector, int N){ //prints out a vector
//     cout << endl << "Vector" << endl;
//     for(int i = 0; i < N; i++){
//         print_digit(i);
//         cout << " ";
//     }
//     cout << endl;
//     for(int i = 0; i < N; i++){
//         print_digit(vector[i]);
//         cout << " ";
//     }
//     cout << endl;
// }

int main(){
    /********** Parameters **********/
    int N = 25; //number of nodes
    double px = 0.5; //probability of excitatory connection
    double pc = 0.5; //probability of connection
    int dur = 100; //time steps
    int reps = 10; //number of repetitions

    /********** Initialization **********/
    int* matrix = matrix_gen(N, px, pc);
    ofstream results; //record results in txt
    results.open("results.txt");

    /********** Simulation **********/
    for(int a = 0; a < reps; a++){ //repetition of runs
        int* vect = vector_gen(N); //initial vector
        int* vect_next = new int [N]; //empty vector to store results
        int r = 0; //used to store sum in matrix multiplication
        vector<int> x_spikes, y_spikes, active, highest_active;
        for(int t = 0; t < dur; t++){ //duration of one run
            /* generate new vect */
            for(int i = 0; i < N; i++){
                for(int j = 0 ; j < N; j++){
                    r += vect[j] * matrix[j * N + i];
                }
                if(r >= 0){
                    vect_next[i] = 1;
                    x_spikes.push_back(t); //record time t;
                    y_spikes.push_back(i); //record the active neuron at time t;
                    active.push_back(i); //record the active neurons into a vector
                }
                else{
                    vect_next[i] = 0;
                }
                r = 0; //clear r
            }
            if(t >= 50 && active.size() > highest_active.size()){
                highest_active = active; //the longest active neuron
            }
            active.clear(); //clear the active neuron vector
            /* replace new vect */
            for(int i = 0; i < N; i++){
                vect[i] = vect_next[i];
            }
        }
        /* output results */
        for(int i = 0; i < x_spikes.size(); i++){
            results << x_spikes[i] << " ";
        }
        results << "\n";
        for(int i = 0; i < y_spikes.size(); i++){
            results << y_spikes[i] << " ";
        }
        results << "\n";
        x_spikes.clear();
        y_spikes.clear();
    }
    results.close();
}