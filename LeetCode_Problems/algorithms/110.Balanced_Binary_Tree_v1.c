#include <stdbool.h>
#include "StringToTree.c"

getTreeDeep(struct TreeNode* tree, int* depth) {
    if(tree == NULL) return true;
    int l_depth = 0, r_depth = 0;
    if(false == getTreeDeep(tree->left, &l_depth)) return false;
    if(false == getTreeDeep(tree->right, &r_depth)) return false;
    *depth = (l_depth > r_depth ? l_depth : r_depth) + 1;
    if(l_depth - r_depth > 1 || l_depth - r_depth < -1) return false;
    else return true;
}

bool isBalanced(struct TreeNode* root) {
    if(root == NULL) return true;
    int depth = 0;
    return getTreeDeep(root, &depth);
}

void main(void) {
    TreeNode_t *root = NULL;
    int size = string_to_tree(&root, "wangmao.txt");
    int flag = isBalanced(root);
    printf("size = %d\nflag = %d\n", size, flag);
}
