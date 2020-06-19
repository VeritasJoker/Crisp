#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <string>
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

void permutation(long int num, ofstream& results, int*& visited, int num_cat, int N){
    int* sums = new int [num_cat]; //sums
    for(int i = 0; i < num_cat; i++){
        sums[i] = 0;
    }
    cout << num << endl;
    vector<int> vect = vector_gen(num, N);
    for(int i = 0; i < N; i++){
        if(find(vect.begin(),vect.end(),i) != vect.end()){ //if num in vect
            if(visited[num]){
                long int mutate = num - pow(2, N - 1 - i); //inhibit the neuron
                                                cout << mutate << "[" << visited[mutate] << "] ";
                sums[visited[mutate] - 1]++;
                //visited[mutate] = 0;
            }
        }
        else{
            if(visited[num]){
                long int mutate = num + pow(2, N - 1 - i); //stimulate the neuron
                sums[visited[mutate] - 1]++;
                                                                cout << mutate << "(" << visited[mutate] << ") ";

                //visited[mutate] = 0;
            }
        }
    }
    cout << endl;
    results << endl << num << ",";
    for(int i = 0; i < num_cat; i++){
        results << sums[i] << ",";
    }
}

int main(){
    /********** Start Timing **********/
    auto start = chrono::system_clock::now();
    time_t start_time = chrono::system_clock::to_time_t(start);
    cout << endl << "\t\t" << "Started computation at " << ctime(&start_time);

    /********** Initialization **********/
    int N, num_cat; //number of nodes, number of categories
    ofstream results; //record results in txt
    results.open("results.csv");

    ifstream visits; //read in visits
    visits.open("category_25.txt");
    visits >> N >> num_cat;

    int* matrix = new int [N * N]; //define matrix
    ifstream the_matrix; //read in matrix
    the_matrix.open("set_matrix_25.txt");
    for(int i = 0; i < N * N; i++){
        the_matrix >> matrix[i];
    }
    the_matrix.close();
    print_matrix(matrix, N, results); //prints out matrix

    long int* highest = new long int [num_cat];
    results << endl << ",";
    for(int i = 0; i < num_cat; i++){ //read in the categories
        visits >> highest[i];
        results << highest[i] << ",";
    }
    long int pos = pow(2,N); //all the possibilities
    int* visited = new(nothrow) int [pos](); //set up visited
    if(!visited){
        cout << "Array memory allocation failed\n";
        return 0;
    }
    for(int i = 0; i < pos; i++){
        visits >> visited[i]; //read in visited from category
    }
    visits.close();

    for(int k = 0; k < num_cat; k++){
        vector<long int> loop;
        vector<int> vect = vector_gen(highest[k], N); //initialize active neuron vector
        vector<int> vect_next; //empty vector to store results for the next active neuron vector
        int r = 0, y = 0;
        while(y != highest[k]){
            for(int i = 0; i < N; i++){
                for(int j = 0 ; j < vect.size(); j++){
                    r += matrix[vect[j] * N + i];
                }
                if(r >= 0){
                    vect_next.push_back(i); //add the active neuron
                }
                r = 0; //clear r
            }
            vect = vect_next;
            vect_next.clear(); //clear the active neuron vector
            y = num_gen(vect, N); //transform the active neuron vector into an integer
            loop.push_back(y);
        }
        for(int i = 0; i < loop.size(); i++){
            permutation(loop[i], results, visited, num_cat, N);
        }
    }

    /********** Printing Results **********/

    results.close();
    if(visited) delete [] visited;

    /********** End Timing **********/
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << endl << "\t\tFinished computation at " << ctime(&end_time) << endl << "elapsed time: " << elapsed_seconds.count() << "s" << endl << endl;
}