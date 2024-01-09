#include "common.hpp"

using namespace std;

class parallel_queue {
    queue<vector<Point>> q;
    omp_lock_t lock;
public:
    parallel_queue() {
        omp_init_lock(&lock);
    }

    ~parallel_queue() {
        omp_destroy_lock(&lock);
    }

    void push(vector<Point> v) {
        omp_set_lock(&lock);
        q.push(v);
        omp_unset_lock(&lock);
    }

    void push(vector<vector<Point>> v) {
        omp_set_lock(&lock);
        for(auto e : v)
            q.push(e);
        omp_unset_lock(&lock);
    }

    vector<Point> pop() {
        omp_set_lock(&lock);
        vector<Point> v = q.front();
        q.pop();
        omp_unset_lock(&lock);
        return v;
    }

    int size() {
        omp_set_lock(&lock);
        int s = q.size();
        omp_unset_lock(&lock);
        return s;
    }
};
