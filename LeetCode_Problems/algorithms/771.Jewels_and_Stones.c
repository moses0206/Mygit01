int numJewelsInStones(char* J, char* S) {
    int hash[256] = {0} , c = 0;
    while(*J != '\0') {
        hash[*J] = 1;
        J++;
    }
    while(*S != '\0') {
        if(hash[*S])
            c++;
        S++;
    }
    return c;
}
