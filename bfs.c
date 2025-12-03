#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Maximum number of vertices

// Function to perform BFS on the graph
void BFS(int graph[MAX][MAX], int n, int start) {
    int visited[MAX] = {0}; // Keeps track of visited nodes
    int queue[MAX];         // Queue for BFS
    int front = 0, rear = 0;

    // Enqueue the starting node and mark it as visited
    queue[rear++] = start;
    visited[start] = 1;

    printf("Nodes reachable from node %d are: ", start);

    while (front < rear) {
        int current = queue[front++]; // Dequeue a node
        printf("%d ", current);       // Print the current node

        // Traverse all adjacent vertices of the current node
        for (int i = 0; i < n; i++) {
            // If there is an edge and it’s not visited yet
            if (graph[current][i] == 1 && !visited[i]) {
                queue[rear++] = i;    // Enqueue the node
                visited[i] = 1;       // Mark as visited
            }
        }
    }
    printf("\n");
}

int main() {
    int n, start;
    int graph[MAX][MAX];

    // Input number of vertices
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Input adjacency matrix
    printf("Enter adjacency matrix of the directed graph:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Input starting node
    printf("Enter starting node (0 to %d): ", n - 1);
    scanf("%d", &start);

    // Perform BFS
    BFS(graph, n, start);

    return 0;
}
