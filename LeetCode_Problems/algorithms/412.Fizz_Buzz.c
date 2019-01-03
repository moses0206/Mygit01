#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** fizzBuzz(int n, int* returnSize) {
    if(n < 1) {
        *returnSize = 0;
        return NULL;
    }
    char ** rt;
    rt = (char**)malloc(n * sizeof(char*));
    int i;
    for(i = 1; i <= n; i++) {
        rt[i - 1] = (char*)calloc(1, 16 * sizeof(char));
        if(i % 15 == 0){
            strcpy(rt[i - 1], "FizzBuzz\0");
        }else if(i % 3 == 0) {
            strcpy(rt[i - 1], "Fizz\0");
        }else if(i % 5 == 0) {
            strcpy(rt[i - 1], "Buzz\0");
        }else {
            snprintf(rt[i - 1], 16, "%d", i);
        }
    }
    *returnSize = n;
    return rt;
}

int main(void) {
    int rs, i;
    char ** rt = fizzBuzz(60, &rs);
    for(i = 0; i < rs; i++) {
        printf("%s\n", rt[i]);
    }
}
