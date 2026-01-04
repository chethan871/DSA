/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void flatten(struct TreeNode* root) {
    struct TreeNode* curr = root;

    while (curr != NULL) {
        if (curr->left != NULL) {
            // Find rightmost node of left subtree
            struct TreeNode* prev = curr->left;
            while (prev->right != NULL) {
                prev = prev->right;
            }

            // Attach original right subtree
            prev->right = curr->right;

            // Move left subtree to right
            curr->right = curr->left;
            curr->left = NULL;
        }
        // Move to next node
        curr = curr->right;
    }
}
