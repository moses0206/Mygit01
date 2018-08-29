#include <stdint.h>
#include <stdio.h>

uint32_t reverseBits(uint32_t n) {
    int i;
    uint32_t t, out = 0;
    for (i = 0; i < 32; ++i) {
        t = (n & (0x1 << i)) >> i;
        out = (out << 1) | t;
    }
    return out;
}

uint32_t reverseBits(uint32_t n) {
    int i;
    uint32_t m = 0;
    for (i = 0; i < 32; ++i) {
        m <<= 1;
        m |= (n & 0x1);
        n >>= 1;
    }
    return m;
}

