#include <stdlib.h>

int ** generate(int numRows, int** columnSizes) {
    if(numRows < 1) return NULL;
    int i = 0, j = 0;
    int **rt = calloc(1, numRows * sizeof(int *));
    int *col_size = calloc(1, numRows * sizeof(int));
    int *cur_arr = NULL;
    for(i = 0; i < numRows; i++) {
        cur_arr = calloc(1, (i + 1) * sizeof(int));
        col_size[i] = i + 1;
        cur_arr[0] = 1;
        cur_arr[i] = 1;
        for(j = 1; j < i; j++) {
            cur_arr[j] = rt[i-1][j-1] + rt[i-1][j];
        }
        rt[i] = cur_arr;
    }
    *columnSizes = col_size;
    return rt;
}
