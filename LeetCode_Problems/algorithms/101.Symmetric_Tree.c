#include <stdbool.h>
#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int compare_2_node(struct TreeNode *l, struct TreeNode *r) {
    if((!l && r) || (l && !r)) return false;
    if(!l) return true;
    if(l->val != r->val)return false;
    if(false == compare_2_node(l->left, r->right)) return false;
    if(false == compare_2_node(l->right, r->left)) return false;
    return true;
}

bool isSymmetric(struct TreeNode* root) {
    if(root == NULL) return true;
    return compare_2_node(root->left, root->right);
}

