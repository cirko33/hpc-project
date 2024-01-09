if [ ! -d "./exec" ]; then
    mkdir exec
fi

if [ $# == 0 ]; then
    echo "Usage: ./performance_graph.sh <max_dimension>"
    exit 1
fi

g++ -fopenmp -O3 -lm -o generate ./graph/generate_graph.cpp 
mv generate ./exec     

g++ ./graph/bfs_seq.cpp -fopenmp -o bfs_seq
mv bfs_seq ./exec

g++ ./graph/bfs_omp_for.cpp -fopenmp -o bfs_omp_for
mv bfs_omp_for ./exec

g++ ./graph/bfs_omp_while.cpp -fopenmp -o bfs_omp_while
mv bfs_omp_while ./exec

seq_all_seq=""
seq_all_omp_for=""
#seq_all_omp_while=""
seq_all_dimensions=""

for ((j=1000; j<=$1; j*=2)); do
    list_seq=""
    list_omp_for=""
    #list_omp_while=""
    
    none=$(./exec/generate "$j 500")
    par="$j $((RANDOM % ($j - 500) + 1)) $((RANDOM % 500 + ($j - 500) + 1))"
    ./exec/bfs_seq $par
    if [ $? -ne 0 ]; then
        ((j/=2))
        continue
    fi

    for i in {1..3}; do
        seq=$(./exec/bfs_seq $par)
        IFS=':' read -ra ADDR <<< "$seq"
        list_seq+=(${ADDR[1]})
        sleep 0.01

        omp_for=$(./exec/bfs_omp_for $par)
        IFS=':' read -ra ADDR <<< "$omp_for"
        list_omp_for+=(${ADDR[1]})
        sleep 0.01

        # omp_while=$(./exec/bfs_omp_while $par)
        # IFS=':' read -ra ADDR <<< "$omp_while"
        # list_omp_while+=(${ADDR[1]})
        # sleep 0.01
    done

    seq=$(python3 python/avg.py ${list_seq[@]})
    omp_for=$(python3 python/avg.py ${list_omp_for[@]})
    # omp_while=$(python3 python/avg.py ${list_omp_while[@]})
    seq_all_seq+="$seq,"
    seq_all_omp_for+="$omp_for,"
    #seq_all_omp_while+="$omp_while,"
    seq_all_dimensions+="$j,"

    echo "Done with dimension $j"
done

python3 python/plot.py "${seq_all_dimensions[@]}" "${seq_all_seq[@]}" "${seq_all_omp_for[@]}" #"${seq_all_omp_while[@]}"