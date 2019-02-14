#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool wordPattern(char* pattern, char* str) {
    char ** map = (char **)calloc(1, sizeof(char*) * 128);
    int p = 0;
    char *ptr = NULL;
    while('\0' != *pattern) {
        while(*str == ' ') str++;
        p = 0;
        ptr = str;
        while(*ptr != ' ' && *ptr != '\0') {p++; ptr++;}
        if(p == 0) return false;
        char * tmp_s = calloc(1, sizeof(char) * (p+1));
        tmp_s = (char*)memcpy(tmp_s, str, p);
        str += p;
        if(NULL == map[(int)*pattern]) {
            map[(int)*pattern] = tmp_s;
        } else {
            if(0 != strcmp(map[(int)*pattern], tmp_s)) return false;
            else free(tmp_s);
        }
        pattern++;
    }
    while(*str != '\0') {
        if(*str != ' ') return false;
        str++;
    }
    int i;
    for(i = 0; i < 127; i++) {
        if(map[i]) {
            for(int j = i + 1; j < 128; j++) {
                if(map[j] && !strcmp(map[i], map[j])) return false; 
            }
            free(map[i]);
        }
    }
    if(map[i]) free(map[i]);
    return true;
}
