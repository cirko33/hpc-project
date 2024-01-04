#include<iostream>
#include<queue>
#include<vector>
#include <fstream>
#include <omp.h>

using namespace std;

template<typename T>
using Matrix = vector<vector<T>>;

template<typename T>
Matrix<T> make_matrix(int n, T value = T()) {
    return vector<vector<T>>(n, vector<T>(n, value));
} 

struct Point { int x, y; };

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

void print_path(vector<Point>& path) {
    ofstream file("./resources/path.txt", ios::out);
    for(auto p : path)
        file << p.x << "," << p.y << endl;

    file.close();
}

void bfs(Matrix<char>& maze, char wall, int n) {
    queue<vector<Point>> q;
    Matrix<bool> visited = make_matrix<bool>(n, false);
    q.push(vector<Point>(1, {0, 0}));

    while (!q.empty()) {
        vector<Point> current = q.front();
        q.pop();
        Point back = current.back();
        int i = back.x, j = back.y;

        if(visited[i][j]) continue;
        visited[i][j] = true;

        if(i == n-1 && j == n-1) {
            cout << "Path found" << endl;
            print_path(current);
            break;
        }
            
        if(i > 0 && maze[i-1][j] != wall && !visited[i-1][j]) {
            vector<Point> next(current);
            next.push_back({i-1, j});
            q.push(next);
        }
        if(i < n-1 && maze[i+1][j] != wall && !visited[i+1][j]) {
            vector<Point> next(current);
            next.push_back({i+1, j});
            q.push(next);
        }
        if(j > 0 && maze[i][j-1] != wall && !visited[i][j-1]) {
            vector<Point> next(current);
            next.push_back({i, j-1});
            q.push(next);
        }
        if(j < n-1 && maze[i][j+1] != wall && !visited[i][j+1]) {
            vector<Point> next(current);
            next.push_back({i, j+1});
            q.push(next);
        }
    }
}

int main(int argc, char** argv)
{
    int n = 100;
    char wall = '#';

    double start = omp_get_wtime();
    if(argc == 2) {
        try {
            n = atoi(argv[1]);
        } catch(...) {
            cout << "Invalid argument" << endl;
            n = 100;
        }
    }

    Matrix<char> maze = read_maze(n);

    bfs(maze, wall, n);
    cout << "Time: " << omp_get_wtime() - start << endl;
    return 0;
}