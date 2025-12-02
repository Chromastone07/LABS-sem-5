#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10
#define INF 99999

int n;                       
int cost[MAX_NODES][MAX_NODES];
int dist[MAX_NODES][MAX_NODES];
int nextHop[MAX_NODES][MAX_NODES];

void read_input(void);
void initialize(void);
void compute_distance_vector(void);
void print_routing_table(int node);
void print_all_tables(void);
void print_path_and_distance(int src, int dst);
void print_path_recursive(int src, int dst);

int main(void) {
    int src, dst;
    read_input();
    initialize();
    compute_distance_vector();

    printf("\nFinal routing tables after convergence:\n");
    print_all_tables();

    while (1) {
        printf("\nEnter two node numbers to find shortest path (src dst), or 0 0 to exit: ");
        if (scanf("%d %d", &src, &dst) != 2) { 
            fprintf(stderr, "Invalid input. Exiting.\n");
            break;
        }
        if (src == 0 && dst == 0) break;
        if (src < 1 || src > n || dst < 1 || dst > n) {
            printf("Node numbers must be between 1 and %d.\n", n);
            continue;
        }
        print_path_and_distance(src - 1, dst - 1);
    }

    printf("Program terminated.\n");
    return 0;
}

void read_input(void) {
    int i, j;
    do {
        printf("Enter the number of nodes (1 - %d): ", MAX_NODES);
        if (scanf("%d", &n) != 1) { exit(1); }
    } while (n < 1 || n > MAX_NODES);

    printf("\nEnter adjacency cost matrix.\n");
    printf("For no direct link enter 999 (or a large value). Enter costs row by row.\n");
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (i == j) {
                cost[i][j] = 0;
            } else {
                printf("Cost from node %d to node %d: ", i + 1, j + 1);
                if (scanf("%d", &cost[i][j]) != 1) exit(1);
                if (cost[i][j] >= 999) cost[i][j] = INF;
            }
        }
    }
}

void initialize(void) {
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            dist[i][j] = cost[i][j];
            if (i == j) {
                nextHop[i][j] = -1;      
            } else if (cost[i][j] < INF) {
                nextHop[i][j] = j;       
            } else {
                nextHop[i][j] = -1;      
            }
        }
    }
}

void compute_distance_vector(void) {
    int changed = 1;
    int i, j, via;
    while (changed) {
        changed = 0;
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                for (via = 0; via < n; ++via) {
                    if (dist[i][via] == INF || dist[via][j] == INF) continue;
                    if (dist[i][j] > dist[i][via] + dist[via][j]) {
                        dist[i][j] = dist[i][via] + dist[via][j];
                        if (nextHop[i][via] != -1)
                            nextHop[i][j] = nextHop[i][via];
                        else
                            nextHop[i][j] = via;
                        changed = 1;
                    }
                }
            }
        }
    }
}

void print_routing_table(int node) {
    int j;
    printf("\nRouting table for node %d:\n", node + 1);
    printf("DEST\tDIST\tNEXT_HOP\n");
    for (j = 0; j < n; ++j) {
        if (dist[node][j] >= INF) {
            printf("%d\t%4s\t%4s\n", j + 1, "INF", "----");
        } else if (node == j) {
            printf("%d\t%4d\t%4s\n", j + 1, 0, "SELF");
        } else {
            if (nextHop[node][j] == -1) {
                printf("%d\t%4d\t%4s\n", j + 1, dist[node][j], "----");
            } else {
                printf("%d\t%4d\t%4d\n", j + 1, dist[node][j], nextHop[node][j] + 1);
            }
        }
    }
}

void print_all_tables(void) {
    int i;
    for (i = 0; i < n; ++i) {
        print_routing_table(i);
    }
}

void print_path_and_distance(int src, int dst) {
    if (dist[src][dst] >= INF) {
        printf("No path from %d to %d.\n", src + 1, dst + 1);
        return;
    }
    printf("Shortest path from %d to %d (cost = %d): ", src + 1, dst + 1, dist[src][dst]);
    print_path_recursive(src, dst);
    printf("\n");
}

void print_path_recursive(int src, int dst) {
    if (src == dst) {
        printf("%d", src + 1);
        return;
    }
    printf("%d -> ", src + 1);
    if (nextHop[src][dst] == -1) {
        printf("%d", dst + 1);
        return;
    }
    print_path_recursive(nextHop[src][dst], dst);
}
