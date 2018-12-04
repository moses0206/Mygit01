#include <stdlib.h>
#include <stdbool.h>

/**
  * 此算法与v1版本思想一致，但是v1版在LeetCode上耗时是8ms，用时较长。
  * 此版本相较v1版本的不同是，将getTreeDeep的参数减少1个，直接使用返回值-1当作失败返回。
  * 而不失败的时候，返回深度。（深度肯定大于0）。
  */

int getTreeDeep(struct TreeNode* tree) {
    if(tree == NULL) return 0;
    int l_depth = 0, r_depth = 0;
    l_depth = getTreeDeep(tree->left);
    r_depth = getTreeDeep(tree->right);
    if(r_depth == -1) return -1;
    if(l_depth == -1) return -1;
    if(abs(l_depth - r_depth) > 1) return -1;
    return (l_depth > r_depth ? l_depth : r_depth) + 1;
}

bool isBalanced(struct TreeNode* root) {
    if(root == NULL) return true;
    return (getTreeDeep(root) != -1);                                                                     
}
