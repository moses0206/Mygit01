#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int titleToNumber(char *s) {
    int result = 0;
    int i;
    for (i = 0; i < strlen(s); i++)
        result = result * 26 + (s[i] - 'A' + 1);
    return result;
}

int main(void) {
    char *s1 = "A";
    char *s2 = "AB";
    char *s3 = "ZY";
     printf("Your Input:%s, %d\n", s1, titleToNumber(s1));
     printf("Your Input:%s, %d\n", s2, titleToNumber(s2));
     printf("Your Input:%s, %d\n", s3, titleToNumber(s3));
    return 0;
}
