#define max(a, b) ((a > b)?(a):(b))
int maxSubArray(int* nums, int numsSize) {
    if (numsSize < 1) return 0;
    int sum = 0;
    int i = 0;
    int res = 0;
    int maxN = nums[0];
    for (i = 0; i < numsSize; i++) {
        sum += nums[i];
        maxN = max(maxN,nums[i]);
        res = max(res,sum);
        sum = max(sum,0);
    }
    if (maxN < 0) return maxN;
    return res;
}
