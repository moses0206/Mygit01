#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

//int depth(struct TreeNode* tn) {
//    if(tn == NULL) return 0;
//    else {
//        int depl, depr;
//        depl = depth(tn->left);
//        depr = depth(tn->right);
//        return (1 + (depl > depr? depl: depr));
//    }
//}
/*
*   level   : tn的所在层(从0开始); 
*   dep     : tn之前已知的最深层数(从1开始);
*   size    : 到tn为止已知的最深层数(从1开始);
*/
int dealOfLevel(struct TreeNode* tn, int level, int **count, double **sum, int dep){
    if(tn == NULL) return dep;
    int depl, depr;
    if(level + 1 > dep) {  //如果tn这层+1 大于 之前已知的最深层数
        *count = realloc(*count, (dep + 1) * sizeof(int));
        *sum = realloc(*sum, (dep + 1) * sizeof(double));
        (*count)[dep] = 0;
        (*sum)[dep] = 0;
        dep++;
    }
    (*count)[level]++;
    (*sum)[level]+=tn->val;
    dep = dealOfLevel(tn->left, level + 1, count, sum, dep);
    dep = dealOfLevel(tn->right, level + 1, count, sum, dep);
    return dep;
}

double* averageOfLevels(struct TreeNode* root, int* returnSize) {
    //Binary Tree depth
    int dep;
    //calculate sum & count of Binary Tree average level
    int *total_count = (int*)calloc(0, sizeof(int));
    double *total_sum = (double*)calloc(0, sizeof(double));
    dep = dealOfLevel(root, 0, &total_count, &total_sum, 0);
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

int main(void){

}
