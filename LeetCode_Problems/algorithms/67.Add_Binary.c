char* addBinary(char* a, char* b) {
#define CHAR2INT(_a, _p) (_a[_p] == '1' ? 1 : 0)
    int a_len = strlen(a), b_len = strlen(b);
    int max_len = a_len > b_len ? a_len : b_len;
    char *rt = calloc(1, max_len + 2);
    int sum = 0, carry = 0, i = 0;
    for(i = 0; i < max_len; i++) {
        if(i >= a_len) sum = CHAR2INT(b, b_len-i-1) + carry;
        else if(i >= b_len) sum = CHAR2INT(a, a_len-i-1) + carry;
        else sum = CHAR2INT(a,a_len-i-1) + CHAR2INT(b, b_len-i-1) + carry;
        carry = sum / 2;
        rt[i] = '0' + (sum % 2);
    }
    if(carry == 1) rt[i++] = '1';
    int left = 0, right = i - 1;
    while(left < right) {
        sum = rt[left];
        rt[left] = rt[right];
        rt[right] = sum;
        left++;right--;
    }
    return rt;
}
