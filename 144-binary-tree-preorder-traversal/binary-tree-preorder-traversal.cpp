class Solution {
public:
    void po(TreeNode* x, vector<int>& ans){
        if (x == nullptr) return; 
        ans.push_back(x->val);
        po(x->left, ans);
        po(x->right, ans);
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        po(root, ans);
        return ans; 
        }
};