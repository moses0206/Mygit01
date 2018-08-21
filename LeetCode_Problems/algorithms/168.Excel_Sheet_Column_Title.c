#include <stdio.h>
#include <stdlib.h>

char * convert(char *p, int n) {
    if (!n) return p;
    char * new  = convert(p, (n-1)/ 26);
    *new = 'A' + (n-1) % 26;
    return new+1;
}

char *convertToTitle(int n) {
    if (n <= 0) return NULL;
    char *p = (char*)calloc(1, 32);
    convert(p, n);
    return p;
}

int main(void) {
    int a;
    scanf("%d", &a);
    while(a != 0) {
        char *p = convertToTitle(a);
        printf("i[%d] = %s\n", a, p);
        free(p);
        scanf("%d", &a);
    }
    return 0;
}
