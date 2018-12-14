/**
  * 这个问题其实是一个求最大子序列和的问题
  * 设买入值是 A(i), 卖出值是A(i+n), 其中i是数组下标,且 n > 0，则 Profit == A(i+n) - A(i);
  * 而 A(i+n) - A(i) == [A(i+n) - A(i+n-1)] + [A(i+n-1) - A(i+n-2)] + [A(i+n-2) - A(i+n-3)] ...... + [A(i+1) - A(i)]
  * 直白的说，就是从 A(i+n) 到 A(i) 之间，相邻两个元素差(后元素-前元素)的和。
  * 而题目要求 maxProfit，也就是求 由相邻两个元素差所组成的序列的最大子序列和。
  * 那么有一个算法 ———— Kadane's algorithm
  * 我们把该题转换为 序列 REQ(n) = [A(0), A(1), A(2), A(3), ... A(n)] 中求最大子序列和。
  * 下面讲解该算法的思想：
  * 我们知道最大子序列的最后一个元素一定在序列内，我们只要求得以每一个元素为序列结尾时的最大子序列和，然后比较这些和里面哪个最大就行了。
    如果我们知道在位置i结束的最大子序列和（称为B(i)），那么在位置i+1处结束的最大子序列总和是什么（等价，什么是B(i+1)）？
    很明显，B(i+1) = max[ A(i+1), B(i) + A(i+1) ]  （因为要以A(i+1)做后缀，所以A(i+1)必须被加上）
  */

static int max(int a, int b) {
    if(a > b) return a;
    else return b;
}

int maxProfit(int* prices, int pricesSize) {
    int maxCur = 0;
    int maxSoFar = 0;
    int i = 0;
    for(i = 1; i < pricesSize; ++i) {
        maxCur = max(0, maxCur += (prices[i] - prices[i-1]));
        maxSoFar = max(maxSoFar, maxCur);
    }
    return maxSoFar;
}
