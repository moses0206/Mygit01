#include <stdint.h>

int hammingWeight(uint32_t n) {
    int rt = 0;
    while (n) {
        rt += (n & 0x1);
        n >>= 1;
    }
    return rt;
}
