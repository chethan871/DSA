#include <stdlib.h>

// Invert binary tree recursively
struct TreeNode* invertTree(struct TreeNode* root) {
    if (!root) return NULL;

    // Swap left and right children
    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Recursively invert subtrees
    invertTree(root->left);
    invertTree(root->right);

    return root;
}
