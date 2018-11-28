bool isIsomorphic(char* s, char* t) {
    int i = 1;
    int first_posi_s[128] = {0};
    int first_posi_t[128] = {0};

    while(*s != '\0' && *t != '\0') {
        if(first_posi_s[*s] == 0) {
            first_posi_s[*s] = i;
        }
        if(first_posi_t[*t] == 0) {
            first_posi_t[*t] = i;
        }
        if(first_posi_s[*s] != first_posi_t[*t]) {
            return false;
        }
        s++;
        t++;
        i++;
    }
    if(*s != '\0' || *t != '\0') {
        return false;
    }

    return true;
}
