/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool flipEquiv(struct TreeNode* root1, struct TreeNode* root2) {
    // Both null → equal
    if (root1 == NULL && root2 == NULL)
        return true;

    // One null or values not equal → not equal
    if (root1 == NULL || root2 == NULL || root1->val != root2->val)
        return false;

    // Case 1: No flip
    bool noFlip = flipEquiv(root1->left, root2->left) &&
                  flipEquiv(root1->right, root2->right);

    // Case 2: Flip children
    bool flip = flipEquiv(root1->left, root2->right) &&
                flipEquiv(root1->right, root2->left);

    return noFlip || flip;
}
