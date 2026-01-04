#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int r, c;
} Point;

/* BFS to find shortest path */
int bfs(int** forest, int rows, int cols, int sr, int sc, int tr, int tc) {
    if (sr == tr && sc == tc) return 0;

    int visited[50][50] = {0};
    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    Point queue[2500];
    int front = 0, rear = 0;

    queue[rear++] = (Point){sr, sc};
    visited[sr][sc] = 1;

    int steps = 0;

    while (front < rear) {
        int size = rear - front;
        while (size--) {
            Point p = queue[front++];

            if (p.r == tr && p.c == tc)
                return steps;

            for (int i = 0; i < 4; i++) {
                int nr = p.r + dr[i];
                int nc = p.c + dc[i];

                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                    !visited[nr][nc] && forest[nr][nc] != 0) {
                    visited[nr][nc] = 1;
                    queue[rear++] = (Point){nr, nc};
                }
            }
        }
        steps++;
    }
    return -1;
}

/* Main Function */
int cutOffTree(int** forest, int forestSize, int* forestColSize) {
    int rows = forestSize;
    int cols = forestColSize[0];

    // Store trees
    int trees[2500][3];
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (forest[i][j] > 1) {
                trees[count][0] = forest[i][j];
                trees[count][1] = i;
                trees[count][2] = j;
                count++;
            }
        }
    }

    // Sort trees by height
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (trees[i][0] > trees[j][0]) {
                int temp[3];
                for (int k = 0; k < 3; k++) {
                    temp[k] = trees[i][k];
                    trees[i][k] = trees[j][k];
                    trees[j][k] = temp[k];
                }
            }
        }
    }

    int sr = 0, sc = 0;
    int totalSteps = 0;

    for (int i = 0; i < count; i++) {
        int tr = trees[i][1];
        int tc = trees[i][2];

        int dist = bfs(forest, rows, cols, sr, sc, tr, tc);
        if (dist == -1) return -1;

        totalSteps += dist;
        sr = tr;
        sc = tc;
        forest[tr][tc] = 1; // cut the tree
    }

    return totalSteps;
}
