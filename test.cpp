#include <random>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
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
    /********** Parameters **********/
    int N; //number of nodes
    double px = 0.5; //probability of excitatory connection
    double pc = 0.5; //probability of connection
    int dur = 250; //time steps

    /********** Initialization **********/
    ofstream results; //record results in txt
    results.open("test_results.txt");

    ifstream the_matrix; //read in matrix
    the_matrix.open("set_matrix_25.txt");
    the_matrix >> N;
    int* matrix = new int [N * N]; //define matrix
    for(int i = 0; i < N * N; i++){
        the_matrix >> matrix[i];
    }
    the_matrix.close();
    long int pos = pow(2,N); //all the possibilities

    long int y, a;
    bool single_test;
    cout << "Single test or multiple? (single test outputs to txt, multiple tests output to console)" 
    << endl << "(reply 0 or 1)" << endl;
    cin >> single_test;

    if(single_test){
        /********** Single Test (output to txt) **********/
        cin >> a;
        results << a << " ";
        vector<int> vect = vector_gen(a, N), vect_next;
        for(int t = 0; t < dur; t++){
            y = matrix_multiplication(vect, vect_next, matrix, N);
            results << y << " ";
        }
        results.close();
    }
    else{
        /********** Multiple Test (output to console) **********/
        while(cin >> a){
            cout << "results for vect " << a << ":" << endl << a << " ";
            vector<int> vect = vector_gen(a, N), vect_next;
            for(int t = 0; t < dur; t++){
                y = matrix_multiplication(vect, vect_next, matrix, N);
                cout << y << " ";
            }
            cout << endl << endl;
        }
    }
}  