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

int main(){
    /********** Parameters **********/
    int N = 20; //number of nodes
    double px = 0.5; //probability of excitatory connection
    double pc = 0.5; //probability of connection
    int dur = 250; //time steps

    /********** Initialization **********/
    int* matrix = matrix_gen(N, px, pc); //initialize matrix
    ofstream results; //record results in txt
    results.open("matrix.txt");
    for(int i = 0; i < N * N; i++){
        results << matrix[i] << " ";
    }
    results.close();
}