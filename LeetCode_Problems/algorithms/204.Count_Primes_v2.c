#include <stdlib.h>
#include <stdio.h>

typedef struct marray {
    int size;
    int used;
    int *p;
} marray_t;

marray_t * marray_new(int size) {
    marray_t * rt = NULL;
    int *p = NULL;
    if (NULL == (rt = (marray_t *)calloc(1, sizeof(marray_t)))) return NULL;
    if (NULL == (p = (int *)malloc(size * sizeof(int)))) {
        free(rt);
        return NULL;
    }
    rt->p = p;
    rt->size = size;
    rt->used = 0;
    return rt;
}

void marray_free(marray_t *m) {
    free(m->p);
    free(m);
}

void marray_add(marray_t *m, int val) {
    m->p[m->used++] = val;
}

int countPrimes(int n) {
    int i, j;
    if (n < 3) return 0;
    marray_t *pri = marray_new(1 << 16);
    marray_add(pri, 2);
    for (i = 3; i < n; i+=2) {
        for (j = 0; j < pri->used; j++) {
            if (i % pri->p[j] == 0) break;
        }
        if (j == pri->used) marray_add(pri, i);
    }
    int rt = pri->used;
    for (i = 0; i < pri->used; i++) {
        printf("pri[%d] = %d,\t", i, pri->p[i]);
        if ((i+1) % 5 == 0) printf("\n");
    }
    marray_free(pri);
    return rt;
}

int main(void) {
    int n = 499979;
    printf("Primes Number:%d\n", countPrimes(n));
    return 0;
}
