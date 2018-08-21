/**
  * Moore Voting Algorithm
  */

int majorityElement(int* nums, int numsSize) {
    int major = nums[0];
    int count = 1;
    int i;
    for(i = 1; i < numsSize; i++) {
        if(count == 0) {
            count++;
            major = nums[i];
        }else if(major == nums[i]) {
            count++;
        }else count--;
    }
    return major;
}
