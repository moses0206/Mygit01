#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int depth(struct TreeNode* tn) {
    if(tn == NULL) return 0;
    else {
        int depl, depr;
        depl = depth(tn->left);
        depr = depth(tn->right);
        return (1 + (depl > depr? depl: depr));
    }
}

void dealOfLevel(struct TreeNode* tn, int level, int *count, double *sum){
    if(tn == NULL) return;
    count[level]++;
    sum[level]+=tn->val;
    ++level;
    dealOfLevel(tn->left, level, count, sum);
    dealOfLevel(tn->right, level, count, sum);
    return;
}

double* averageOfLevels(struct TreeNode* root, int* returnSize) {
    //Binary Tree depth
    int dep = 0;
    dep = depth(root);
    if(dep == 0) {*returnSize = 0; return NULL;}
    //calculate sum & count of Binary Tree average level
    int *total_count;
    total_count = (int*)calloc(1, dep * sizeof(int));
    double *total_sum;
    total_sum = (double*)calloc(1, dep * sizeof(double));
    dealOfLevel(root, 0, total_count, total_sum);
    int i;
    double *rt;
    rt = (double*)malloc(dep * sizeof(double));
    for(i = 0; i < dep; i++) {
        rt[i] = total_sum[i] / total_count[i];
    }
    free(total_count);
    free(total_sum);
    *returnSize = dep;
    return rt; 
}

void main(void){

}
