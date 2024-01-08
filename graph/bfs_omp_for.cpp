#include "common_graph.hpp"

using namespace std;

void bfs(EdgeMap edges, int n, int start, int end) {
    queue<vector<int>> q;
    bool visited[n] = {false};
    {
        vector<int> st = edges[start];
        #pragma omp parallel for
        for(int i = 0; i < st.size(); i++) {
            vector<int> path(1, start);
            path.push_back(st[i]);
            #pragma omp critical
            q.push(path);
        }
        visited[start] = true;
    }

    int back;
    vector<int> current, edges_back;
    bool found = false;
    
    #pragma omp parallel
    while (!found)
    {
        #pragma omp for private(current, edges_back, back)
        for(int i = 0; i < q.size(); i++) {
            #pragma omp critical
            {
                current = q.front();
                q.pop();
            }
            if(found) continue;

            back = current.back();
            if(visited[back]) continue;
                visited[back] = true;

            if(back == end && !found) {
                found = true;
                cout << "Path found" << endl;
                print_path(current, "omp_for");
                continue;
            }

            edges_back = edges[back];
            for(int i = 0; i < edges_back.size(); i++) {
                if(visited[edges_back[i]]) continue;
                vector<int> new_path(current);
                new_path.push_back(edges_back[i]);
                #pragma omp critical
                q.push(new_path);
            } 
        }
    }

    if(!found)
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
    cout << "omp for graph time: " << omp_get_wtime() - time << endl;
    return 0;
}