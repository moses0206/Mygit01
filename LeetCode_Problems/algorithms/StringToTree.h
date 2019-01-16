#ifndef __STRINGTOTREE_H__
#define __STRINGTOTREE_H__
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
typedef struct TreeNode TreeNode_t;
extern int string_to_tree(TreeNode_t **rt_node, const char * file_name);
#endif
