#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <algorithm>
using namespace std;

vector<int> vector_gen(long int state, int N){ //converts states from a number to an active neuron vector
    vector<int> vect;
    for(int i = 0; state > 0; i++){
        if(state % 2 == 1){
            vect.insert(vect.begin(), N - i - 1);
        }
        state /= 2;
    }
    return vect;
}

long int num_gen(vector<int> vect, int N){ //converts states from an active neuron vector to a number
    long int n = 0;
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
    /********** Start Timing **********/
    auto start = chrono::system_clock::now();
    time_t start_time = chrono::system_clock::to_time_t(start);
    cout << endl << "\t\t" << "Started computation at " << ctime(&start_time);

    /********** Parameters **********/
    int N = 25; //number of nodes
    double px = 0.5; //probability of excitatory connection
    double pc = 0.5; //probability of connection
    long int dur = 100000000; //time steps
    //double noise = 0.01; //probability of one neuron changing state

    /********** Initialization **********/
    int* matrix = new int [N * N]; //define matrix
    ifstream the_matrix; //read in matrix
    the_matrix.open("set_matrix_1.txt");
    for(int i = 0; i < N * N; i++){
        the_matrix >> matrix[i];
    }
    the_matrix.close();
    check_matrix(matrix,N); //prints out matrix

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1.0);
    uniform_real_distribution<> diss(-1.0, 1.0);
    uniform_int_distribution<int> int_dis(0,24);

    /********** Simulation **********/
    cout << endl << "\t\t" << "Started Simulation" << endl;
    vector<int> vect; //starting vector
    double pf = dis(gen), noise;
    for(int i = 0; i < N; i++){ //randomly generize starting vector
        if(dis(gen) < pf){
            vect.push_back(i);
        }
    }
    //vector<int> vect = vector_gen(a,N);
    vector<int> vect_next; //empty vector to store results for the next active neuron vector
    /* r: a variable used in matrix multiplication
       current: tracks current state
       next: tracks next state
       y: a variable used to store the number for the active neuron vector */
    int r = 0, current = -1, next = -1;
    long int y = num_gen(vect,N);
    bool push = false;
    cout << "Starting Vector: " << y << endl; //prints out starting vector
    int* transitions = new int [25]; //define results for transitions
    for(int i = 0; i < 25; i++){
        transitions[i] = 0;
    }
    int* sums = new int [5]; //define results for sums
    for(int i = 0; i < 5; i++){
        sums[i] = 0;
    }
    for(int t = 0; t < dur; t++){ //duration of one run
        /*** generate new vect ***/
        for(int i = 0; i < N; i++){
            for(int j = 0 ; j < vect.size(); j++){
                r += matrix[vect[j] * N + i];
            }
            noise = diss(gen);
            if(r >= 0 && noise >= 0){
                push = true;
            }
            if(r <= 0 && noise <= 0){
                push = true;
            }
            if(push){
                vect_next.push_back(i); //add the active neuron
            }
            r = 0; //clear r
            push = false; //clear push
        }
        /*** wrap up ***/
        vect = vect_next;
        vect_next.clear(); //clear the active neuron vector
        y = num_gen(vect, N); //transform the active neuron vector into an integer
        if(y == 5144527) {next = 0; sums[0]++;}
        else if(y == 5176783) {next = 1; sums[1]++;}
        else if(y == 25982156) {next = 2; sums[2]++;}
        else if(y == 26113486) {next = 3; sums[3]++;}
        else if(y == 33554415) {next = 4; sums[4]++;}
        if(next >= 0){
            if(current >= 0){
                transitions[current * 5 + next]++;
            }
            current = next;
            next = -1;
        }
    }
    cout << "TRANSITIONS" << endl;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cout << transitions[i*5+j] << " ";
        }
        cout << endl;
    }
    cout << "SUMS" << endl;
    for(int i = 0; i < 5; i++){
        cout << sums[i] << endl;
    }
    /********** End Timing **********/
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << endl << "\t\tFinished computation at " << ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s" << endl << endl;
}