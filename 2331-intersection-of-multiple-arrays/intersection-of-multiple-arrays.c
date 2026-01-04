#include <stdlib.h>

int* intersection(int** nums, int numsSize, int* numsColSize, int* returnSize) {
    
    int count[1001] = {0};
    *returnSize = 0;

    // Count presence of each number in each array
    for (int i = 0; i < numsSize; i++) {
        int visited[1001] = {0};  // to avoid double counting in same array
        
        for (int j = 0; j < numsColSize[i]; j++) {
            int val = nums[i][j];
            if (!visited[val]) {
                count[val]++;
                visited[val] = 1;
            }
        }
    }

    // Allocate result array
    int* result = (int*)malloc(sizeof(int) * 1000);

    // Collect numbers present in all arrays
    for (int i = 1; i <= 1000; i++) {
        if (count[i] == numsSize) {
            result[*returnSize] = i;
            (*returnSize)++;
        }
    }

    return result;
}
