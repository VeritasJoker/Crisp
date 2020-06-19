#include <random>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;

double rand_gen(){ //genreates random number in [0,1)
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1.0);
    return dis(gen);
}

int* matrix_gen(int N, double px, double pc){ //generates matrix randomly
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

long int matrix_multiplication(vector<int> &vect, vector<int> &vect_next, int* &matrix, int N){
    int r = 0;
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
    long int y = num_gen(vect, N); //transform the active neuron vector into an integer
    return y;
}

int main(){
    /********** Start Timing **********/
    auto start = chrono::system_clock::now();
    time_t start_time = chrono::system_clock::to_time_t(start);
    cout << endl << "\t\t" << "Started computation at " << ctime(&start_time);

    /********** Parameters **********/
    int N = 20; //number of nodes
    double px = 0.5; //probability of excitatory connection
    double pc = 0.5; //probability of connection
    int dur = 250; //time steps

    /********** Initialization **********/
    ofstream results; //record results in txt
    results.open("results.txt");

    int* matrix = new int [N * N]; //define matrix
    ifstream the_matrix; //read in matrix
    the_matrix.open("matrix.txt");
    for(int i = 0; i < N * N; i++){
        the_matrix >> matrix[i];
    }
    the_matrix.close();
    print_matrix(matrix, N, results); //prints out matrix
    long int pos = pow(2,N); //all the possibilities

    long int** visited = new(nothrow) long int* [pos](); //track the y_highest for all active neuron vectors
    int* levels = new(nothrow) int [pos];
    for(int i = 0; i < pos; i++){
        levels[i] = -1;
    }
    if(!visited || !levels){
        cout << "Array memory allocation failed\n";
        return 0;
    }
    long int loop1 = -1, loop2 = -2;

    map<long int, vector<long int>> category; //final results
    list<long int> highest;

    /********** Simulation **********/
    for(long int a = 0; a < pos; a++){ //run for every vector
        if(visited[a]) continue;
        /* vect: initialize active neuron vector
           vect_next: empty vector to store results for the next active neuron vector
           vect_visited: empty vetor to store all newly visited active neuron vectors in this run */
        vector<int> vect = vector_gen(a, N), vect_next, vect_visited;
        /* y_highest: the highest number in the loop for this run
           y: a variable used to store the number for current active neuron vector */
        long int y_highest = -1, y;
        int level_lowest; //store the lowest level possible in one run
        visited[a] = &loop1; //mark this active neuron vector as visited
        vect_visited.push_back(a);
        for(int t = 0; t < dur; t++){ //duration of one run
            y = matrix_multiplication(vect, vect_next, matrix, N);
            if(visited[y]){
                if(*visited[y] == -1){
                    visited[y] = &loop2; //start of the loop, loop through it again
                    levels[y] = 0; //mark the levels as zero
                    if(y_highest < y){
                        y_highest = y; //change y_highest
                    }
                }
                else{
                    level_lowest = levels[y];
                    break; //break loop
                } 
            }
            else{ //not visited
                visited[y] = &loop1; //mark this active neuron vector as visited for the first time
                vect_visited.push_back(y); //add active neuron vector
            }
        }
        /*** categorization ***/
        if(*visited[y] == -2){ //not mapped
            highest.push_back(y_highest); //store the highest value
            visited[y] = &(highest.back());
        }
        for(int i = 0; i < vect_visited.size(); i++){
            visited[vect_visited[i]] = visited[y];
            category[*visited[y]].push_back(vect_visited[i]); // mapping newly visited active neuron vectors
            int z = vect_visited.size() - 1 - i;
            if(levels[vect_visited[z]] == -1){
                if(i == 0){
                    levels[vect_visited[z]] = level_lowest + 1;
                }
                else{
                    levels[vect_visited[z]] = levels[vect_visited[z+1]] + 1;
                }
            }
        }
    }
    /********** Printing Results **********/
    long int size = 0, looping_y; //size is used to check if all vectors are categorized; looping_y is used to print out cycles
    vector<int> vect, vect_next; //same functions as before
    map<long int, vector<long int>>::iterator itr;
    results << endl << "RESULTS" << endl << endl;
    for(itr = category.begin(); itr != category.end(); itr++){ //iterate for each category
        results << "(";
        looping_y = itr->first;
        while(visited[looping_y]){ //prints out cycles
            results << " " << looping_y;
            visited[looping_y] = NULL;
            vect = vector_gen(looping_y, N);
            looping_y = matrix_multiplication(vect, vect_next, matrix, N);
        }
        results << " )" << endl << "Total: " << itr->second.size() << endl; //prints out total vectors
        size+=itr->second.size(); //increment size
        map<int, long int> tree;
        for(int i = 0; i < itr->second.size(); i++){ //building the levels tree
            auto search = tree.find(levels[itr->second[i]]);
            if(search == tree.end()){ //not found
                tree.insert(map<int,long int>::value_type(levels[itr->second[i]],1));
            } //found
            else{
                search->second++;
            }
        }
        map<int, long int>::iterator level_itr;
        for(level_itr = tree.begin(); level_itr != tree.end(); level_itr++){
            results << "Level " << level_itr->first << ": " << level_itr->second << endl;
        }
        results << endl;
    }
    results << endl << "Number of categories: " << category.size() << endl;
    results << "Total vectors categorized: " << size;
    results.close();

    ofstream detailed_results;
    detailed_results.open("detailed_results.txt");
    for(itr = category.begin(); itr != category.end(); itr++){
        detailed_results << "\t\t" << itr->first << ": ";
        for(int i = 0; i < itr->second.size(); i++){
            detailed_results << itr->second[i] << "(" << levels[itr->second[i]] << ")" << " ";
        }
        detailed_results << endl << endl;
    }
    detailed_results.close();
    if(visited) delete [] visited;

    /********** End Timing **********/
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << endl << "\t\tFinished computation at " << ctime(&end_time) << endl << "elapsed time: " << elapsed_seconds.count() << "s" << endl << endl;
}