/**
  * 该版本会导致时间溢出，该解法不可取
  */

int countPrimes(int n) {
    int i, j, count = 0;
    for (i = 2; i < n; i++) {
        for (j = 2; j < i; j++) {
            if (i % j == 0) {
                count--;
                break;
            }
        }
        count++;
    }
    return count;
}
