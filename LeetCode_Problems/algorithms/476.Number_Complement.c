#include <stdio.h>
#include <math.h>

int findComplement(int num) {
    int i, flag = 0;
    int tmp_num = abs(num);
    if (num < 0) {
        flag = 1;
        tmp_num = (-num);
    }
    tmp_num = ~tmp_num;
    for(i = 31; i >= 0; i--) {
        if ( (tmp_num & (1 << i)) == 0) {
            tmp_num&=((1 << i) - 1);
            break;
        }
    }
    return (flag ? -tmp_num : tmp_num);
}

int main(void) {
    int num = 0;
    printf("Please input a integer:\n");
    scanf("%d", &num);
    printf("Input integer is %d, and its complement number is %d\n",
        num, findComplement(num));
    return 0;
}
