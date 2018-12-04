/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool hasPathSum(struct TreeNode* root, int sum) {
    if(root == NULL) return false;
    if(root->left != NULL) {
        if(true == hasPathSum(root->left, sum - root->val)) return true;
    }
    if(root->right != NULL) {
        if(true == hasPathSum(root->right, sum - root->val)) return true;
    }
    if(root->left == NULL && root->right == NULL) {
        if(sum - root->val == 0) return true;
    }
    return false;
}

/**
  * 优化一下上面的代码
  */

bool hasPathSum(struct TreeNode* root, int sum) {
    if(root == NULL) return false;
    if(root->left == NULL && root->right == NULL && root->val == sum) return true;
    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}
