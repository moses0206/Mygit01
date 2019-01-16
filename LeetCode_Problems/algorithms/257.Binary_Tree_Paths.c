/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#define DEFAULT_CHAR_SIZE (1 << 10)

char **xxx(struct TreeNode *node, char *a, int *rs) {
    char tmp[32] = {0};
    if(strlen(a) == 0) {
        snprintf(tmp, 32, "%d", node->val);
    } else {
        snprintf(tmp, 32, "->%d", node->val);
    }
    strcat(a, tmp);
    char *b = NULL;
    int int_l = 0, int_r = 0;
    int flag = 0;
    char **rt_l = NULL, **rt_r = NULL, **rt;
    if(node->left && node->right) {
        flag = 2;
        b = calloc(DEFAULT_CHAR_SIZE, sizeof(char));
        memcpy(b, a, DEFAULT_CHAR_SIZE);
        rt_l = xxx(node->left, a, &int_l);
        rt_r = xxx(node->right, b, &int_r);
    } else {
        if(node->left) {
            flag = 1;
            rt_l = xxx(node->left, a, &int_l);
        }
        if(node->right) {
            flag = 1;
            rt_l = xxx(node->right, a, &int_l);
        }
    }
    if(flag == 0) {
        *rs = 1;
        rt = calloc(1, sizeof(char*));
        rt[0] = a;
    } else {
        if(flag == 1) {
            *rs = int_l;
            rt = rt_l;
        } else {
            *rs = int_l + int_r;
            rt = realloc(rt_l, (*rs) * sizeof(char*));
            for(int i = 0; i < int_r; ++i) {
                rt[int_l + i] = rt_r[i];
            }
            free(rt_r);
        }
    }
    return rt;
}

char** binaryTreePaths(struct TreeNode* root, int* returnSize) {
    if(!root) return NULL;
    char * a = calloc(1, DEFAULT_CHAR_SIZE * sizeof(char));
    return xxx(root, a, returnSize);
}
