#include <stdbool.h>

bool checkStraightLine(int** coordinates, int coordinatesSize, int* coordinatesColSize) {
    int x0 = coordinates[0][0];
    int y0 = coordinates[0][1];
    int x1 = coordinates[1][0];
    int y1 = coordinates[1][1];

    // Direction vector
    int dx = x1 - x0;
    int dy = y1 - y0;

    for (int i = 2; i < coordinatesSize; i++) {
        int x = coordinates[i][0];
        int y = coordinates[i][1];

        // Check cross product == 0
        if ((long)(y - y0) * dx != (long)(x - x0) * dy) {
            return false;
        }
    }
    return true;
}
