/**
  * emphasis ['emfəsɪs] n. 重点；强调；加强语气
  * 这个问题我并没有想出解法来，通过看别人的代码去理解思路：
  * 本题关键约束条件：不能打劫相邻的，即不能有两个相邻的数相加。
  * 那么从头到尾，加上当前数的和应该是截至上上个数为止最大的和。
  *
  * 首先我们保证每一次求和都不违反题设(不能相邻相加)；
  * 假设第n个数是E(n)，在E(n)之前能与E(n)相加的数是P(n)，加上第n个数的和是S(n)
  * 即：S(n) = E(n) + P(n)
  * 那么P(n)需要满足如下条件：
  *     P(n)一定是不包含E(n-1)的数；
  *     P(n)一定是包含E(n-2)与不包含E(n-2)的数中较大的那个。
  * 如下数组：
  *     [a, b, c, d, e, f]
  *     当求S(0)时，需要E(0)+P(0)，E(0)是a，P(0)是0，得S(0) = a;
  *     当求S(1)时，需要E(1)+P(1)，E(1)是b，P(1)还是0（因为没有E(1-2)这个数），得S(1) = b;
  *     当求S(2)时，需要E(2)+P(2)，E(2)是c，P(2)就是S(0)与S(-1)中较大的数，因为没有S(-1)，则P(2)就是S(0)，得S(2) = c + a;
  *     当求S(3)时，需要E(3)+P(3)，E(3)是d，P(3)就是S(1)与S(0)中较大的数，则P(3) = max(a, b)，得S(3) = d + max(a, b);
  *     当求S(4)时，需要E(4)+P(4)，E(4)是e，P(4)就是S(2)与S(1)中较大的数，则P(4) = max(c+a, b)，得S(4) = e + max(c+a, b);
  *     当求S(5)时，需要E(5)+P(5)，E(5)是f，P(5)就是S(3)与S(2)中较大的数，则P(5) = max[d + max(a,b), c+a]，得S(5) = f + max[d + max(a,b), c+a];
  *     最后，我们只需要得到 max[S(5), S(4)] 就是本体的答案。
  *
  * 下述两个函数都是借鉴LeetCode上的解法。
  */

#define max(a, b) ((a) > (b)? (a):(b))
int rob1(int* nums, int numsSize) {
    int a = 0, b = 0;
    int i;
    for (i = 0; i < numsSize; i++) {
        if (i%2 == 0)
            a = max(a + nums[i], b);
        else
            b = max(a, b + nums[i]);
    }
    return max(a, b);
}

#include <stdlib.h>
int rob2(int* nums, int numsSize) {
    int i;
    int **dp = (int **)calloc(1, sizeof(int*) * (numsSize+1));
    for (i = 0; i <= numsSize; i++) {
        dp[i] = (int *)calloc(1, sizeof(int) * 2);
    }
    for (i = 1; i <= numsSize; i++) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        dp[i][1] = nums[i-1] + dp[i-1][0];
    }
    return max(dp[numsSize][0], dp[numsSize][1]);
}

//下面这个函数是根据rob2转换来的
int rob2_new(int* nums, int numsSize) {
    int prevNo = 0;
    int prevYes = 0;
    int i;
    for (i = 0; i < numsSize; i++) {
        int temp = prevNo;
        prevNo = max(prevNo, prevYes);
        prevYes = nums[i] + temp;
    }
    return max(prevNo, prevYes);
}

