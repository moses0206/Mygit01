#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* reverseString(char* s) {
    int len = strlen(s);
    int i, j = 0;
    char *rt;
    rt = (char*)malloc(len * sizeof(char) + 1);
    if(len > 0) 
        for(i = len - 1, j = 0; i >= 0; i--, j++){
            rt[j] = s[i];
        }
    rt[j] = '\0';
    return rt;
}

int main(void) {
    char * test = "i'm a man";
    char * rt;
    rt = reverseString(test);
    puts(rt);
}
