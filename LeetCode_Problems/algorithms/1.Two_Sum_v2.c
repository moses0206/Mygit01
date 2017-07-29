#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target) {
    int* rt = (int*)malloc(2 * sizeof(int));
    if(numsSize < 3) {
        rt[0] = 0;
        rt[1] = 1;
    } else {
        int i;
        int min, max;
        min = max = nums[0];
        for(i = 1; i < numsSize; i++) {
            if(min > nums[i]) min = nums[i];
            if(max < nums[i]) max = nums[i];
        }
        max -= min;

        int *hash = (int*)calloc(1, (max+1) * sizeof(int));
        for(i = 0; i < numsSize; i++) {
            hash[nums[i]-min] = i + 1;
        }

        int tmp;
        for(i = 0; i < numsSize; i++) {
            tmp = target - nums[i];
            if(tmp > max+min || tmp < min) continue;
            tmp = hash[target - nums[i] - min];
            if(tmp && tmp!= (i + 1))
                break;
        }

        rt[0] = i;
        rt[1] = hash[target - nums[i] -min] -1;
    }
    return rt;
}

void main(void) {
    int nums[5] = {-1, -2, -3, -4, -5};
    int* rt;
    rt = twoSum(nums, 5, -8);
    printf("[%d, ", rt[0]);
    printf("%d]\n", rt[1]);
}
