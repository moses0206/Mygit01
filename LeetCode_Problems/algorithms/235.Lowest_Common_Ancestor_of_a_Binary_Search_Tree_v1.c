/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if(p->val == q->val) return p;
    struct TreeNode *left = NULL, *right = NULL;
    left = p->val < q->val ? p : q;
    right = p->val < q->val ? q : p;
    while(root) {
        if(left->val <= root->val && right->val >= root->val) {
            return root;
        }
        if(left->val < root->val) root = root->left;
        else root = root->right;
    }
    return NULL;
}
