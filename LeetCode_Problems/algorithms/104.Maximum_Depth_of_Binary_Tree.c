#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode_t;

int maxDepth(TreeNode_t* root) {
    if(root == NULL) return 0;
    int tmp_l, tmp_r;
    tmp_l = maxDepth(root->left);
    tmp_r = maxDepth(root->right);
    return 1 + ((tmp_l > tmp_r)? tmp_l : tmp_r);
}

static TreeNode_t* init_TreeNode(int n, int d) { // n - val's number; d - depth;
    if(d < 1) return NULL;
    TreeNode_t * tn = (TreeNode_t*)malloc(sizeof(TreeNode_t));
    tn->val = n;
    tn->left = init_TreeNode(n + 1, d - 1);
    tn->right = init_TreeNode(n + 1, d - 1);
    return tn;
}

void main(void) {
    TreeNode_t* test;
    test = init_TreeNode(1, 7);
    printf("TreeNode* test's depth = %d\n", maxDepth(test));
}
