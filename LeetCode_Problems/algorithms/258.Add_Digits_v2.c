/**
 * 该题是在求数根，利用同余公式求解
 * dr(n) = 1 + ((n - 1) mod 9).
 */
int addDigits(int num) {
    return 1 + (num - 1) % 9;
}

