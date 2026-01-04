#include <stdlib.h>
#include <math.h>

int isPerfectSquare(long long x) {
    long long r = (long long)(sqrt(x));
    return r * r == x;
}

void dfs(int* nums, int numsSize, int* used, int prev, int depth, int* count) {
    if (depth == numsSize) {
        (*count)++;
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        if (used[i]) continue;

        // Skip duplicates
        if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])
            continue;

        if (depth == 0 || isPerfectSquare((long long)prev + nums[i])) {
            used[i] = 1;
            dfs(nums, numsSize, used, nums[i], depth + 1, count);
            used[i] = 0;
        }
    }
}

int numSquarefulPerms(int* nums, int numsSize) {
    // Sort nums
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] > nums[j]) {
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }

    int* used = (int*)calloc(numsSize, sizeof(int));
    int count = 0;

    dfs(nums, numsSize, used, 0, 0, &count);

    free(used);
    return count;
}
