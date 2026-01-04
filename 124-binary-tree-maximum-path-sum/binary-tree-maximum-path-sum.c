#include <limits.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int maxSum;

int maxGain(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    // Compute max contribution from left and right
    int left = maxGain(root->left);
    int right = maxGain(root->right);

    // Ignore negative paths
    if (left < 0) left = 0;
    if (right < 0) right = 0;

    // Path passing through this node
    int currentPath = root->val + left + right;

    // Update global maximum
    if (currentPath > maxSum)
        maxSum = currentPath;

    // Return max single-path contribution
    return root->val + (left > right ? left : right);
}

int maxPathSum(struct TreeNode* root) {
    maxSum = INT_MIN;
    maxGain(root);
    return maxSum;
}
