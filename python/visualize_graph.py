import sys
import networkx as nx
import matplotlib.pyplot as plt

def visualize_graph(n, edges, start_vertex, end_vertex):
    G = nx.DiGraph()

    for edge in edges:
        x, y = map(int, edge.split(','))
        G.add_edge(x, y)

    pos = nx.shell_layout(G)
    labels = {i: str(i) for i in range(n)}

    plt.figure(figsize=(10, 6))

    nx.draw(G, pos, with_labels=True, labels=labels, node_size=700, node_color='skyblue', font_size=10, font_color='black', font_weight='bold', arrowsize=20, width=1.5)

    try:
        path = nx.shortest_path(G, source=start_vertex, target=end_vertex)
        edges_path = [(path[i], path[i + 1]) for i in range(len(path) - 1)]
        edge_colors = ['red' if edge in edges_path else 'black' for edge in G.edges()]
    except:
        print(f"Error: No path from {start_vertex} to {end_vertex}.")
        edge_colors = ['black' for edge in G.edges()]

    nx.draw_networkx_edges(G, pos, edgelist=G.edges(), edge_color=edge_colors, width=1.5, alpha=0.7)

    plt.title(f"Directed Graph Visualization - Path from {start_vertex} to {end_vertex}")
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python visualize_graph.py <number_of_vertices> <start_vertex> <end_vertex>")
        sys.exit(1)

    n = int(sys.argv[1])
    start_vertex = int(sys.argv[2])
    end_vertex = int(sys.argv[3])

    filename = "./resources/graph_edges.txt"

    try:
        with open(filename, 'r') as file:
            edges = file.read().strip().split('\n')
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found.")
        sys.exit(1)

    visualize_graph(n, edges, start_vertex, end_vertex)
