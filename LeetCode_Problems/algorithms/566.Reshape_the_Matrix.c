#include <stdio.h>
#include <stdlib.h>


int** matrixReshape(int** nums, int numsRowSize, int numsColSize, int r, int c, int** columnSizes, int* returnSize) {
    if(numsRowSize * numsColSize != r *c) {
        r = numsRowSize;
        c = numsColSize;
    }
    *returnSize = r;
    int **rt;
    rt= (int**)malloc(r * sizeof(int*));
    *columnSizes = (int *)malloc(r * sizeof(int));
    int i;
    for(i = 0; i < r; i++) {
        rt[i] = (int*)malloc(c * sizeof(int));
        (*columnSizes)[i] = c;
    }
    for(i = 0; i < numsRowSize * numsColSize; ++i) {
        rt[i/c][i%c] = nums[i/numsColSize][i%numsColSize];
    }
    return rt;
}

int main(void){
    int **test = (int **)malloc(2 * sizeof(int*));
    test[0] = (int*)malloc(3 * sizeof(int));
    test[1] = (int*)malloc(3 * sizeof(int));
    int t, k;
    int number = 0;
    for(t = 0; t < 2; t++) {
        for(k = 0; k < 3; k++)
            test[t][k] = (number++);
    }
    int * columnSizes, returnSize;
    int ** rt = matrixReshape((int **)test, 2, 3, 3, 2, &columnSizes, &returnSize);
    int i, j;
    for(i = 0; i < returnSize; i++) {
        for(j = 0; j < columnSizes[i]; j++) {
            if(columnSizes[i] == (j + 1)) printf("%d", rt[i][j]);
            else printf("%d,", rt[i][j]);
        }
        printf("\n");
    }
}
