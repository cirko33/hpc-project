#include "common.hpp"

using namespace std;

void bfs(Matrix<char>& maze, char wall, int n) {
    queue<vector<Point>> q;
    Matrix<bool> visited = make_matrix<bool>(n, false);
    q.push(vector<Point>(1, {0, 0}));
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};
    const int LEN = 4;

    int i, j, k, ni, nj;
    Point back;
    vector<Point> current;
 
    #pragma omp parallel
    #pragma omp single nowait
    while (!q.empty()) {
        current = q.front();
        q.pop();
        back = current.back();
        i = back.x, j = back.y;

        if (visited[i][j]) continue;            
        visited[i][j] = true;

        if (i == n - 1 && j == n - 1) {
            print_path(current, "omp_while");
            break;
        }

        #pragma omp taskloop private(ni, nj, k) shared(current)
        for (k = 0; k < LEN; ++k) {
            ni = i + dx[k];
            nj = j + dy[k];

            if (ni >= 0 && ni < n && nj >= 0 && nj < n &&
                maze[ni][nj] != wall && !visited[ni][nj]) {
                vector<Point> next(current);
                next.push_back({ni, nj});
                #pragma omp critical
                q.push(next);
            }
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
    cout << "omp while time: " << omp_get_wtime() - start << endl;
    return 0;
}