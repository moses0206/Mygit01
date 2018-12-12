#include <stdlib.h>

/**
  * 第一个是笨办法解
  */

int* getRow(int rowIndex, int* returnSize) {
    if(rowIndex < 0) return NULL;
    int *rt = calloc(1, (rowIndex + 1) * sizeof(int));
    *returnSize = rowIndex + 1;
    rt[0] = 1;
    if(rowIndex < 1) { return rt; }
    rt[1] = 1;
    int i = 0, j = 0;
    int pre = 0, tmp = 0;
    for(i = 2; i <= rowIndex; i++) {
        pre = 1;
        for(j = 1; j < i; j++) {
            tmp = rt[j];
            rt[j] = rt[j] + pre;
            pre = tmp;
        }
        rt[j] = 1;
    }
    return rt;
}

/**
  * 第二个好一些
  */

int* getRow(int rowIndex, int* returnSize) {
    if(rowIndex < 0) return NULL;
    int *rt = calloc(1, (rowIndex + 1) * sizeof(int));
    *returnSize = rowIndex + 1;
    rt[0] = 1;
    int i = 0, j = 0;
    for(i = 1; i <= rowIndex; i++) {
        for(j = i; j > 0; j--) {
            rt[j] = rt[j] + rt[j-1];
        }
    }
    return rt;
}
