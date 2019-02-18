#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


int bianli(struct TreeNode* root, int is_left) {
    int rt = 0;
    if(NULL == root->left && NULL == root->right && is_left) {
        rt = root->val;
    }
    if(root->left) {
        rt += bianli(root->left, 1);
    }
    if(root->right) {
        rt += bianli(root->right, 0);
    }
    return rt;
}

int sumOfLeftLeaves(struct TreeNode* root) {
    if(!root) return 0;
    return bianli(root, 0);
}

int sumOfLeftLeaves2(struct TreeNode* root) {
    if (!root) return 0;
    if (root->left && !root->left->left && !root->left->right) 
        return root->left->val + sumOfLeftLeaves(root->right);
    return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
}
