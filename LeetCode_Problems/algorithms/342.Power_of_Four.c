#include <stdbool.h>

bool isPowerOfFour(int num) {
    while(num > 3 && num % 4 == 0) {
        num /= 4;
    }
    return num == 1;
}

bool isPowerOfFour2(int num) {
    if(num <= 0) return false;
    while(num / 4) {
        if(num % 4 != 0) return false;
        num /= 4;
    }
    return num == 1;
}
