struct TreeNode* mergeTrees(struct TreeNode* root1, struct TreeNode* root2) {
    if (root1 == NULL) return root2;
    if (root2 == NULL) return root1;

    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = root1->val + root2->val;

    newNode->left = mergeTrees(root1->left, root2->left);
    newNode->right = mergeTrees(root1->right, root2->right);

    return newNode;
}
