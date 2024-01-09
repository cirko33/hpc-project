#include "parallel_queue.hpp"

using namespace std;

void bfs(Matrix<char>& maze, char wall, int n) {
    parallel_queue q;
    Matrix<bool> visited = make_matrix<bool>(n, false);
    q.push(vector<Point>(1, {0, 0}));
    visited[0][0] = true;

    bool found = false;
    int i, j, ni, nj;
    Point back;
    vector<Point> current;
    while (!found)
    {
        #pragma omp parallel for firstprivate(i, j, ni, nj, back, current)
        for (int q_size = 0; q_size < q.size(); ++q_size) {
            current = q.pop();
            back = current.back();
            i = back.x, j = back.y;

            if (i == n - 1 && j == n - 1) {
                if(!found) {
                    found = true;
                    print_path(current, "omp_for");
                }
            }

            if(i + 1 < n && maze[i+1][j] != wall && !visited[i+1][j]) {
                vector<Point> next(current);
                next.push_back({i+1, j});
                q.push(next);
                visited[i+1][j] = true;
            }

            if(i - 1 >= 0 && maze[i-1][j] != wall && !visited[i-1][j]) {
                vector<Point> next(current);
                next.push_back({i-1, j});
                q.push(next);
                visited[i-1][j] = true;
            }

            if(j + 1 < n && maze[i][j+1] != wall && !visited[i][j+1]) {
                vector<Point> next(current);
                next.push_back({i, j+1});
                q.push(next);
                visited[i][j+1] = true;
            }

            if(j - 1 >= 0 && maze[i][j-1] != wall && !visited[i][j-1]) {
                vector<Point> next(current);
                next.push_back({i, j-1});
                q.push(next);
                visited[i][j-1] = true;
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
    cout << "omp for time: " << omp_get_wtime() - start << endl;
    return 0;
}