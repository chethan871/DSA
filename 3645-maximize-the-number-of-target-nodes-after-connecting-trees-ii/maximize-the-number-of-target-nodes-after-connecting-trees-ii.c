#include <stdlib.h>

void dfs(int u, int parent, int color,
         int *colors, int *cnt0, int *cnt1,
         int **adj, int *deg)
{
    colors[u] = color;
    if (color == 0) (*cnt0)++;
    else (*cnt1)++;

    for (int i = 0; i < deg[u]; i++) {
        int v = adj[u][i];
        if (v != parent)
            dfs(v, u, color ^ 1, colors, cnt0, cnt1, adj, deg);
    }
}

int* maxTargetNodes(
    int** edges1, int edges1Size, int* edges1ColSize,
    int** edges2, int edges2Size, int* edges2ColSize,
    int* returnSize
) {
    int n = edges1Size + 1;
    int m = edges2Size + 1;

    /* ---------- build adjacency for tree 1 ---------- */
    int *deg1 = calloc(n, sizeof(int));
    for (int i = 0; i < edges1Size; i++) {
        deg1[edges1[i][0]]++;
        deg1[edges1[i][1]]++;
    }

    int **adj1 = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        adj1[i] = malloc(deg1[i] * sizeof(int));

    int *idx1 = calloc(n, sizeof(int));
    for (int i = 0; i < edges1Size; i++) {
        int u = edges1[i][0], v = edges1[i][1];
        adj1[u][idx1[u]++] = v;
        adj1[v][idx1[v]++] = u;
    }

    /* ---------- build adjacency for tree 2 ---------- */
    int *deg2 = calloc(m, sizeof(int));
    for (int i = 0; i < edges2Size; i++) {
        deg2[edges2[i][0]]++;
        deg2[edges2[i][1]]++;
    }

    int **adj2 = malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++)
        adj2[i] = malloc(deg2[i] * sizeof(int));

    int *idx2 = calloc(m, sizeof(int));
    for (int i = 0; i < edges2Size; i++) {
        int u = edges2[i][0], v = edges2[i][1];
        adj2[u][idx2[u]++] = v;
        adj2[v][idx2[v]++] = u;
    }

    /* ---------- DFS coloring ---------- */
    int *color1 = calloc(n, sizeof(int));
    int *color2 = calloc(m, sizeof(int));

    int even1 = 0, odd1 = 0;
    int even2 = 0, odd2 = 0;

    dfs(0, -1, 0, color1, &even1, &odd1, adj1, deg1);
    dfs(0, -1, 0, color2, &even2, &odd2, adj2, deg2);

    int bestSecond = (even2 > odd2) ? even2 : odd2;

    int *answer = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        answer[i] = (color1[i] == 0 ? even1 : odd1) + bestSecond;
    }

    *returnSize = n;
    return answer;
}
