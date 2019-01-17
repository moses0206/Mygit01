int missingNumber1(int* nums, int numsSize) {
    long long sum = 0;
    for(int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }
    long long re_sum = ((numsSize + 1)/2 * (long long)numsSize)
                       +
                       ((numsSize + 1) % 2 * (numsSize/2));
    return re_sum - sum;
}
int missingNumber2(int* nums, int numsSize) {
    long long sum = 0;
    int i = 0;
    for(; i < numsSize; i++) {
        sum = sum + i + nums[i];
    }
    return (int)(sum + i);
}
