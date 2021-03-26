#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>
#include <chrono>
#include <ctime>
using namespace std;

double rand_int_gen(long int x, long int y){ //genreates random integers in [x,y]
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(x, y);
    return dis(gen);
}

long int simp_num_gen(vector<int> vect){
    long int n = 0;
    for(int i = 0; i < vect.size(); i++){
        if(vect[i] == 1){
            n += pow(2, vect.size() - 1 - i);
        }
    }
    return n;
}

int main(){
    /********** Start Timing **********/
    auto start = chrono::system_clock::now();
    time_t start_time = chrono::system_clock::to_time_t(start);
    cout << endl << "\t\t" << "Started computation at " << ctime(&start_time);

    /*********** Parameters ***********/
    long int steps = 1000000;

    /********** Initialization **********/
    int N, num_cat; //number of nodes, number of categories
    ofstream results; //record results in txt
    results.open("random_25.txt");

    ifstream visits; //read in visits
    visits.open("category_25.txt");
    visits >> N >> num_cat;
    results << N << endl << num_cat << endl;

    long int* highest = new long int [num_cat];
    for(int i = 0; i < num_cat; i++){ //read in and write the categories
        visits >> highest[i];
        results << highest[i] << " ";
    }
    results << endl << endl;

    long int pos = pow(2, N); //all the possibilities
    int* visited = new(nothrow) int [pos](); //set up visited
    if(!visited){
        cout << "Array memory allocation failed\n";
        return 0;
    }
    for(int i = 0; i < pos; i++){
        visits >> visited[i]; //read in visited from category
    }
    visits.close();

    vector<vector<long int>> cat_results(num_cat, vector<long int>(num_cat,0)); // 2d vector to store results
    int start_state = 0, end_state = 0;

    /********** Random Walk **********/
    bitset<25> vect (rand_int_gen(0, pos - 1)); // bitset of random integer between 0 to 2^25-1

    for(int i = 0; i < steps; i++){
        start_state = visited[vect.to_ulong()]; // start state of the vector
        vect = vect.flip(rand_int_gen(0,24)); // flip one bit
        end_state = visited[vect.to_ulong()]; // end state of the vector
        cat_results[start_state - 1][end_state - 1]++; // record transition in 2d vector
    }

    /********** Printing Results **********/

    for(int i = 0; i < num_cat; i++){
        for(int j = 0; j < num_cat; j++){
            results << cat_results[i][j] << " ";
        }
        results << endl;
    }
    results.close();
    if(visited) delete [] visited;

    /********** End Timing **********/
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << endl << "\t\tFinished computation at " << ctime(&end_time) << endl << "elapsed time: " << elapsed_seconds.count() << "s" << endl << endl;
}