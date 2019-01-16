#include <stdbool.h>

bool isAnagram(char* s, char* t) {
    int arr[26] = {0};
	for(; *s != '\0'; ++s) {
        arr[*s - 'a']++;
    }
	for(; *t != '\0'; ++t) {
        arr[*t - 'a']--;
    }
    for(int i = 0; i < 26; ++i) {
        if(arr[i] != 0) return false;
    }
    return true;
}
