void rotate(int* nums, int numsSize, int k) {
    if (numsSize < 2) return;
    int i, j, tmp;
    k %= numsSize;
    for (i = 0; i < k; ++i) {
        tmp = nums[0];
        for (j = 1; j < numsSize; ++j) {
            tmp ^= nums[j];
            nums[j] ^= tmp;
            tmp ^= nums[j];
        }
        nums[0] = tmp;
    }
    return;
}
