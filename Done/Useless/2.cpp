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

vector<int> rand_vector_gen(int N){ //generates vector randomly
    vector<int> vect;
    double pf = rand_gen();
    for(int i = 0; i < N; i++){
        if(rand_gen() < pf){
            vect.push_back(i);
        }
    }
    return vect;
}

unsigned long int num_gen(vector<int> vect, int N){ //converts states from an active neuron vetor to a number
    unsigned long int n = 0;
    for(int i = 0; i < vect.size(); i++){
        n += pow(2, N - 1 - vect[i]);
    }
    return n;
}

void print_digit(int num){ //prints out a digit
    if(num < 10 && num >= 0){
        cout << " " << num;
    }
    else{
        cout << num;
    }
}

void check_matrix(int* matrix, int N){ //prints out a matrix
    cout << endl << "Matrix" << endl << "    ";
    for(int i = 0; i < N; i++){
        print_digit(i);
        cout << " ";
    }
    cout << endl << endl;
    for(int i = 0; i < N; i++){
        print_digit(i);
        cout << "| ";
        for(int j = 0 ; j < N; j++){
            print_digit(matrix[i * N + j]);
            cout << " ";
        }
        cout << endl;
    }
}

void check_vector(vector<int> vector){ //prints out an active neuron vector
    cout << endl << "Vector" << endl;
    for(int i = 0; i < vector.size(); i++){
        cout << vector[i] << " ";
    }
    cout << endl;
}

int main(){
    /********** Parameters **********/
    int N = 25; //number of nodes
    double px = 0.5; //probability of excitatory connection
    double pc = 0.5; //probability of connection
    int dur = 100; //time steps
    int reps = 10; //number of repetitions

    /********** Initialization **********/
    int* matrix = matrix_gen(N, px, pc); //initialize matrix
    ofstream results; //record results in txt
    results.open("results.txt");

    /********** Simulation **********/
    for(unsigned long int a = 0; a < N; a++){ //run for every vector
        vector<int> vect = rand_vector_gen(N); //randomly initialize active neuron vector
        vector<int> vect_next; //empty vector to store results for the next active neuron vector
        unsigned long int y = num_gen(vect_next,N); //convert the active neuron into a number
        /* r: used in matrix multiplication
           x_highest: time when y_highest occurs
           y_highest: the decimal number for the vector with the most number of activated neurons */
        int r = 0, x_highest = 0, y_highest;
        x_highest = y;
        /* x_spikes: x values for the plot, represents time t
           y_spikes: y values for the plot, represents the neuron number that is active at t */
        vector<int> x_spikes, y_spikes;
        for(int t = 0; t < dur; t++){ //duration of one run
            /* generate new vect */
            for(int i = 0; i < N; i++){
                for(int j = 0 ; j < vect.size(); j++){
                    r += matrix[vect[j] * N + i];
                }
                if(r >= 0){
                    vect_next.push_back(i); //add the active neuron
                    x_spikes.push_back(t); //add time t;
                    y_spikes.push_back(i); //add the active neuron;
                }
                r = 0; //clear r
            }
            if(t >= 50 && vect_next.size() > highest_active.size()){
                highest_active = vect_next; //the longest active neuron
            }
            vect = vect_next;
            vect_next.clear(); //clear the active neuron vector
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

    delete [] visited;
}