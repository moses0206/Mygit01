#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int convert(char *p, int *power) {
    if (*p == '\0') {
        *power = 0;
        return 0;
    }
    int low_sum, sum;
    low_sum = convert(p+1, power);
    sum = low_sum + (*p - 'A' + 1)*pow((double)26, (double)*power);
    (*power)++;
    return sum;
}

int titleToNumber(char *s) {
    if (*s == '\0') return 0;
    int power = 0;
    return convert(s, &power);
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
