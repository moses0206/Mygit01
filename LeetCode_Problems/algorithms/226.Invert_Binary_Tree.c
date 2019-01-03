/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * straightforward DFS 
 */

#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct TreeNode TreeNode_t;

TreeNode_t* invertCloneTree(TreeNode_t *root) {
    if(NULL == root) return NULL;
    TreeNode_t *new = (TreeNode_t*)calloc(1, sizeof(TreeNode_t));
    new->val = root->val;
    new->left = invertCloneTree(root->right);
    new->right = invertCloneTree(root->left);
    return new;
}

TreeNode_t* invertTree(TreeNode_t *root) {
    if(NULL == root) return NULL;
    TreeNode_t *left = root->left;
    TreeNode_t *right = root->right;
    root->left = invertTree(right);
    root->right = invertTree(left);
    return root;
}

