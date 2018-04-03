int uniqueMorseRepresentations(char** words, int wordsSize) {
    unsigned long long morse[26] = { 0x1,0x8,0xA,0x4,0x0,0x2,0x6,0x0,0x0,0x7,0x5,0x4,0x3,0x2,0x7,
                                    0x6,0xD,0x2,0x0,0x1,0x1,0x1,0x3,0x9,0xB,0xC};
    int m_len[26] = {2,4,4,3,1,4,3,4,2,4,3,4,2,2,3,
                        4,4,3,3,1,3,4,3,4,4,4};
    int i, j;
    unsigned long long m_str[100] = {0};
    for(i = 0; i < wordsSize; i++) {
        j = 0;
        while(words[i][j] != '\0') {
            m_str[i] = (m_str[i] << m_len[words[i][j]-'a']) | morse[words[i][j]-'a'];
            j++;
        }
    }
    int count = wordsSize;
    for(i = 0; i < wordsSize-1; i++) {
        for(j = i+1; j < wordsSize; j++) {
            if(!(m_str[i] ^ m_str[j])) {
                count--;
                break;
            }
        }
    }
    return count;
}
/*
int main(void) {
    char * words[] = {"rwjje","aittjje","auyyn","lqtktn","lmjwn"};
    printf("count = %d\n", uniqueMorseRepresentations(words, 5));
    return 0;
}
*/
