#include <stdbool.h>


bool isPerfectSquare(int num) {
    int low = 0, hight = 46341;
    int i = (low + hight)/2;
    while(i > low && i < hight) {
        if(i * i == num) return true;
        if(i * i < num) {
            low = i;
            i = i + (hight - low)/2;
            continue;
        }
        if(i * i > num) {
            hight = i;
            i = i - (hight - low)/2;
            continue;
        }
    }
    return false;
}

bool isPerfectSquare2(int x) {
    long r = x;
    while (r*r > x)
        r = (r + x/r) / 2;
    return r*r == x;
}
