#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define C2D(x) (x - '0')

char* addStrings(char* num1, char* num2) {
    int len1 = strlen(num1), len2 = strlen(num2);
    int bigger = len1 > len2 ? len1 : len2;
    char * rt = calloc(1, (bigger + 2) * sizeof(char));
    int i = len1 - 1, j = len2 - 1;
    int carry = 0, cnt = bigger;
    for(; i >= 0 && j >= 0; i--, j--) {
        rt[cnt--] = '0' + ((C2D(num1[i]) + C2D(num2[j]) + carry) % 10);
        carry = (C2D(num1[i]) + C2D(num2[j]) + carry) / 10;
    }
    for(; i >= 0; i--) {
        rt[cnt--] = '0' + ((C2D(num1[i]) + carry) % 10);
        carry = (C2D(num1[i]) + carry) / 10;
    }
    for(; j >= 0; j--) {
        rt[cnt--] = '0' + ((C2D(num2[j]) + carry) % 10);
        carry = (C2D(num2[j]) + carry) / 10;
    }
    if(carry == 1) {
        rt[cnt--] = '1';
    }
    return &(rt[cnt+1]);
}

char* addStrings2(char *num1, char *num2) {
    if(strlen(num1) < strlen(num2)) return addStrings2(num2, num1);
    int carry = 0;
    int i = strlen(num1) - 1;
    int j = strlen(num2) - 1;
    for(; i >= 0 && (carry || j >= 0); i--, j--, carry /= 10) {
        num1[i] = (carry += (num1[i] - '0' + (j >= 0 ? num2[j] - '0' : 0))) % 10 + '0';
    }
    if(!carry) return num1;
    char *rt = calloc(strlen(num1) + 2, sizeof(char));
    rt[0] = '1';
    strcpy(&rt[1], num1);
    return rt;
}
