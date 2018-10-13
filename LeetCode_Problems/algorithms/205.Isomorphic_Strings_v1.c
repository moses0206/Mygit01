bool isIsomorphic(char* s, char* t) {
    int i = 1;
    int map_s[128] = {0};
    int map_t[128] = {0};
    int first_posi_s[128] = {0};
    int first_posi_t[128] = {0};
    char *p  = s, *q = t;
    while(*p != '\0' && *q != '\0') {
        if(map_s[*p] == 0) first_posi_s[*p] = i;
        if(map_t[*q] == 0) first_posi_t[*q] = i;
        if(first_posi_s[*p] != first_posi_t[*q]) return false;

        map_s[*p]++;
        map_t[*q]++;
        if(map_s[*p] != map_t[*q])  return false;
        p++;
        q++;
        i++;
    }
    if(*p != '\0' || *q != '\0') {
        return false;
    } else {
        return true;
    }
    return true;
}
