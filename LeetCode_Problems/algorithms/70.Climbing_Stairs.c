int climbStairs(int n) {
    if(n < 4) return n;
    int curr = 3, prev = 2;
    int i = 4;
    for(; i <= n; i++) {
        curr = curr + prev;
        prev = curr - prev;
    }
    return curr;
}
