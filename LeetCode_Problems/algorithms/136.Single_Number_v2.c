#include <stdio.h>

//利用“异或”特性取解。
//相同的两个数的异或值为0。
int singleNumber(int *n, int ns) {
    int i, rt = 0;
    for(i = 0; i < ns; i++) {
        rt ^= n[i];
    }
    return rt;
}

void main(void) {
    int test[9] = {2, 5, 8, 2, 4, 3, 4, 5, 8};
    int i;
    printf("test[9] = { ");
    for(i = 0; i < 9; i++) {
        printf("%d", test[i]);
        if(i != 8) printf(", ");
        else printf(" }\n");
    }
    printf("SingleNumber is %d\n", singleNumber(test, 9));
}
