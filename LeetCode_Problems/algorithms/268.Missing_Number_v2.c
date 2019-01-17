int missingNumber(int* nums, int numsSize) {
    int xor = 0, i = 0;
    for(; i < numsSize; i++) {
        xor = xor ^ i ^ nums[i];
    }
    return xor ^ i;
}
