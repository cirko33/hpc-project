import matplotlib.pyplot as plt
import numpy as np
from sys import argv
import warnings
warnings.filterwarnings("ignore")

def visualize_maze(maze, title=None, path=None):
    cmap = plt.cm.get_cmap('Blues', 3) 
    n = len(maze)

    img = np.ones((n, n, 3))

    for i in range(n):
        for j in range(n):
            if maze[i][j] == '+':
                img[i, j] = cmap(0)[:3]
            elif maze[i][j] == '#':
                img[i, j] = cmap(1)[:3]

    if path is not None:
        for node in path:
            img[node[0], node[1]] = cmap(2)[:3]

    if title is not None:
        plt.title(title)
    else:
        plt.title("Maze")

    fig = plt.gcf()
    fig.set_size_inches(8, 8)

    plt.imshow(img)
    plt.axis('off')
    plt.show()

def read_maze(file_path):
    with open(file_path, 'r') as file:
        maze = [list(line.strip()) for line in file]
    return maze

if __name__ == "__main__":
    if(len(argv) < 2):
        print("Usage: python visualize.py <n> [<title>]")
        exit(1)

    n = int(argv[1])
    title = argv[2] if len(argv) > 2 else ""

    labyrinth_file = f"./resources/maze_{n}.txt"
    coordinates_file = f"./resources/path_{title}.txt"

    maze = read_maze(labyrinth_file)

    with open(coordinates_file, 'r') as coord_file:
        coordinates = [tuple(map(int, line.strip().split(','))) for line in coord_file]

    visualize_maze(maze, title, coordinates)
