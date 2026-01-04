/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 *
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool dfs(struct TreeNode* root, struct ListNode* head) {
    if (head == NULL) return true;      // list fully matched
    if (root == NULL) return false;
    if (root->val != head->val) return false;

    return dfs(root->left, head->next) || dfs(root->right, head->next);
}

bool isSubPath(struct ListNode* head, struct TreeNode* root) {
    if (root == NULL) return false;

    // Try matching from this node OR continue searching in subtrees
    if (dfs(root, head)) return true;

    return isSubPath(head, root->left) || isSubPath(head, root->right);
}
