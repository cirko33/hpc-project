#pragma once
#include<iostream>
#include<queue>
#include<vector>
#include<fstream>
#include<omp.h>

using namespace std;

template<typename T>
using Matrix = vector<vector<T>>;
struct Point { int x, y; };

template<typename T>
Matrix<T> make_matrix(int n, T value = T()) {
    return vector<vector<T>>(n, vector<T>(n, value));
}

void print_path(vector<Point>& path, string mode) {
    ofstream file("./resources/path_" + mode + ".txt", ios::out);
    for(auto p : path)
        file << p.x << "," << p.y << endl;

    file.close();
}


Matrix<char> read_maze(int n) {
    ifstream file("./resources/maze_" + to_string(n) + ".txt", ios::in);
    Matrix<char> maze = make_matrix<char>(n);

    string line;
    for(int i = 0; i < n; i++) {
        getline(file, line);
        for(int j=0; j<n; j++)
            maze[i][j] = line[j];
    }

    return maze;
}