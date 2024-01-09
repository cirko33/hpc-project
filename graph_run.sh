if [ $# -lt 3 ]; then
    echo "Usage: ./run_graph.sh <n> <start> <end>"
    exit 1
fi

g++ -fopenmp -O3 -lm -o generate ./graph/generate_graph.cpp 
mv generate ./exec
if [ $# -eq 4 ]; then
    ./exec/generate $1 $2 $3 $4
else
    ./exec/generate $1 $2 $3
fi

g++ -fopenmp -o bfs_seq ./graph/bfs_seq.cpp 
mv bfs_seq ./exec
./exec/bfs_seq $1 $2 $3

sleep 0.5

g++ -fopenmp -o bfs_omp_for ./graph/bfs_omp_for.cpp 
mv bfs_omp_for ./exec
./exec/bfs_omp_for $1 $2 $3

sleep 0.5

g++ -fopenmp -O2 -o bfs_omp_while ./graph/bfs_omp_while.cpp 
mv bfs_omp_while ./exec
./exec/bfs_omp_while $1 $2 $3

sleep 0.5

if [ $1 -lt 80 ]; then
    python3 ./python/visualize_graph.py $1 $2 $3
fi