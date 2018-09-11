#include <stdlib.h>
#include <stdio.h>

/**
  本解法是在v3版本上改进的
  改进点P1：只要 n >= 3，就一定包含2这个素数，而P2处可以直接从3开始。
            注意，j要定义成 long long，否则P3处会溢出。
  改进点P2：直接从3开始，然后忽略所有的偶数，省去了至少一半的遍历。
  改进点P3：从i*i开始筛掉合数而不是从i+i，是因为要筛去所有的i的倍数，
            步长是i，即筛去  2*i, 3*i, 4*i, 5*i, 6*i, 7*i, ... i*i ...直到>=n，
            而不管是几乘以i，只要比i小的，在i之前的筛选时其实就已经被筛掉了，
            就上例来说，在P2处即筛去了所有偶数，而3*i其实已经在i曾是3时，就已经筛去了当前的 3*i,
            4*i也早被筛去了，5*i也和3*i一个道理，之前就筛去了，6*i，7*i也一样。
            所以，可以直接从i*i开始筛去。
            还有一点要注意，就是两个int做运算时是会将结果也当作int处理的，然后再赋值给j，所以运算前就要强转类型。
  */

int countPrimes(int n) {
    if (n < 3) return 0;
    int i, count = 1;                       //P1
    long long j;
    int *arr = calloc(n, sizeof(int));
    for (i = 3; i < n; i+=2) {              //P2
        if (arr[i] == 0) {
            count++;
            for (j = (long long)i*i; j < n; j+=i) {    //P3
                arr[j] = 1;
            }
        }
    }
    free(arr);
    return count;
}

int main(void) {
    int n = 499979;
    printf("Primes Number:%d\n", countPrimes(n));
    return 0;
}

