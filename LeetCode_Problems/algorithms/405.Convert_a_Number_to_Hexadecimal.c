#include <stdlib.h>

char* toHex(int num) {
    char *rt = calloc(1, 256 * sizeof(char));
    char map[16] = {'0', '1', '2', '3', '4', 
                   '5', '6', '7', '8', '9', 
                   'a', 'b', 'c', 'd', 'e', 
                   'f'};
    long long n = 0;
    if(num == -2147483648) n = (long long)2147483648;
    else if(num < 0) n = (long long)4294967296 + num;
    else n = num;
    int i = 0;
    for(; n/16 != 0; i++) {
        rt[i] = map[n % 16];
        n /= 16;
    }
    rt[i++] = map[n % 16];
    char tmp;
    for(int j = 0; j < i / 2; j++) {
        tmp = rt[j];
        rt[j] = rt[i - 1 - j];
        rt[i - 1 - j] = tmp;
    }
    return rt;
}

/**
 * 利用位移操作解决问题
 * 如果 num == 0 ，则直接返回 “0”；
 * 正数进行位移操作时，不管左移还是右移，空的位都补0，这样右移后总会成为0（最多右移动32位）
 * 负数进行位移操作时： 如果是左移，所有位移动，符号位不变，空位补0.
 *                      如果是右移，所有位移动，符号位不变，空位补1.
 *      例如：  a = -1;             内存为 FFFF FFFF
 *              a <<= 4;            内存为 FFFF FFF0
 *              print("%d", a);     输出为 -16
 *              b = -65536;         内存为 FFFF 0000
 *              b >>= 4;            内存为 FFFF F000
 *              print("%d", b);     输出为 -4096
 *      
 *      例如：  a = 1;              内存为 0000 0001
 *              a <<= 4;            内存为 0000 0010
 *              print("%d", a);     输出为 16
 */

char* toHex2(int num) {
    char *rt = calloc(1, 256 * sizeof(char));
    if(num == 0) return "0";
    int count = 0;
    while(num && count < 8) {
        int tmp = num & 15;
        rt[count++] = tmp < 10 ? '0' + tmp : 'a' + (tmp - 10);
        num >>= 4;
    }
    char tmp2;
    for(int j = 0; j < count / 2; j++) {
        tmp2 = rt[j];
        rt[j] = rt[count - 1 - j];
        rt[count - 1 - j] = tmp2;
    }
    return rt;
}
