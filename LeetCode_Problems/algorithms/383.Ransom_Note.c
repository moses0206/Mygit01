#include <stdbool.h>

bool canConstruct(char* ransomNote, char* magazine) {
    int apper[128] = {0};
    for(;*ransomNote != '\0'; ransomNote++) {
        if(apper[(int)*ransomNote] == 0) {
            while(*magazine != '\0') {
                apper[(int)*magazine]++;
                magazine++;
                if(apper[(int)*ransomNote] > 0) break;
            }
            if(apper[(int)*ransomNote] == 0) return false;
        }
        apper[(int)*ransomNote]--;
    }
    return true;
}
