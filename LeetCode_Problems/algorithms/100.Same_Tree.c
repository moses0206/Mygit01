/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
//C99中提供了一个头文件<stdbool.h>定义了bool代表 _Bool，true代表1，false代表0。
#include <stdbool.h>
#include <stdlib.h>
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if(p == NULL && q == NULL) return true;
    if(p == NULL || q == NULL) return false;
    if(p->val != q->val) return false;
    if(false == isSameTree(p->left, q->left)) return false;
    if(false == isSameTree(p->right, q->right)) return false;
    return true;
}
