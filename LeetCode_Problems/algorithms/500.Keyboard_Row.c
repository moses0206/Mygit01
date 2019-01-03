#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** findWords(char** words, int wordsSize, int* returnSize) {
    unsigned int matrix[26] = {1, 0, 0, 1, 2, 1, 1, 1, 2, 1, 1, 1, 0, 0, 2, 2, 2, 2, 1, 2, 2, 0, 2, 0, 2, 0};
    if(wordsSize <= 0) return NULL;
    int flag[wordsSize];
    int index, count = 0;
    for(index = 0; index < wordsSize; index++) {
        char* p = words[index];
        unsigned int temp = ((*p >= 'a') ? matrix[*p - 'a'] : matrix[*p - 'A']);
        while( *p != '\0') {
            if( (*p > 'Z' && temp != matrix[*p - 'a']) || (*p < 'a' && temp != matrix[*p - 'A'])){
                break;
            }else{
                p++;
                continue;
            }
        }
        if(*p == '\0') {
            count++;
            flag[index] = 1;
        }else 
            flag[index] = 0;
    }
    * returnSize = count;
    if(count == 0) return NULL;
    char ** p = (char **)malloc(count * sizeof(char*));

    for(index = 0, count = 0; index < wordsSize; index++) {
        if(!flag[index]) continue;
        *(char**)(p + count) = (char*)malloc(strlen(words[index]) + 1);
        strncpy(*(char**)(p + count), words[index], strlen(words[index]));
        *(*(char**)(p + count) + strlen(words[index])) = '\0';
        count++;
    }
    return p;
}

int main(void) {
    char * test[4] = {"Hello", "Alaska", "Dad", "Peace"};
    int count;
    char ** result = findWords(test, 4, &count);
    while( count > 0){
        printf("%s\n", result[count - 1]);
        count--;
    }
}
