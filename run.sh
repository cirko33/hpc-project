if [ ! -d "./exec" ]; then
    mkdir exec
fi

if [ $# == 0 ]; then
    echo "Usage: ./run.sh <maze_dimension>"
    exit 1
fi

python3 python/maze.py $1

g++ bfs_seq.cpp -fopenmp -o bfs_seq
mv bfs_seq ./exec
./exec/bfs_seq $1

bash -c "python3 python/visualize.py $1 seq" &

g++ bfs_omp_for.cpp -fopenmp -o bfs_omp_for

mv bfs_omp_for ./exec
./exec/bfs_omp_for $1

bash -c "python3 python/visualize.py $1 omp_for" &

g++ bfs_omp_while.cpp -fopenmp -o bfs_omp_while

mv bfs_omp_while ./exec
./exec/bfs_omp_while $1

bash -c "python3 python/visualize.py $1 omp_while" &