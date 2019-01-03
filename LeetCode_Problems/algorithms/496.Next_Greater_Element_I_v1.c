#include <stdio.h>
#include <stdlib.h>

int* nextGreaterElement(int* fn, int fns, int* n, int ns, int* rts) {
    int i, j;
    int *rt;
    int flag;
    rt = (int*)malloc(fns * sizeof(int));
    for(i = 0; i < fns; i++) {
        flag = -1;
        for(j = 0; j < ns; j++) {
            if(n[j] == fn[i]) {
                flag = 0;
                continue;
            }
            if(flag == 0 && n[j] > fn[i]) {
                flag = 1;
                break;
            }
        }
        rt[i] = (flag == 1? n[j]: -1);
    }
    *rts = i;
    return rt;
}

int main(void) {
//    int *nums1, *nums2;
//    nums1 = (int*)malloc(6 * sizeof(int));
//    nums2 = (int*)malloc(12 * sizeof(int));
//    nums1 
    int nums1[8] = { 2, 9, 10, 1, 5, 11, 4, 7};
    int nums2[12] = { 2, 4, 8, 1, 6, 12, 9, 5, 11, 7, 3, 10};
    int *rt, rts;
    rt = nextGreaterElement(nums1, 8, nums2, 12, &rts);
    int i;
    for(i = 0 ; i < 8; i++) {
        printf("%d,", nums1[i]);
    }
    puts("");
    for(i = 0 ; i < 12; i++) {
        printf("%d,", nums2[i]);
    }
    puts("");
    for(i = 0 ; i < rts; i++) {
        printf("%d,", rt[i]);
    }
    puts("");
}
