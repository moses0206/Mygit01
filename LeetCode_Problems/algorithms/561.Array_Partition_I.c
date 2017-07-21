#include <stdio.h>
#include <stdlib.h>

int neipai(int *nums, int left, int right){
    int target = nums[left];
    int pos = left;
    int var, i;
    for(i = left + 1; i <= right; i++){
        if(nums[i] < target){
            pos++;
            var = nums[i];
            nums[i] = nums[pos];
            nums[pos] = var;
        }
    }
    var = nums[left];
    nums[left] = nums[pos];
    nums[pos] = var;
    return pos;
}

void quicksort(int *nums, int left, int right) {
    if (left > right) return;
    int pos = neipai(nums, left, right);
    quicksort(nums, left, pos - 1);
    quicksort(nums, pos + 1, right);
}

int main(int argc, char **argv) {
    int numsSize = argc - 1;
    int nums[numsSize];
    int i;
    for (i = 0; i < numsSize; i++){
        nums[i] = atoi(argv[i+1]);
        printf(" %3d", nums[i]);
    }
    printf("\n");

    int sum = 0;
    quicksort(nums, 0, numsSize - 1);
    for (i = 0; i < numsSize; i++) {
        printf(" %3d", nums[i]);
    }
    printf("\n");

    for (i = 0; i < numsSize; i += 2) {
        sum += nums[i];
        printf(" %3d", nums[i]);
        printf("    ");
    }
    printf("\n");
    printf("   %d\n", sum);
    return 0;
}
