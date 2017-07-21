#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* reverseWords(char* s) {
    char * temp, *rt;
    temp = (char *)malloc(strlen(s) + 1);
    rt = (char *)malloc(strlen(s) + 1);
    *(temp + strlen(s)) = '\0';
    *(rt + strlen(s)) = '\0';
    int index = strlen(s) -1;
    char * p = temp;
    while( index >= 0) {
        *(p++) = *(s + index);
        index--;
    }
    index = strlen(s) -1;
    int n = 0;
    while(index >= 0) {
        if(index == 0){
            strncpy(rt + n, temp + index, strlen(temp + index));
            n+= strlen(temp + index);
        }
        if(*(temp + index) == ' '){
            *(temp + index) = '\0';
            strncpy(rt + n, temp + index + 1, strlen(temp + index + 1));
            n+= strlen(temp + index + 1);
            *(rt + n) = ' ';
            n++;
        }
        index--;
    }

    return rt;
}

void main(void) {
    char * test = "Let's take LeetCode contest";
    char * rt;
    puts(test);
    rt = reverseWords(test);
    puts(rt);
}
