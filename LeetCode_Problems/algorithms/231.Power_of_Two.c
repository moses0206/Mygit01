#include <stdbool.h>

bool isPowerOfTwo(int n) {
    if(n <= 0) return false;
    while(n%2 == 0) {
        n /= 2;
    }
    return n == 1;
}

/**
 * n = 2 ^ 0 = 1 = 0b0000...0001, and (n-1) = 0 = 0b0000...0000
 * n = 2 ^ 1 = 2 = 0b0000...0010, and (n-1) = 1 = 0b0000...0001
 * n = 2 ^ 2 = 4 = 0b0000...0100, and (n-1) = 3 = 0b0000...0011
 * n = 2 ^ 3 = 8 = 0b0000...1000, and (n-1) = 7 = 0b0000...0111
 * ....
 * So, (n & (n-1) == 0) when n is power of two.
 */
bool isPowerOfTwo2(int n) {
    return n > 0 && ((n & (n-1)) == 0);
}
