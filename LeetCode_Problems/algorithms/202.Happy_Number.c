/**
  * 该题的意思是，如果求和结果是1，那么就是true，否则求的和会落入一个循环，那么它就永远都不可能是1，则返回false。
  * 例如：
  *     28 → 2²+8²=68 → 6²+8²=100 → 1²+0²+0²=1
  *     32 → 3²+2²=13 → 1²+3²=10 → 1²+0²=1
  *     37 → 3²+7²=58 → 5²+8²=89 → 8²+9²=145 → 1²+4²+5²=42 → 4²+2²=20 → 2²+0²=4 → 4²=16 → 1²+6²=37……
  * 因此28和32是快乐数，而在37的计算过程中，37重复出现，继续计算的结果只会是上述数字的循环，不会出现1，因此37不是快乐数。
  * 此题解法类似于单链表找环。
  */
#include <stdbool.h>

int digitSquareSum(int n) {
    int sum = 0;
    while (n) {
        sum += ((n % 10) * (n % 10));
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    int slow, fast;
    slow = fast = n;
    do {
        slow = digitSquareSum(slow);
        fast = digitSquareSum(fast);
        fast = digitSquareSum(fast);
    } while(slow != fast && fast != 1);
    if (slow == 1 || fast == 1) return 1;
    else return 0;
}
