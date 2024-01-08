#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <omp.h>

using namespace std;

void generateGraph(int n, const string& filename, int start, int end) {
    const int MAX_NEIGHBOURS = 10;
    double times = omp_get_wtime();
    srand(time(0));
    vector<vector<int>> graph(n, vector<int>(n, 0));
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (rand() % MAX_NEIGHBOURS) + 1; j++) {
            graph[i][rand() % n] = 1;
        }
    }

    // int first, second = start;
    // for(int i = 0; i < MAX_NEIGHBOURS; i++) {
    //     first = second;
    //     second = rand() % n;
    //     graph[first][second] = 1;
    // }
    // graph[second][end] = 1;

    ofstream outputFile(filename, ios::out);
    char comma = ',';

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        string str = "";
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 1) {
                if(i == j) continue;
                str += to_string(i) + ',' + to_string(j) + '\n';
            }
        }
        #pragma omp critical
        outputFile << str;
    }
    outputFile.close();
    cout << "Graph with " << n << " vertices generated and written to " << filename << endl;
    cout << "Time taken: " << omp_get_wtime() - times << " seconds" << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <number_of_vertices> <start> <end>" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);

    if (n <= 0) {
        cerr << "Number of vertices must be a positive integer." << endl;
        return 1;
    }

    string filename = "./resources/graph_edges.txt";
    generateGraph(n, filename, start, end);

    return 0;
}
