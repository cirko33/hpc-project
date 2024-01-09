from sys import argv

if __name__ == "__main__":
    sum = 0
    cnt = 0
    for i in range(1, len(argv)):
        sum += float(argv[i])
        cnt += 1

    print("{:.5f}".format(sum / cnt))
