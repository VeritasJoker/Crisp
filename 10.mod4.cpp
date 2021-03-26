#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <map>
using namespace std;

vector<int> vector_gen(long int state, int N){ // converts states from a number to an active neuron vector
    vector<int> vect;
    for(int i = 0; state > 0; i++){
        if(state % 2 == 1){
            vect.insert(vect.begin(), N - i - 1);
        }
        state /= 2;
    }
    return vect;
}

long int num_gen(vector<int> vect, int N){ // converts states from an active neuron vetor to a number
    long int n = 0;
    for(int i = 0; i < vect.size(); i++){
        n += pow(2, N - 1 - vect[i]);
    }
    return n;
}

int main(){
    /********** Start Timing **********/
    auto start = chrono::system_clock::now();
    time_t start_time = chrono::system_clock::to_time_t(start);
    cout << endl << "\t\t" << "Started computation at " << ctime(&start_time);

   /********** Parameters **********/
    int N, num_cat, fixed_node = 20; // number of nodes and number of final cycles

    /********** Initialization **********/
    ifstream the_matrix; // stream for matrix
    the_matrix.open("set_matrix_25.txt");
    the_matrix >> N; // read in vector number
    int* matrix = new int [N * N]; // define matrix
    for(int i = 0; i < N * N; i++){
        the_matrix >> matrix[i]; // read in matrix
    }
    the_matrix.close();

    ifstream cycles; // stream for mod1 results
    cycles.open("results.txt");
    cycles >> N >> num_cat; // read in number of nodes and number of final cycles
    vector<vector<long int>> cat_cycles(num_cat, vector<long int>(1,0)); // 2d vector to store cycle vetors
    vector<long int> cat_nums(num_cat,0); // vector to store cycle vector numbers
    vector<vector<int>> sim_nodes(num_cat, vector<int>(1,0));
    for(int i = 0; i < num_cat; i++){
        cout << i << endl;
        cycles >> cat_cycles[i][0] >> cat_nums[i]; // read in cycles and numbers
        vector<int> vect = vector_gen(cat_cycles[i].back(), N); // initialize active neuron vector
        if(!binary_search(vect.begin(),vect.end(),fixed_node)){
            vect.push_back(fixed_node); // fix node
        }
        cat_cycles[i][0] = num_gen(vect,N); // update number with fix node
        vect = vector_gen(cat_cycles[i][0],N); // update vector with fix node
        vector<int> vect_next; // empty vector to store results for the next active neuron vector
        sim_nodes[i] = vect; // get the active nodes for the first cycle
        int y = 0, r = 0;
        while(y != cat_cycles[i][0]){
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
            if(!binary_search(vect.begin(),vect.end(),fixed_node)){
                vect.push_back(fixed_node); // fix node
            }
            vect_next.clear();
            y = num_gen(vect, N); //transform the active neuron vector into an integer
            cat_cycles[i].push_back(y);
            vector<int> v(sim_nodes[i].size() + vect.size()); 
            vector<int>::iterator it, st;
            vector<int> sim_nodes_filler;
            it = set_intersection(sim_nodes[i].begin(), 
                                sim_nodes[i].end(), 
                                vect.begin(), 
                                vect.end(), 
                                v.begin());
            for (st = v.begin(); st != it; ++st){
                sim_nodes_filler.push_back(*st); // add common nodes to the filler vector
            }
            sim_nodes[i] = sim_nodes_filler;
            sim_nodes_filler.clear();
        }
    }

    for(int i = 0; i < num_cat; i++){
        for(int j = 0; j < cat_cycles[i].size(); j++){
            cout << cat_cycles[i][j] << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < num_cat; i++){
        for(int j = 0; j < sim_nodes[i].size(); j++){
            cout << sim_nodes[i][j] << " ";
        }
        cout << endl;
    }

    /********** End Timing **********/
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << endl << "\t\tFinished computation at " << ctime(&end_time) << endl << "elapsed time: " << elapsed_seconds.count() << "s" << endl << endl;
}