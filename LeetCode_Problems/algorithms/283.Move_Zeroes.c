void moveZeroes(int* nums, int numsSize) {
    int cur = 0, zero = 0;
    while(cur < numsSize && nums[cur] != 0) {
        cur++;
    }
    zero = cur++;
    for(; cur < numsSize; cur++) {
        if(nums[cur] != 0) {
            nums[zero++] = nums[cur];
            nums[cur] = 0;
        }
    }
    return;
}
