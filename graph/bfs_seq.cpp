#include "common_graph.hpp"

using namespace std;

void bfs(EdgeMap edges, int n, int start, int end) {
    queue<vector<int>> q;
    bool visited[n] = {false};
    for(auto it = edges[start].begin(); it != edges[start].end(); ++it) {
        vector<int> path(1, start);
        path.push_back(*it);
        q.push(path);
    }
    visited[start] = true;

    int back;
    vector<int> current;
    
    while (!q.empty()) {
        current = q.front();
        q.pop();
        back = current.back();

        if(visited[back]) continue;
        visited[back] = true;

        if(back == end) {
            cout << "Path found" << endl;
            print_path(current, "seq");
            return;
        }

        for(auto it = edges[back].begin(); it != edges[back].end(); ++it) {
            if(visited[*it]) continue;
            vector<int> new_path(current);
            new_path.push_back(*it);
            q.push(new_path);
        }
    }

    cout << "Path not found :(" << endl;
}

int main(int argc, char** argv)
{
    int n, start, end;
    if(argc != 4) {
        cout << "Usage: ./bfs_seq_graph <n> <start> <end>" << endl;
        return 0;
    }

    double time = omp_get_wtime();
    try {
        n = atoi(argv[1]);
        start = atoi(argv[2]);
        end = atoi(argv[3]);
    } catch(...) {
        cout << "Invalid argument" << endl;
        exit(1);
    }

    if(start < 0 || start >= n || end < 0 || end >= n) {
        cout << "Invalid argument" << endl;
        exit(1);
    }

    if(start == end) {
        cout << "Start can't be equal to end" << endl;
        exit(1);
    }

    EdgeMap edges = read_graph_edges();

    bfs(edges, n, start, end);
    cout << "Seq. graph time: " << omp_get_wtime() - time << endl;
    return 0;
}