#include <stdio.h>
#define INF 999999

int main() {
    int n;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int cost[n][n];
    printf("Enter the adjacency matrix (0 for no edge):\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0 && i != j) {
                cost[i][j] = INF;
            }
        }
    }

    int selected[n];
    for (int i = 0; i < n; i++)
        selected[i] = 0;

    selected[0] = 1;

    int edges = 0;
    int total_cost = 0;

    printf("\nEdges selected in Minimum Spanning Tree:\n");

    while (edges < n - 1) {
        int min = INF;
        int a = -1, b = -1;

        for (int i = 0; i < n; i++) {
            if (selected[i]) {
                for (int j = 0; j < n; j++) {
                    if (!selected[j] && cost[i][j] < min) {
                        min = cost[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }

        printf("%d  %d  | Weight = %d\n", a, b, cost[a][b]);
        total_cost += cost[a][b];
        selected[b] = 1;
        edges++;
    }

    printf("\nTotal Minimum Cost = %d\n", total_cost);
    return 0;
}
