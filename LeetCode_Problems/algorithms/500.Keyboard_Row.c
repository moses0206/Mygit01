#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** findWords(char** words, int wordsSize, int* returnSize) {
    unsigned int list[26] = { 1, 0, 0, 1, 2, 1, 1, 1, 2, 1, 1, 1, \
        0, 0, 2, 2, 2, 2, 1, 2, 2, 0, 2, 0, 2, 0};
    int i;
    int flag[1000] = {0};
    char *p;
    for (i = 0; i < wordsSize; i++) {
        p = words[i];
        flag[i] = 1;
        unsigned int tmp = ( (*p >= 'a') ? list[(*p - 'a')] : list[(*p - 'A')]);
        while(*p != '\0') {
            if ( *p >= 'a')
                if ( list[(*p - 'a')] != tmp) {
                    flag[i] = 0;
                    break;
                }else {
                    p++;
                    continue;
                }
            if ( list[(*p - 'A')] != tmp) {
                flag[i] = 0;
                break;
            }else {
                p++;
                continue;
            }
        }
    }
    int rtsize = 0;
    for (i = 0; i < wordsSize; i++)
        rtsize += flag[i];
    *returnSize = rtsize;
    char **rt;
    if (rtsize == 0) return NULL;
    rt = (char **)malloc(sizeof(char*) * rtsize);
    printf("rt = %p\n", rt);
    int j = 0;
    for ( i = 0; i < wordsSize; i++){
        if (!flag[i]) {  continue;}
        printf("rt[%d] = %p\n", j, rt + j);
        *(rt + j) = (char *)malloc(strlen(words[i]) + 1);
        strncpy(*(rt + j), words[i], strlen(words[i]));
        *(*(rt + j) + strlen(words[i])) = '\0';
        j++;
    }
    return rt;
}

void main(void) {
    char* words[4] = {"Hello", "Alaska", "Dad", "Peace" };
    int i;
    int  returnSize;
    char ** pp = findWords(words, 4, &returnSize);
    printf("returnSize = %d\n", returnSize);
    for(i = 0; i < returnSize; i++)
        printf("%s\n", pp[i]);
}


