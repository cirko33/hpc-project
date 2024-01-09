import matplotlib.pyplot as plt
from sys import argv

def plot(x, y_seq, y_omp_for):
    print(x)
    print(y_seq)
    print(y_omp_for)
    #print(y_omp_while)
    plt.plot(x, y_seq, label='Sequential')
    plt.plot(x, y_omp_for, label='Parallel for')
    #plt.plot(x, y_omp_while, label='Parallel task')

    plt.xlabel('Graph dimensions')
    plt.ylabel('Time(s)')
    plt.title('Graph BFS time')
    plt.legend()

    plt.show()

if __name__ == "__main__":
    data = []
    if(len(argv) < 4):
        print("Usage: python3 plot.py <seq_data> <omp_for_data> <omp_while_data>")
        exit(1)

    for i in range(1, len(argv)):
        data.append([])
        for num in argv[i].split(","):
            if(num == ""):
                continue
            if(i == 1):
                data[i-1].append(int(num))
            else:
                data[i-1].append(float(num))

    plot(data[0], data[1], data[2])