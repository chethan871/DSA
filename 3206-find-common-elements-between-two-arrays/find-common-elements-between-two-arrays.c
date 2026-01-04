#include <stdlib.h>

int* findIntersectionValues(int* nums1, int n, int* nums2, int m, int* returnSize) {
    int freq1[101] = {0};
    int freq2[101] = {0};

    // Count frequencies
    for (int i = 0; i < n; i++)
        freq1[nums1[i]]++;

    for (int i = 0; i < m; i++)
        freq2[nums2[i]]++;

    int answer1 = 0, answer2 = 0;

    // Count answer1
    for (int i = 0; i < n; i++) {
        if (freq2[nums1[i]] > 0)
            answer1++;
    }

    // Count answer2
    for (int i = 0; i < m; i++) {
        if (freq1[nums2[i]] > 0)
            answer2++;
    }

    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = answer1;
    result[1] = answer2;
    *returnSize = 2;

    return result;
}
