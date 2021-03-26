#include <random>
#include <vector>
#include <map>
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
    int dur = 250; //time steps

    /********** Initialization **********/
    int* matrix = new int [N * N]; //define matrix
    ifstream the_matrix; //read in matrix
    the_matrix.open("matrix.txt");
    for(int i = 0; i < N * N; i++){
        the_matrix >> matrix[i];
    }
    the_matrix.closee();
    //check_matrix(matrix,N); //prints out matrix
    long int pos = pow(2,N); //all the possibilities

    long int** visited = new(nothrow) long int* [pos](); //track the y_highest for all active neuron vectors
    if(!visited){
        cout << "Array memory allocation failed\n";
        return 0;
    }
    long int loop1 = 0, loop2 = -1;

    map<long int, vector<long int>> category; //final results
    list<long int> highest;

    // ofstream results; //record results in txt
    // results.open("results.txt");

    /********** Simulation **********/
    cout << endl << "\t\t" << "Started Simulation" << endl;
    for(long int a = 1002032; a < 1002033; a++){ //run for every vector
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
        // for(int i = 0; i < vect_visited.size(); i++){
        //     cout << vect_visited[i] << endl;
        // }
        /*** categorization ***/
        if(*visited[y] == -1){ //not mapped
            //cout << "\t\tPushed Y_HIGHEST: " << y_highest << endl;
            highest.push_back(y_highest); //store the highest value
            //visited[y] = &(highest[highest.size()-1]); //point y to the highest value
            visited[y] = &(highest.back());
        }
        for(int i = 0; i < vect_visited.size(); i++){
            visited[vect_visited[i]] = visited[y];
            category[*visited[y]].push_back(vect_visited[i]); // mapping newly visited active neuron vectors
        }
        //cout << "\t\tCategory size check: " << category[*visited[y]].size() << endl;
        // /*** output results for graph ***/
        // for(int i = 0; i < x_spikes.size(); i++){
        //     results << x_spikes[i] << " ";
        // }
        // results << "\n";
        // for(int i = 0; i < y_spikes.size(); i++){
        //     results << y_spikes[i] << " ";
        // }
        // results << "\n";
        // x_spikes.clear();
        // y_spikes.clear();
    }
    cout << endl << "\t\tFinished all runs, Printing results" << endl << endl;
    /********** Printing Results **********/
    long int size = 0;
    map<long int, vector<long int>>::iterator itr;
    // for(itr = category.begin(); itr != category.end(); itr++){
    //     cout << "\t\t" << itr->first << ": ";
    //     //if(itr->first <= 100) size++;
    //     for(int i = 0; i < itr->second.size(); i++){
    //         cout << itr->second[i] << " ";
    //         size++;
    //     }
    //     cout << endl;
    // }
    cout << "\t\tNumber of categories: " << category.size() << endl;
    for(itr = category.begin(); itr != category.end(); itr++){
        cout << "\t\t" << itr->first << ": " << itr->second.size() << endl;
        size+=itr->second.size();
    }
    cout << "\t\tTotal vectors categorized: " << size << endl;
    if(visited) delete [] visited;
    //results.close();

    /********** End Timing **********/
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << endl << "\t\tFinished computation at " << ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s" << endl << endl;
}