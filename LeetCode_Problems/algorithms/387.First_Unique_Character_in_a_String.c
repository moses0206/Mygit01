int firstUniqChar(char* s) {
    int arr[128] = {0};
    char *ch = s;
    for(; *ch != '\0'; ch++) {
        arr[(int)*ch]++;
    }
    for(int pos = 0; s[pos] != '\0'; pos++) {
        if(arr[(int)s[pos]] == 1) return pos;
    }
    return -1;
}
