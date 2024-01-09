#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <omp.h>

using namespace std;

void generateGraph(int n, const string& filename, int max_neighbors = 10) {
    double times = omp_get_wtime();
    srand(time(0));
    ofstream outputFile(filename, ios::out);

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        vector<bool> graph = vector<bool>(n, false);
        string str = "";
        for (int j = 0; j < (rand() % max_neighbors) + 1; j++) {
            int neighbour = rand() % n;
            if (neighbour == i) continue;
            if(graph[neighbour]) continue;
            graph[neighbour] = true;
            str += to_string(i) + ',' + to_string(neighbour) + '\n';
        }
        #pragma omp critical
        outputFile << str;
    }

    outputFile.close();
    cout << "Graph with " << n << " vertices generated and written to " << filename << endl;
    cout << "Time taken: " << omp_get_wtime() - times << " seconds" << endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <number_of_vertices> [max_neighbors]" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    int max_neighbors = 10;
    if(argc == 3) max_neighbors = atoi(argv[2]);

    if (n <= 0) {
        cerr << "Number of vertices must be a positive integer." << endl;
        return 1;
    }

    string filename = "./resources/graph_edges.txt";
    generateGraph(n, filename, max_neighbors);

    return 0;
}
