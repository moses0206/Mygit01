#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* reverseWords(char* s) {
    char * rt;
    rt = (char *)malloc(strlen(s) + 1);
    *(rt + strlen(s)) = '\0';
    char *p = s;
    int i, jishu = 0;
    int s_p = 0;
    int rt_p = 0;
    for(;*p != '\0'; p++) {
        if(*p == ' '){
            for( i = s_p - 1; i >= (s_p - jishu); i--){
                *(rt + rt_p) = *(s + i);
                rt_p++; 
            }
            jishu = 0;
            *(rt + rt_p) = ' ';
            rt_p++;
            s_p++;
        }else{
            jishu++;
            s_p++;
        }
    }
    if( *(p-1) != ' '){
        for( i = s_p -1; i>= (s_p - jishu); i--){
            *(rt + rt_p) = *(s + i);
            rt_p++;
        }
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
