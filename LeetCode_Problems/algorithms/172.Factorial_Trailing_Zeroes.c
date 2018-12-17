/**
  * 所有的结尾的0都是因为2*5，所以可以数n里面有多少个以5结尾的数： n / 5
  * 但是，25 这个数是 5 * 5组成的，所以25 中其实是包含两个 5 的。
  * 同样的，125 这个数是 5 * 5 * 5 组成的，所以 125 中其实是包含三个 5 的。
  * 简单且方便理解的方法就是计算n中有多少个 5^1 ，再加上有多少个 5^2，再加上有多少个 5^3........
  * 如第一个解法。
  */

int trailingZeroes(int n) {
    int result = 0;
    long long i = 5;    //防止溢出，定义为 long long
    for(i = 5; n / i > 0; i *=5) {
        result += (n / i);
    }
    return result;
}

/**
  * 第二个解法的是利用递归，相当于每次将n缩小5倍，然后求解，原理和第一个解一样的。
  * 运行效率上，第二个比第一个高。
  */
int trailingZeroes(int n) {
    if(n < 5) return 0;
    return n / 5 + trailingZeroes(n / 5);
}
