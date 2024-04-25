//  main.cpp
//  banker_algrthm
//
//  Created by Bianca Amoako on 4/12/24.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


#define n_processes 5
#define m_resources 3


int main() {
    
    // matrix vector
    vector<int> matrixv;
    int x;
    //read matrix
    string fileName = "/Users/biancaamoako/Desktop/banker_algrthm/banker_algrthm/resource_matrix";
    ifstream matrix(fileName);
    if(matrix.is_open()){
        while(matrix >> x){
            matrixv.push_back(x);
        }
    }
    
    //available vector
    //there are k instances of resource type Rj available
    cout << "available vector: " << endl;
    vector<int> available;
    for(int i = 0; i < 3; ++i){
        available.push_back(matrixv[i]);
        cout << available[i] << " ";
    }
    cout << endl;
    
    
    //allocation vector
    //n x m; 5 processes x 3 resource types row = 5, column = 3
    //Pi is currently allocated k instances of Rj
    vector<vector<int>> allocate;
    cout << "allocate vector: " <<endl;
    int k = 0;
    for (int i = 0; i < n_processes; ++i) {
        vector<int> resource;
        for(int j = 0; j < m_resources; ++j){
            resource.push_back(matrixv[k+3]);
            k++;
        }
        allocate.push_back(resource);
    }
    
    for(int i = 0; i < allocate.size(); ++i){
        for(int j = 0; j < allocate[i].size(); ++j){
            cout << allocate[i][j] << " ";
        }
        cout << endl;
    }
    
    //max vector
    //n x m; 5 processes x 3 resource types
    // process Pi may request at most k instances of resource type Rj
    vector<vector<int>> max;
    cout << "max vector: " <<endl;
    k = 0;
    for (int i = 0; i < n_processes; ++i) {
        vector<int> resource;
        for(int j = 0; j < m_resources; ++j){
            resource.push_back(matrixv[k+18]);
            k++;
        }
        max.push_back(resource);
    }
    
    for(int i = 0; i < max.size(); ++i){
        for(int j = 0; j < max[i].size(); ++j){
            cout << max[i][j] << " ";
        }
        cout << endl;
    }
    
    //need vector
    //n x m; current need of each process ; Need [i,j] = Max[i,j] – Allocation [i,j]
    //Pi may need k more instances of Rj to complete its task
    vector<vector<int>> need;
    cout << "need vector: " <<endl;
    for (int i = 0; i < n_processes; ++i) {
        vector<int> resource;
        for(int j = 0; j < m_resources; ++j){
            resource.push_back(max[i][j] - allocate[i][j]);
        }
        need.push_back(resource);
    }
    
    for(int i = 0; i < need.size(); ++i){
        for(int j = 0; j < need[i].size(); ++j){
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
    
    //Let Work and Finish be vectors of length m and n, respectively
    vector<int> work = available;
    cout << "work vector: " << endl;
    for(int i = 0; i < work.size(); ++i){
        cout << work[i] << " ";
    }
    cout << endl;
    
    vector<bool> finish; //all processes are unsafe atm
    for(int i = 0; i < 5; ++i){
        finish.push_back(false);
    }
    
    //vector of finished processes
    vector<int> complete;
    
    int count = 0;
    while(count < n_processes){
        
        //check for a process that can be satisfied
        bool found = false;
        for(int i = 0; i < n_processes; ++i){
            if(finish[i] == false){ //check if process is finished/true
                int j;
                for(j = 0; j < m_resources; ++j){
                    if(need[i][j] > work[j])
                        break; //if the process needs more than what is available break
                }
                if(j == m_resources){ //if process was satisfied/completed
                    for(int k = 0; k < m_resources; ++k){
                        work[k] += allocate[i][k]; //update work with the allocated values of finished process
                    }
                    //update complete vector, increment count, update finish vector to true
                    complete.push_back(i);
                    count++;
                    finish[i] = true;
                    found = true;
                    }
                }
            }
        
        if(found == false) //if found leaves while loop as false, deadlock
            cout << "system entered deadlock" << endl;
    }
    
    //if no deadlock process sequence printed
    cout << "No deadlock occured, the system IS in a safe state." << endl << "Order of processes: ";
    for(int i = 0; i < n_processes; ++i)
        cout << complete[i] << " ";
    cout << endl;
}
