#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target) {
    int i, j, flag = 0;
    for(i = 0; i < numsSize - 1; i++) {
        for(j = i + 1; j < numsSize; j++) {
            if(nums[i] + nums[j] == target) {
                flag = 1;
                break;
            }
        }
        if(flag == 1) break;
    }
    int* rt = (int*)malloc(2 * sizeof(int));
    rt[0] = i;
    rt[1] = j;
    return rt;
}


int main(void) {
    int nums[4] = {2, 7, 11, 15};
    int* rt;
    rt = twoSum(nums, 4, 26);
    printf("[%d, ", rt[0]);
    printf("%d]\n", rt[1]);
}
