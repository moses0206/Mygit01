#include <stdio.h>
void main(void) {
    int a;
    a = reverse(-2147483648);
    printf("a = %d\n", a);
}

int reverse(int x) {
    int flag = 1;
    if(x == -2147483648) return 0;
    if(x < 0) {
        flag = -1;
        x = -x;
    }
    long long rt = 0;
    while(x/10) {
        rt = rt*10 + (x%10);
        x = x / 10;
    }
    rt = rt*10 + x;
    if(rt > (((long long)1 << 31) - 1)) return 0;
    else return flag*((int)rt);
}
