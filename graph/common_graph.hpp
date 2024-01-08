#pragma once
#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<fstream>
#include<omp.h>

#define NUM_THREADS 16
using namespace std;

struct Point { int x, y; };
using EdgeMap = map<int, vector<int>>;

void print_path(vector<int>& path, string mode) {
    ofstream file("./resources/graph_path_" + mode + ".txt", ios::out);
    for(auto p : path)
        file << p << ",";
    file << endl;
}


EdgeMap read_graph_edges() {
    ifstream file("./resources/graph_edges.txt", ios::in);
    if (!file.is_open()) {
        cerr << "Error opening the file." << endl;
        exit(1);
    }
    
    EdgeMap edges = map<int, vector<int>>();
    int x, y;
    char comma;
    while (file >> x >> comma >> y) {
        edges[x].push_back(y);
    }

    return edges;
}