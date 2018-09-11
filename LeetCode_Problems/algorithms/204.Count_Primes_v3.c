#include <stdlib.h>
#include <stdio.h>

/**
  本解法使用埃拉托色尼筛选法(Sieve of Eratosthenes)，步骤如下：
  （1）先把1删除（现今数学界1既不是质数也不是合数）
  （2）读取队列中当前最小的数2，然后把2的倍数删去
  （3）读取队列中当前最小的数3，然后把3的倍数删去
  （4）读取队列中当前最小的数5，然后把5的倍数删去
  （5）读取队列中当前最小的数7，然后把7的倍数删去
  （6）如上所述直到需求的范围内所有的数均删除或读取
*/

int countPrimes(int n) {
    if (n < 3) return 0;
    int i, j, count = 0;
    int *arr = calloc(n, sizeof(int));
    arr[0] = -1;
    arr[1] = -1;
    for (i = 2; i < n; i++) {
        if (arr[i] == 0)
            for (j = i+i; j < n; j+=i) {
                arr[j] = -1;
            }
    }
    for (i = 0; i < n; i++) 
        count+=(arr[i]+1);
    free(arr);
    return count;
}

int main(void) {
    int n = 499979;
    printf("Primes Number:%d\n", countPrimes(n));
    return 0;
}

