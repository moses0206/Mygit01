#include <stdio.h>

int sort(int* n, int l, int r){
    int i, tmp;
    int pos = l;
    int obj = n[l];
    for(i = l+1; i <= r; i++) {
        if(n[i] < obj) {
            pos++;
            tmp = n[i];
            n[i] = n[pos];
            n[pos] = tmp;
        }
    }
    tmp = n[l];
    n[l] = n[pos];
    n[pos] = tmp;
    return pos;
}

void q_sort(int* n, int l, int r){
    if(l > r) return;
    int pos = sort(n, l, r);
    q_sort(n, l, pos-1);
    q_sort(n, pos+1, r);
}

int singleNumber(int* nums, int numsSize) {
    if(!(numsSize%2)) return 0;
    q_sort(nums, 0, numsSize-1);
    int i;
    int rt;
    for(i = 1; i < numsSize; i+=2) {
        if(nums[i] != nums[i-1]) {
            return nums[i-1];
        }
    }
    return nums[i-1];
}

void main(void) {
}
