#include <string.h>

int longestPalindrome(char* s) {
    int a[128] = {0};
    int sum = 0;
    char * p = s;
    for(;*p; p++) {
        a[(int)*p]++;
        if(a[(int)*p]%2 == 0) sum+=2;
    }
    return (int)strlen(s) == sum ? sum: sum+1;
}
