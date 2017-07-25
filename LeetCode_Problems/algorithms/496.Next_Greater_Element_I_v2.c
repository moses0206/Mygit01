#include <stdio.h>
#include <stdlib.h>

int* nextGreaterElement(int* fn, int fns, int* n, int ns, int* rts) {
    if(fn == NULL || fns < 1 || n == NULL || ns < 1) {
        if(rts != NULL) *rts = 0;
        return NULL;
    }
    *rts = fns;
    int i, j, max, min;
    max = n[0];
    min = n[0];
    for(i = 1; i < ns; i++) {
        if(max < n[i]) max = n[i];
        if(min > n[i]) min = n[i];
    }
    int offset = 0;
    if(min < 0) max+=(-min);
    else max-=min;
    offset = (-min);
    int *rt;
    rt = (int*)malloc(fns * sizeof(int));
    int *hash_n;
    hash_n = (int*)malloc((max+1) * sizeof(int));
    for(i = 0; i < ns-1; i++) {
        hash_n[n[i] + offset] = -1;
        for(j = i+1; j < ns; j++) {
            if(n[j] > n[i]) {
                hash_n[n[i] + offset] = n[j];
                break;
            }
        }
    }
    hash_n[n[i] + offset] = -1;

    for(i = 0; i < fns; i++) {
        rt[i] = hash_n[fn[i] + offset];
    }
    free(hash_n);
    return rt;
}

void main(void) {
//    int *nums1, *nums2;
//    nums1 = (int*)malloc(6 * sizeof(int));
//    nums2 = (int*)malloc(12 * sizeof(int));
//    nums1 
    int nums1[7] = {3,1,5,7,9,2,6};
    int nums2[8] = {1,2,3,5,6,7,9,11};
    int *rt, rts;
    rt = nextGreaterElement(nums1, 7, nums2, 8, &rts);
    int i;
    for(i = 0 ; i < 7; i++) {
        printf("%d,", nums1[i]);
    }
    puts("");
    for(i = 0 ; i < 8; i++) {
        printf("%d,", nums2[i]);
    }
    puts("");
    for(i = 0 ; i < rts; i++) {
        printf("%d,", rt[i]);
    }
    puts("");
}
