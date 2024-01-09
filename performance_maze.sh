if [ ! -d "./exec" ]; then
    mkdir exec
fi

if [ $# == 0 ]; then
    echo "Usage: ./performance_maze.sh <max_dimension>"
    exit 1
fi


g++ ./maze/bfs_seq.cpp -fopenmp -O2 -o bfs_seq
mv bfs_seq ./exec

g++ ./maze/bfs_omp_for.cpp -fopenmp -O2 -o bfs_omp_for
mv bfs_omp_for ./exec

g++ ./maze/bfs_omp_while.cpp -fopenmp -O2 -o bfs_omp_while
mv bfs_omp_while ./exec

seq_all_seq=""
seq_all_omp_for=""
seq_all_omp_while=""
seq_all_dimensions=""

for ((j=100; j<=$1; j+=100)); do
    list_seq=""
    list_omp_for=""
    list_omp_while=""

    for i in {1..3}; do
        python3 python/maze.py $j

        seq=$(./exec/bfs_seq $j)
        IFS=':' read -ra ADDR <<< "$seq"
        list_seq+=(${ADDR[1]})
        sleep 0.5

        omp_for=$(./exec/bfs_omp_for $j)
        IFS=':' read -ra ADDR <<< "$omp_for"
        list_omp_for+=(${ADDR[1]})
        sleep 0.5

        omp_while=$(./exec/bfs_omp_while $j)
        IFS=':' read -ra ADDR <<< "$omp_while"
        list_omp_while+=(${ADDR[1]})
        sleep 0.5
    done

    seq=$(python3 python/avg.py ${list_seq[@]})
    omp_for=$(python3 python/avg.py ${list_omp_for[@]})
    omp_while=$(python3 python/avg.py ${list_omp_while[@]})
    seq_all_seq+="$seq,"
    seq_all_omp_for+="$omp_for,"
    seq_all_omp_while+="$omp_while,"
    seq_all_dimensions+="$j,"
done

python3 python/plot.py "${seq_all_dimensions[@]}" "${seq_all_seq[@]}" "${seq_all_omp_for[@]}" "${seq_all_omp_while[@]}"


