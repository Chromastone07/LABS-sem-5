#include <stdio.h>
#define MAX 100  // Maximum number of vertices

int visited[MAX]; // To keep track of visited nodes

// Function to perform DFS recursively
void DFS(int graph[MAX][MAX], int n, int start) {
    visited[start] = 1;          // Mark current node as visited
    printf("%d ", start);        // Print current node

    // Visit all adjacent vertices
    for (int i = 0; i < n; i++) {
        if (graph[start][i] == 1 && !visited[i]) {
            DFS(graph, n, i);    // Recursive call for unvisited adjacent node
        }
    }
}

int main() {
    int n, start;
    int graph[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix of the directed graph:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter starting node (0 to %d): ", n - 1);
    scanf("%d", &start);

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("Nodes reachable from node %d are: ", start);
    DFS(graph, n, start);

    printf("\n");
    return 0;
}
