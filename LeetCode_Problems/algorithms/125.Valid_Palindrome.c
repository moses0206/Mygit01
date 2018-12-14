#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int judgeChar(char ch) {
    if((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) {
        return (int)ch;
    }
    if(ch >= 'A' && ch <= 'Z') {
        return (int)(ch + ('a' - 'A'));
    }
    return 0;
}
bool isPalindrome(char* s) {
    int strLen = strlen(s);
    if(strLen < 2) return true;
    int i = 0, j = strLen - 1;
    int chI = 0, chJ = 0;
    while(i < j) {
        chI = judgeChar(s[i]);
        chJ = judgeChar(s[j]);
        if((0 == chI) && (0 == chJ)) {
            i++; j--; continue;
        }
        if(0 == chI) {
            i++; continue;
        }
        if(0 == chJ) {
            j--; continue;
        }
        if(chI != chJ) {
            return false;
        }else {
            i++; j--;
        }
    }
    return true;
}
