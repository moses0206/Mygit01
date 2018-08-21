/**
  * Randomization
  * 随机检测法，该算法在此问题上非常有效，题设描述元素出现次数>n/2，随机到的概率很高。
  * 其次，在遍历数组时，随机的元素出现次数>n/2时及结束，也提高了效率。
  */
#include <stdlib.h>

int majorityElement(int* nums, int numsSize) {
    srand((unsigned)time(NULL));
    while(1) {
        int idx = rand() % numsSize;
        int candidate = nums[idx];
        int counts = 0;
        int i;
        for (i = 0; i < numsSize; i++)
            if (nums[i] == candidate)
                counts++;
        if (counts > numsSize / 2) return candidate;
    }
    return 0;
}
