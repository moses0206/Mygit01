#include <stdio.h>
#include <stdlib.h>


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* mergeTrees(struct TreeNode* t1, struct TreeNode* t2) {
    if (t1 == NULL || t2 == NULL){
        return (t1 ? t1 : t2);
    }
    struct TreeNode * tn = calloc(1, sizeof(struct TreeNode));
    tn->val = t1->val + t2->val;
    if (t1->left == NULL || t2->left == NULL){
        tn->left = (t1->left ? t1->left : t2->left);
    }else{
        tn->left = mergeTrees(t1->left, t2->left);
    }
    if (t1->right == NULL || t2->right == NULL){
        tn->right = (t1->right ? t1->right : t2->right);
    }else{
        tn->right = mergeTrees(t1->right, t2->right);
    }
    return tn;
}

void __free(struct TreeNode * tn) {
    if (tn->left != NULL) {
        __free(tn->left);
    }
    if (tn->right != NULL) {
        __free(tn->right);
    }
    free(tn);
}

int main(void) {
    struct TreeNode * tn = calloc(1, sizeof(struct TreeNode));
    tn->val = 8;
    printf("tn->val is %d\n", tn->val);
    __free(tn);
    return 0;
}
