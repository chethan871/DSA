#include <stdlib.h>

int* intersection(int* nums1, int nums1Size,
                  int* nums2, int nums2Size,
                  int* returnSize) {
    
    int freq[1001] = {0};   // values range: 0–1000
    int* result = (int*)malloc(sizeof(int) * 1000);
    *returnSize = 0;

    // Mark elements of nums1
    for (int i = 0; i < nums1Size; i++) {
        freq[nums1[i]] = 1;
    }

    // Find intersection
    for (int i = 0; i < nums2Size; i++) {
        if (freq[nums2[i]] == 1) {
            result[*returnSize] = nums2[i];
            (*returnSize)++;
            freq[nums2[i]] = 0;   // ensure uniqueness
        }
    }

    return result;
}
