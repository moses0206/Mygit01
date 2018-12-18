#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * 该解法是通过实现一个哈希表来实现的，只是在插入哈希表的时候多做一下判重校验。
 * 这也是借鉴的LeetCode上的解法。
 */

typedef struct hashlist {
    int val;
    struct hashlist *next;
} list;

bool containsDuplicate(int* nums, int numsSize) {
    if(numsSize < 2) return false;
    int mask = numsSize;
    list * tmp[numsSize];           //注意，此处不能做初始化操作，因为大小不确定。
    memset(tmp, 0, sizeof(list) * numsSize);    //此处必须初始化
    for(int i = 0; i < numsSize; ++i) {
        list *node = calloc(1, sizeof(list));
        node->val = nums[i];
        int idx = abs(nums[i]) % mask;
        list *p = tmp[idx];
        node->next = p;
        tmp[idx] = node;
        while(p) {
            if(p->val == node->val) {
                return true;
            }
            p = p->next;
        }
    }
    return false;
}
