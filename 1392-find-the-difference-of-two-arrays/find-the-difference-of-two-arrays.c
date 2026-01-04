#include <stdlib.h>
#include <string.h>

#define RANGE 2001  // from -1000 to 1000

int** findDifference(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize, int** returnColumnSizes) {
    int** ans = (int**)malloc(2 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(2 * sizeof(int));
    (*returnColumnSizes)[0] = 0;
    (*returnColumnSizes)[1] = 0;
    
    ans[0] = (int*)malloc(nums1Size * sizeof(int));
    ans[1] = (int*)malloc(nums2Size * sizeof(int));
    
    int hash1[RANGE] = {0};
    int hash2[RANGE] = {0};
    
    for (int i = 0; i < nums1Size; i++)
        hash1[nums1[i] + 1000] = 1;
    
    for (int i = 0; i < nums2Size; i++)
        hash2[nums2[i] + 1000] = 1;
    
    // nums1 not in nums2
    for (int i = 0; i < nums1Size; i++) {
        int val = nums1[i] + 1000;
        if (hash1[val] && !hash2[val]) {
            ans[0][(*returnColumnSizes)[0]++] = nums1[i];
            hash1[val] = 0;
        }
    }
    
    // nums2 not in nums1
    for (int i = 0; i < nums2Size; i++) {
        int val = nums2[i] + 1000;
        if (hash2[val] && !hash1[val]) {  // FIXED: use hash1[val], not val+1000
            ans[1][(*returnColumnSizes)[1]++] = nums2[i];
            hash2[val] = 0;
        }
    }
    
    *returnSize = 2;
    return ans;
}
