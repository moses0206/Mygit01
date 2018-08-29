#include <stdlib.h>
#include <stdio.h>

void rotate(int* nums, int numsSize, int k) {
#define POS ((j+k)%numsSize)
    if (numsSize < 2) return;
    k %= numsSize;
    int i, j, tmp = nums[0];
    int flag = 0;
    for (i = 0, j = 0; i < numsSize; ++i, j+=k) {
        if (POS == flag) {
            nums[POS] = tmp;
            tmp = nums[flag+1];
            j = flag + 1 - k;
            flag = flag + 1;
            continue;
        }
        tmp ^= nums[POS];
        nums[POS] ^= tmp;
        tmp ^= nums[POS];
    }
    return;
}

void main(void ) {
    int * arr = (int *)calloc(1, 6*sizeof(int));
    arr[0]= 1;
    arr[1]= 2;
    arr[2]= 3;
    arr[3]= 4;
    arr[4]= 5;
    arr[5]= 6;
    rotate(arr, 6, 3);
    int i;
    printf("[");
    for (i = 0; i < 6; ++i) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
}

