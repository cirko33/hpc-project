#include "common_graph.hpp"

using namespace std;

void bfs(EdgeMap edges, int n, int start, int end) {
    queue<vector<int>> q;
    bool visited[n] = {false};
    q.push(vector<int>(1, start));

    int back;
    vector<int> current, edges_back;
    bool found = false;
    #pragma omp parallel
    #pragma omp single nowait
    {
        while (!q.empty() || !found)
        {
            current = q.front();
            q.pop();
            back = current.back();
            if(visited[back]) continue;
            visited[back] = true;
            
            edges_back = edges[back];
            #pragma omp taskloop
            for(int i = 0; i < edges_back.size(); i++) {
                if(!visited[edges_back[i]]) {
                    vector<int> new_path(current);
                    new_path.push_back(edges_back[i]);
                    if(edges_back[i] == end && !found) {
                        found = true;
                        print_path(new_path, "omp_while");
                    } else {
                        #pragma omp critical
                        q.push(new_path);
                    }

                }
            } 
        }
    }

    if(!found)
        cout << "Path not found" << endl;
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
    cout << "omp while graph time: " << omp_get_wtime() - time << endl;
    return 0;
}