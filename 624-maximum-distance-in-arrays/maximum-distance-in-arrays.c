#include <stdlib.h>

int maxDistance(int** arrays, int arraysSize, int* arraysColSize) {
    
    int minVal = arrays[0][0];
    int maxVal = arrays[0][arraysColSize[0] - 1];
    int result = 0;

    for (int i = 1; i < arraysSize; i++) {
        int currMin = arrays[i][0];
        int currMax = arrays[i][arraysColSize[i] - 1];

        // Calculate max distance using different arrays
        if (abs(currMax - minVal) > result)
            result = abs(currMax - minVal);

        if (abs(maxVal - currMin) > result)
            result = abs(maxVal - currMin);

        // Update global min and max
        if (currMin < minVal)
            minVal = currMin;

        if (currMax > maxVal)
            maxVal = currMax;
    }

    return result;
}
