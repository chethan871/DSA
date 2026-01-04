#include <stdio.h>
#include <stdlib.h>

#define MAXV 51

typedef struct NodeStack {
    int val;
    struct NodeStack* next;
} NodeStack;

typedef struct Edge {
    int to;
    int next;
} Edge;

Edge* edges;
int* head;
int edgeCnt;
int* nums;
int* ans;
int* depth;
NodeStack* last[MAXV];
int coprime[MAXV][MAXV];

void addEdge(int u, int v) {
    edges[edgeCnt].to = v;
    edges[edgeCnt].next = head[u];
    head[u] = edgeCnt++;
}

void push(int val, int node) {
    NodeStack* ns = (NodeStack*)malloc(sizeof(NodeStack));
    ns->val = node;
    ns->next = last[val];
    last[val] = ns;
}

void pop(int val) {
    NodeStack* ns = last[val];
    if (ns) {
        last[val] = ns->next;
        free(ns);
    }
}

int top(int val) {
    if (last[val]) return last[val]->val;
    return -1;
}

void dfs(int u, int parent) {
    int bestNode = -1, bestDepth = -1;

    for (int v = 1; v <= 50; v++) {
        if (last[v] && coprime[v][nums[u]]) {
            int candidate = top(v);
            if (depth[candidate] > bestDepth) {
                bestDepth = depth[candidate];
                bestNode = candidate;
            }
        }
    }

    ans[u] = bestNode;

    push(nums[u], u);

    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != parent) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    pop(nums[u]);
}

int* getCoprimes(int* numsArr, int n, int** edgesArr, int edgesSize, int* edgesColSize, int* returnSize) {
    nums = numsArr;

    edges = (Edge*)malloc(sizeof(Edge) * 2 * edgesSize);
    head = (int*)malloc(sizeof(int) * n);
    depth = (int*)malloc(sizeof(int) * n);
    ans = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) head[i] = -1;
    edgeCnt = 0;

    for (int i = 0; i < edgesSize; i++) {
        int u = edgesArr[i][0];
        int v = edgesArr[i][1];
        addEdge(u, v);
        addEdge(v, u);
    }

    // Precompute coprime table
    for (int i = 1; i <= 50; i++) {
        for (int j = 1; j <= 50; j++) {
            int a = i, b = j;
            while (b) { int t = a % b; a = b; b = t; }
            coprime[i][j] = (a == 1);
        }
    }

    for (int i = 1; i <= 50; i++) last[i] = NULL;

    depth[0] = 0;
    dfs(0, -1);

    *returnSize = n;
    return ans;
}
