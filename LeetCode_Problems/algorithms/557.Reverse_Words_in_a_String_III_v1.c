#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(int b, int e, char *s) {
    while(b < e) {
        s[b] = s[b] ^ s[e];
        s[e] = s[b] ^ s[e];
        s[b] = s[b] ^ s[e];
        b++;
        e--;
    }
}

char* reverseWords(char* s) {
    int index = 0, s_len = strlen(s);
    int i;
    for(i = 0; i <= s_len; i++) {
        if((s[i] == ' ') || (s[i] == '\0')){
            reverse(index, i - 1, s);
            index = i + 1;
        }
    }
    return s;
}

void main(void) {
    char test[] = "Let's take LeetCode contest";
    char * rt;
    puts(test);
    rt = reverseWords(test);
    puts(rt);
}
