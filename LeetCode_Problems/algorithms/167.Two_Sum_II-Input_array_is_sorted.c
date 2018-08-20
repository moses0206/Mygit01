/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int i, j, k, sum;
    for(k = 1; k < numbersSize; k++) {
        if (numbers[k] > target - numbers[0])
            break;
    }
    i = 0, j = k-1;
    while(i < j) {
        sum = numbers[i] + numbers[j];
        if (sum == target) break;
        else {
            if (sum < target) i++;
            else j--;
        }
    }
    if (i < j) {
        int *rt = (int *)malloc(sizeof(int) * 2);
        rt[0] = i+1;
        rt[1] = j+1;
        *returnSize = 2;
        return rt;
    }
    return NULL;
}
