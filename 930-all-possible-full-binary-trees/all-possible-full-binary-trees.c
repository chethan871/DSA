#include <stdlib.h>

/* TreeNode is already defined by the platform
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
*/

struct TreeNode* newNode() {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode** allPossibleFBTUtil(int n, int* returnSize) {
    if (n % 2 == 0) {
        *returnSize = 0;
        return NULL;
    }

    if (n == 1) {
        struct TreeNode** result = malloc(sizeof(struct TreeNode*));
        result[0] = newNode();
        *returnSize = 1;
        return result;
    }

    struct TreeNode** result = NULL;
    int count = 0;

    for (int left = 1; left < n; left += 2) {
        int right = n - 1 - left;

        int leftSize, rightSize;
        struct TreeNode** leftTrees = allPossibleFBTUtil(left, &leftSize);
        struct TreeNode** rightTrees = allPossibleFBTUtil(right, &rightSize);

        for (int i = 0; i < leftSize; i++) {
            for (int j = 0; j < rightSize; j++) {
                struct TreeNode* root = newNode();
                root->left = leftTrees[i];
                root->right = rightTrees[j];

                result = realloc(result, sizeof(struct TreeNode*) * (count + 1));
                result[count++] = root;
            }
        }
    }

    *returnSize = count;
    return result;
}

struct TreeNode** allPossibleFBT(int n, int* returnSize) {
    return allPossibleFBTUtil(n, returnSize);
}
