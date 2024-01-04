import matplotlib.pyplot as plt
import numpy as np
from sys import argv

def visualize_maze(maze, path=None):
    cmap = plt.cm.get_cmap('Blues', 3) 
    n = len(maze)

    img = np.ones((n, n, 3))

    for i in range(n):
        for j in range(n):
            if maze[i][j] == '#':
                img[i, j] = cmap(1)[:3]
            elif maze[i][j] == '+':
                img[i, j] = cmap(0)[:3]

    if path is not None:
        for node in path:
            img[node[0], node[1]] = cmap(2)[:3]

    plt.imshow(img)
    plt.axis('off')
    plt.show()

def read_maze(file_path):
    with open(file_path, 'r') as file:
        maze = [list(line.strip()) for line in file]
    return maze

if __name__ == "__main__":
    if(len(argv) != 2):
        print("Usage: python visualize.py <n>")
        exit(1)

    n = int(argv[1])
    labyrinth_file = f"./resources/maze_{n}.txt"
    coordinates_file = "./resources/path.txt"

    maze = read_maze(labyrinth_file)

    with open(coordinates_file, 'r') as coord_file:
        coordinates = [tuple(map(int, line.strip().split(','))) for line in coord_file]

    visualize_maze(maze, coordinates)
