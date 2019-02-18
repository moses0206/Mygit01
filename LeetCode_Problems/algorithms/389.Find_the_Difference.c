char findTheDifference(char* s, char* t) {
    int apper[128] = {0};
    while(*s) {
        apper[(int)*s++]--;
        apper[(int)*t++]++;
    }
    apper[(int)*t]++;
    for(int i = 97; i < 123; i++) {
        if(apper[i] == 1) return (char)i; 
    }
    return 'a';
}
