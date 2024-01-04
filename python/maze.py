import os
import random

def generate_maze(rows, cols):
    maze = [['#' for _ in range(cols)] for _ in range(rows)]
    stack = [(0, 0)]

    while stack:
        x, y = stack[-1]
        maze[x][y] = '+'
        neighbors = [(dx, dy) for dx, dy in [(0, 2), (2, 0), (0, -2), (-2, 0)]]
        random.shuffle(neighbors)

        found = False
        for dx, dy in neighbors:
            nx, ny = x + dx, y + dy
            if 0 <= nx < rows and 0 <= ny < cols and maze[nx][ny] == '#':
                maze[x + dx // 2][y + dy // 2] = '+'
                stack.append((nx, ny))
                found = True
                break

        if not found:
            stack.pop()

    maze[rows - 1][cols - 1] = '+'
    maze[rows - 2][cols - 1] = '+'
    return maze

def print_maze(maze, rows):
    if os.path.exists(f"./resources/maze_{rows}.txt"):
        os.remove(f"./resources/maze_{rows}.txt")
        
    with open(f"./resources/maze_{rows}.txt", 'a+') as file:
        for row in maze:
            print(''.join(row), file=file)

if __name__ == "__main__":
    import sys

    if len(sys.argv) != 2:
        print("Usage: python generate_maze.py <rows>")
        sys.exit(1)

    rows, cols = int(sys.argv[1]), int(sys.argv[1])
    maze = generate_maze(rows, cols)
    print_maze(maze, rows)
