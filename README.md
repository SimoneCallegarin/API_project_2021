# API_project_2021
Program that reads a sequence of graphs from standard input, each represented by an adjacency matrix. For each graph, it calculates the sum of the shortest paths from node 0 to all other nodes using a simplified version of Dijkstra’s algorithm.

## Main Steps
### Input:
- Number of nodes n_nodi.
- Number K of top graphs to keep based on shortest-path sum.

### Processing Each Graph:
- Reads the adjacency matrix.
- Computes shortest paths from node 0 to all others.
- Calculates the total sum of these shortest paths.

### Top-K Tracking:
- If K < 100: uses an array with insertion sort.
- If K ≥ 100: uses a doubly linked list, sorted by the path sum.

### Output:
- When the line starts with "T", it prints the indices of the K graphs with the smallest total shortest-path sums seen so far.

