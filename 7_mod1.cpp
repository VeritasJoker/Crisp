#include <random>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
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

long int num_gen(vector<int> vect, int N){ //converts states from an active neuron vetor to a number
    long int n = 0;
    for(int i = 0; i < vect.size(); i++){
        n += pow(2, N - 1 - vect[i]);
    }
    return n;
}

void print_digit(int num, ofstream& results){ //prints out a digit
    if(num < 10 && num >= 0){
        results << " " << num;
    }
    else{
        results << num;
    }
}

void print_matrix(int* matrix, int N, ofstream& results){ //prints out a matrix
    results << "MATRIX" << endl << "    ";
    for(int i = 0; i < N; i++){
        print_digit(i, results);
        results << " ";
    }
    results << endl << endl;
    for(int i = 0; i < N; i++){
        print_digit(i, results);
        results << "| ";
        for(int j = 0 ; j < N; j++){
            print_digit(matrix[i * N + j], results);
            results << " ";
        }
        results << endl;
    }
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
    int dur = 250; //time steps

    /********** Initialization **********/
    ofstream results; //record results in txt
    results.open("results.txt");

    ifstream the_matrix; //read in matrix
    the_matrix.open("set_matrix_25.txt");
    int* matrix = new int [N * N]; //define matrix
    for(int i = 0; i < N * N; i++){
        the_matrix >> matrix[i];
    }
    the_matrix.close();
    //print_matrix(matrix, N, results); //prints out matrix
    long int pos = pow(2,N); //all the possibilities

    int** visited = new(nothrow) int* [pos](); //track the y_highest for all active neuron vectors
    if(!visited){
        cout << "Array memory allocation failed\n";
        return 0;
    }
    int loop1 = 0, loop2 = -1;

    vector<long int> highest;
    list<int> highest_index;

    /********** Simulation **********/
    for(long int a = 0; a < pos; a++){ //run for every vector
        if(visited[a]) continue;
        vector<int> vect = vector_gen(a, N); //initialize active neuron vector
        vector<int> vect_next; //empty vector to store results for the next active neuron vector
        vector<int> vect_visited; //empty vetor to store all newly visited active neuron vectors in this run
        /* r: a variable used in matrix multiplication
           y_highest: the highest number in the loop for this run
           y: a variable used to store the number for the active neuron vector */
        int r = 0;
        long int y_highest = -1, y;
        visited[a] = &loop1; //mark this active neuron vector as visited
        vect_visited.push_back(a);
        for(int t = 0; t < dur; t++){ //duration of one run
            /*** generate new vect ***/
            for(int i = 0; i < N; i++){
                for(int j = 0 ; j < vect.size(); j++){
                    r += matrix[vect[j] * N + i];
                }
                if(r >= 0){
                    vect_next.push_back(i); //add the active neuron
                }
                r = 0; //clear r
            }
            /*** wrap up ***/
            vect = vect_next;
            vect_next.clear(); //clear the active neuron vector
            y = num_gen(vect, N); //transform the active neuron vector into an integer
            if(visited[y]){
                if(*visited[y] == 0){
                    visited[y] = &loop2; //start of the loop, loop through it again
                    if(y_highest < y){
                        y_highest = y; //change y_highest
                    }
                }
                else{
                    break; //break loop
                } 
            }
            else{ //not visited
                visited[y] = &loop1; //mark this active neuron vector as visited for the first time
                vect_visited.push_back(y); //add active neuron vector
            }
        }
        /*** categorization ***/
        vector<long int> loop;
        if(*visited[y] == -1){ //not mapped
            highest.push_back(y_highest); //store the highest value
            highest_index.push_back(highest.size());
            visited[y] = &(highest_index.back());
        }
        for(int i = 0; i < vect_visited.size(); i++){
            visited[vect_visited[i]] = visited[y];
        }
    }
    /********** Printing Results **********/
    results << N << endl << highest.size() << endl;
    for(int i = 0; i < highest.size(); i++){
        results << highest[i] << endl;
    }
    for(int i = 0; i < pos; i++){
        results << *visited[i] << " ";
    }
    results.close();
    if(visited) delete [] visited;

    /********** End Timing **********/
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << endl << "\t\tFinished computation at " << ctime(&end_time) << endl << "elapsed time: " << elapsed_seconds.count() << "s" << endl << endl;
}