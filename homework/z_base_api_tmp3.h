#ifndef __Z_BASE_API_H__
#define __Z_BASE_API_H__

#include "z_obj.h"

#define MAX_CMD 0X30000

/*  memory api  */
/**
*内存池api。
*本api只管理本api获取的内存空间，且只能由本api管理。
*使用本api获取的内存空间总是在可使用的首地址前缀16个字节的空间，这样做的目的是在总内存的第9个字节存储该段内存的总大小。
*本api非线程安全，已废弃。
*/

/**
*参数: 无;
*返回值: 无。
*功能: 内存池的初始化。
*详述: 无。
*注意: 若要使用本api，则必须首先使用一次该函数。
*/
Z_API void zMM_start(void);

/**
*参数: sz - 需要申请的内存空间长度（字节数）;
*返回值: 满足需要的内存空间的可用首地址。
*功能: 申请一块满足需要的内存空间。
*详述: 无。
*注意: 无。
*/
Z_API void *zMM_malloc(size_t sz);

/**
*参数: c - 需要申请的单个空间长度;
*      sc - 需要申请的单个空间的数量;
*返回值: 满足需要的内存空间的可用首地址。
*功能: 申请并重置一块满足需要的内存空间。
*详述: (c * sc)是需要的内存空间长度。
*注意: 无。
*/
Z_API void *zMM_calloc(size_t c, size_t sz);

/**
*参数: p - 原内存空间的可用首地址;
*      sz - 新需要的内存空间长度（字节数）;
*返回值: 满足需要的内存空间的可用首地址。
*功能: 重新分配内存空间。
*详述: 若原内存空间不满足需要，则重新分配一块满足需要的内存空间，并将原内存空间的数据拷贝到新内存中，回收原内存。
*注意: 无需自行释放原内存。
*/
Z_API void *zMM_realloc(void *p, size_t sz);

/**
*参数: p - 待释放内存空间的可用首地址;
*返回值: 无。
*功能: 内存空间释放函数。
*详述: 无。
*注意: 无。
*/
Z_API void zMM_free(void *p);

/**
*参数: 无;
*返回值: 无。
*功能: 内存池的结束清理。
*详述: 使用free函数释放掉之前所有已申请且未真正释放的内存空间。
*注意: 程序不再使用本api时，应当使用一次该函数。
*/
Z_API void zMM_finish(void);

//==================================================================================================================================================================//
/* buffer api */
/**
*字符串缓存api。
*因为是字符串缓存，所以z_buffer_t->ptr_中的数据总是以'\0'结尾（z_buffer_t->used_ == 0 时 z_buffer_t->ptr_[0] == '\0'）。
*本api的函数对z_buffer_t操作时其字符串缓存空间是动态扩展的。
*/

/**
*参数: 无;
*返回值: z_buffer_t *。
*功能: 初始化一个z_buffer_t。
*详述: calloc一块sizeof(z_buffer_t)大小的内存，malloc一块 Z_DEFAULT_POWER * char的内存并将地址赋值给z_buffer_t->ptr_。
*注意: Z_DEFAULT_POWER 是宏定义。用毕需手动使用 zB_free 释放掉。
*/
Z_API z_buffer_t *zB_init(void);

/**
*参数: n - 自定义缓存区空间的长度（字节数）;
*返回值: z_buffer_t *。
*功能: 类似于zB_init()，可按参数malloc内存空间长度。
*详述: calloc一块sizeof(z_buffer_t)长度的内存，malloc一块满足 n 长度的内存并将地址赋值给z_buffer_t->ptr_。
*注意: 如果 1G < n <= 2G，则申请的空间为2G；如果 > 2G，则申请的空间为3G；如果n <= 1G，则申请大于size_t的最小2的幂次方空间，最小为 (1 << Z_DEFAULT_POWER) 。
*/
Z_API z_buffer_t *zB_init_size(size_t n);

/**
*参数: m - 原数据的起始地址;
*      n - 原数据的长度（字节数）;
*返回值: z_buffer_t *。
*功能: 将m开始的n个字节数据拷贝到一个新的z_buffer_t存放。
*详述: 使用zB_init_size函数初始化一个z_buffer_t，缓存长度为 n + 1 ,并将m地址的n个大小的数据拷贝到新申请的z_buffer_t->ptr_的内存空间中，并以'\0'结尾。。
*注意: 此函数适用于指定数据长度的z_buffer_t初始化。
*/
Z_API z_buffer_t *zB_init_memory(const char *m, size_t n);

/**
*参数: s - 原字符串的起始地址;
*返回值: z_buffer_t *。
*功能: 将s地址的字符串拷贝到一个新的z_buffer_t存放。
*详述: 封装的zB_init_memory(s, strlen(s)) 函数，自动检查字符串s的长度。
*注意: 此函数适用于字符串（'\0'结尾）数据的z_buffer_t初始化。
*/
Z_API z_buffer_t *zB_init_str(const char *s);

/**
*参数: b - 待释放的z_buffer_t*;
*返回值: 无。
*功能: 释放一个z_buffer_t。
*详述: 无。
*注意: 无。
*/
Z_API void zB_free(z_buffer_t *b);

/**
*参数: b - 待重置的z_buffer_t *;
*返回值: 无。
*功能: 重置z_buffer_t的字符串缓存区。
*详述: 只是 b->used_ = 0 和 b->ptr_[0] = '\0'。
*注意: 没有回收内存。
*/
Z_API void zB_reset(z_buffer_t *b);

/**
*参数: b1 - 待比较的z_buffer_t *;
*      b2 - 待比较的z_buffer_t *;
*返回值: 一致时返回0，否则返回非0。
*功能: 比较两个z_buffer_t缓存中的数据是否一致；。
*详述: 从低到高比较两个缓存中每一字节的数据是否一致，不一致返回同位置数据之差，如果其中一个字符串是从头部完全包含另一个，则返回两者数据长度之差。
*注意: 无。
*/
Z_API int zB_cmp(const z_buffer_t *b1, const z_buffer_t *b2);

/**
*参数: b - 需要扩展缓存区空间的z_buffer_t*;
*      n - 需要的新长度;
*返回值: 无。
*功能: 根据需要扩展缓存区的大小。
*详述: 如何n不大于b->size_，则不做任何操作，否则将（b->size_ << 1），直到大于n位置，然后再使用realloc函数将b->ptr_按照b->size_指定的大小扩展，将realloc结果赋值给b->ptr_。
*注意: 如果 1G < n <= 2G，则申请的空间为2G；如果 > 2G，则申请的空间为3G；如果参数 <= 1G，则申请大于size_t的最小2的幂次方空间，最小为 (1 << Z_DEFAULT_POWER) 。
*      本函数自动被其他api调用，无需单独使用。
*/
Z_API void zB_prepare_size(z_buffer_t *b, size_t n);

/**
*参数: b - 目标z_buffer_t*;
*      fmt - 格式化字符串;
*      ... - 根据格式化字符串中的格式控制符所需的可变参数;
*返回值: 返回格式化追加保存后的z_buffer_t*。
*功能: 将可变参数以fmt格式化为字符串，并追加保存到目标z_buffer_t中。
*详述: 可变参数根据fmt中的格式说明符格式化成字符串，然后追加到b中。
*      例如: z_buffer_t * b = zB_init_str("Example:");
*            zB_append_fmt(b, "%s's value is %d.", "amount", 100);
*            printf("%s", b->ptr_);
*      结果: Example:amount's value is 100.
*注意: 可变参数支持的类型：NULL, long long, int, unsigned int, unsigned long long, void *, z_hash_t *, double, char, z_buffer_t *。
*      fmt支持的格式说明符和相对应的可变参数类型：
*      %s  ==> NULL,char *
*           例: z_buffer_t * b = zB_init_str("Example: ");
*               char * s1 = NULL; 
*               char * s2 = "str2";
*               zB_append_fmt(b, "%s, %s, %s, %s", NULL, "string", s1, s2);
*               printf("%s", b->ptr_);
*           输出: Example: <NULL>, string, <NULL>, str2
*           注意：char * 应是一个字符串（以'\0'结尾）。
*      %l  ==> long long
*           例: z_buffer_t * b = zB_init_str("Example: ");
*               long long ll1 = 123; 
*               long long ll2 = -123; 
*               zB_append_fmt(b, "ll1 = %l, ll2 = %l", ll1, ll2);
*               printf("%s", b->ptr_);
*           输出: Example: ll1 = 123, ll2 = -123
*      %d  ==> int
*           例: z_buffer_t * b = zB_init_str("Example: ");
*               int i1 = 123; 
*               int i2 = -123; 
*               zB_append_fmt(b, "i1 = %d, i2 = %d", i1, i2);
*               printf("%s", b->ptr_);
*           输出: Example: i1 = 123, i2 = -123
*      %u  ==> unsigned int
*           例: z_buffer_t * b = zB_init_str("Example: ");
*               unsigned int ui = 123; 
*               zB_append_fmt(b, "ui = %u", ui);
*               printf("%s", b->ptr_);
*           输出: Example: ui = 123
*      %U  ==> unsigned long long
*           例: z_buffer_t * b = zB_init_str("Example: ");
*               unsigned long long ull = 123; 
*               zB_append_fmt(b, "ull = %U", ull);
*               printf("%s", b->ptr_);
*           输出: Example: ull = 123
*      %p  ==> void *  结果为0X十六进制表示
*           例: z_buffer_t * b = zB_init_str("Example: ");
*               int i = 123; long long ll = 321;
*               void * p1 = &i; long long * p2 = &ll;
*               zB_append_fmt(b, "i = %d, p1 = %p, ll = %l, p2 = %p", i, p1, ll, p2);
*               printf("%s", b->ptr_);
*           输出: Example: i = 123, p1 = OX7FFD42607200, ll = 321, p2 = OX7FFD42607210
*           注意：上例中p2的用法不完全准确，应在p2前加类型强转操作(void *)。
*      %X  ==> unsigned int
*           首先，会将这个unsigned int数（后面简称为x）转为大写的十六进制字符串（前缀0X），
*           然后，如果 0 < x < MAX_CMD ;
*                   如果 g_cmd2name_mapping[x] 已初始化了字符串
*                       则加上'('g_cmd2name_mapping[x]')';
*                   否则，如果((x & 0X20000) && g_cmd2name_mapping[x & 0XFFFF])
*                       则加上"(KEEP..."g_cmd2name_mapping[x & 0XFFFF]')'
*           例: z_buffer_t * b = zB_init_str("Example: ");
*               z_cmdmap_t g_test_name2cmd_mapping[] = {
*                   {"this is test1", 0x10a1},
*                   {"this is test2", 0x10a2},
*                   {NULL, -1}
*               };
*               z_persudo(g_test_name2cmd_mapping);
*               unsigned int cmd1 = 0x10a1, cmd2 = 0x10a2, cmd3 = 0x10a3, cmd4 = 0x210a2, cmd5 = 0x210a3;
*               zB_append_fmt(b, "cmd1 = %X, cmd2 = %X, cmd3 = %X, cmd4 = %X, cmd5 = %X", cmd1, cmd2, cmd3, cmd4, cmd5);
*               printf("%s", b->ptr_);
*           输出: Example: cmd1 = 0X10A1(this is test1), cmd2 = 0X10A2(this is test2), cmd3 = 0X10A3, cmd4 = 0X210A2(KEEP...this is test2), cmd5 = 0X210A3
*           注意: z_persudo() 和 z_cmdmap_t 参照 z_persudo.h ， g_cmd2name_mapping[MAX_CMD] 参照本文件 log api部分。
*      %h  ==> z_hash_t *  将z_hash_t格式化为不换行的json格式字符串
*           例: z_buffer_t * b = zB_init_str("Example: ");
*               z_array_t * a = zA_init(); zA_insert_double(a, 12.21); zA_insert_ll(a, 1111); zA_insert_str(a, "array!");
*               z_hash_t * h = zH_init();
*               z_hash_t * h1 = zH_init(); zH_strinsert_str(h1, "h1key1", "h1value1"); zH_strinsert_ll(h1, "h1key2", 123);
*               z_hash_t * h2 = zH_init(); zH_strinsert(h2, "this is array", (z_obj_t *)a);        
*               zH_strinsert_str(h, "hkey1", "hvalue1"); zH_llinsert(h, 321, (z_obj_t *)h1); zH_strinsert(h, "Is h2", (z_obj_t *)h2);
*               zB_append_fmt(b, "hash = %h", h);
*               printf("%s", b->ptr_);
*           输出: {"hkey1":"hvalue1",321:{"h1key1":"h1value1","h1key2":123},"Is h2":{"this is array":[12.210000000,1111,"array!"]}}
*      %H  ==> z_hash_t *  将z_hash_t格式化为有换行和缩进形式的json格式
*           例：参照%h的例子
*           输出: Example: hash = {
*                     "hkey1" : "hvalue1",
*                     321 : {
*                         "h1key1" : "h1value1",
*                         "h1key2" : 123
*                     },
*                     "Is h2" : {
*                         "this is array" : [
*                             12.210000000,
*                             1111,
*                             "array!"
*                         ]
*                     }
*                 }
*      %t  ==> 当前时间的时间戳，没有可变参数//wangmao//
*      %f  ==> double
*      %c  ==> int //wangmao//
*      %m  ==> size_t 和 char * //wangmao//写个例子
*      %b  ==> z_buffer_t * //wangmao//写个例子
*      %B  ==> z_buffer_t *    结果是：0x[将z_buffer_t *的字符串的每个字符转换为十六进制]   例如："ABC123" ==> "0x[414243313233]"。
*/
Z_API z_buffer_t *zB_append_fmt(z_buffer_t *b, const char *fmt, ...);

/**
*参数: z_buffer_t* - 目标缓冲区结构体指针;
*      const char * - 格式化字符串指针;
*      va_list - 根据格式化字符串中的格式控制符所需的可变参数;
*返回值: 返回格式化追加保存后的缓冲区结构体指针。
*功能: 与 zB_append_fmt 类似。
*详述: zB_append_fmt 函数实际使用的就是该函数实现的，如果你理解va_list,va_start的话，你也可以直接使用该函数达到和zB_append_fmt相同的目的，但不建议这样做。
*注意: 不建议使用本函数。
*/
Z_API z_buffer_t *zB_append_vafmt(z_buffer_t *, const char *, va_list);

/**
*参数: z_buffer_t * - 目标缓冲区结构体指针;
*      const char * - 源字符串指针;//wangmao//二进制数据
*      size_t - 源字符串中需要保存的字节数;
*返回值: 保存后的缓冲区结构体指针。
*功能: 将源字符串中指定大小个字节的字符覆盖保存到目标缓冲区结构体中。
*详述: 无。
*注意: 源字符串的数据会覆盖目标缓冲区中原有的数据。
*/
Z_API z_buffer_t *zB_copy_memory(z_buffer_t *, const char *, size_t);//wangmao//是否最后有追加\0

/**
*参数: z_buffer_t * - 目标缓冲区结构体指针;
*      const char * - 源字符串指针;
*返回值: 保存后的缓冲区结构体指针。
*功能: 与 zB_copy_memory 类似，只是省去了size_t的参数，实际使用strlen(const char *)做参数。
*详述: 无。
*注意: 无。
*/
Z_API z_buffer_t *zB_copy_str(z_buffer_t *, const char *);//wangmao//是否最后有追加\0

/**
*参数: z_buffer_t * - 目标缓冲区结构体指针;
*      char - 源字符;
*返回值: 追加后的缓冲区结构体指针。
*功能: 将源字符追加保存到目标缓冲区中。
*详述: 无。
*注意: 无。
*/
Z_API z_buffer_t *zB_append_char(z_buffer_t *, char);//wangmao//是否最后有追加\0

/**
*参数: z_buffer_t * - 目标缓冲区结构体指针;
*      const char * - 源字符串指针;
*      size_t - 源字符串中需要保存的字节数;
*返回值: 保存后的缓冲区结构体指针。
*功能: 将源字符串中指定大小个字节的字符追加保存到目标缓冲区结构体中。
*详述: 无。
*注意: 源字符串的数据会追加到目标缓冲区中原有的数据之后。
*/
Z_API z_buffer_t *zB_append_memory(z_buffer_t *, const char *, size_t);//wangmao//是否最后有追加\0

/**
*参数: z_buffer_t * - 目标缓冲区结构体指针;
*      const char * - 源字符串指针;
*返回值: 保存后的缓冲区结构体指针。
*功能: 与 zB_append_memory 类似，只是省去了size_t的参数，实际使用strlen(const char *)做参数。
*详述: 无。
*注意: 无。
*/
Z_API z_buffer_t *zB_append_str(z_buffer_t *, const char *);

/**
*参数: z_buffer_t * - 目标缓冲区结构体指针;
*      int - 源整形数值;
*返回值: 追加后的缓冲区结构体指针。
*功能: 将源整形数值以十进制形式转换为字符串并追加保存到目标缓冲区中。
*详述: 无。
*注意: 无。
*/
Z_API z_buffer_t *zB_append_int(z_buffer_t *, int);

/**
*参数: z_buffer_t * - 目标缓冲区结构体指针;
*      double - 源浮点型数值;
*返回值: 追加后的缓冲区结构体指针。
*功能: 将源浮点型数值以十进制形式转换为字符串并追加保存到目标缓冲区中。
*详述: 无。
*注意: 最长支持小数点后9位数字。//wangmao//是保留，还是支持，具体怎么实现的
*/
Z_API z_buffer_t *zB_append_double(z_buffer_t *, double);

/**
*参数: z_buffer_t * - 目标缓冲区结构体指针;
*      unsigned int - 源无符号整形数值;
*返回值: 追加后的缓冲区结构体指针。
*功能: 将源无符号整形数值以十进制形式转换为字符串并追加保存到目标缓冲区中。
*详述: 无。
*注意: 无。
*/
Z_API z_buffer_t *zB_append_uint(z_buffer_t *, unsigned int);

/**
*参数: z_buffer_t * - 目标缓冲区结构体指针;
*      long long - 源长整形数值;
*返回值: 追加后的缓冲区结构体指针。
*功能: 将源长整形数值以十进制形式转换为字符串并追加保存到目标缓冲区中。
*详述: 无。
*注意: 无。
*/
Z_API z_buffer_t *zB_append_ll(z_buffer_t *, long long);

/**
*参数: z_buffer_t * - 目标缓冲区结构体指针;
*      unsigned long long - 源无符号长整形数值;
*返回值: 追加后的缓冲区结构体指针。
*功能: 将源无符号长整形数值以十进制形式转换为字符串并追加保存到目标缓冲区中。
*详述: 无。
*注意: 无。
*/
Z_API z_buffer_t *zB_append_ull(z_buffer_t *, unsigned long long);

//==================================================================================================================================================================//
/* list api */
/**
*这是一个双向链表管理模块。
*/

/**
*参数: 无;
*返回值: 无。//wangmao//
*功能: 初始化一个 z_list_t 。
*详述: 无。
*注意: 无。
*/
#define zL_init() ((z_list_t *)calloc(1, sizeof(z_list_t)))

/**
*参数: 双链表结构体指针;
*返回值: jian memset。//wangmao//
*功能: 重置一个 z_list_t 。
*详述: 无。
*注意: 无。
*/
#define zL_reset(l) memset(l, 0, sizeof(z_list_t))

/**
*参数: 双链表结构体指针;
*返回值: 无。//wangmao//
*功能: 释放一个 z_list_t 。
*详述: 无。
*注意: 无。
*/
#define zL_free(l) free(l)

/**
*参数: z_list_t * - 目标双链表指针;
*      z_list_node_t * - 待插入的双链表节点指针;
*返回值: 成功返回0。//wangmao//永远返回0
*功能: 向目标链表插入一个节点，并使该节点成为头节点。
*详述: 无。
*注意: 无。
*/
Z_API int zL_insert_head(z_list_t *, z_list_node_t *);

/**
*参数: z_list_t * - 目标双链表指针;
*      z_list_node_t * - 待插入的双链表节点指针;
*返回值: 成功返回0。
*功能: 向目标链表插入一个节点，并使该节点成为尾节点。
*详述: 无。
*注意: 无。
*/
Z_API int zL_insert_tail(z_list_t *, z_list_node_t *);

/**
*参数: z_list_t * - 目标双链表指针;
*      z_list_node_t * - 插入位置的参照节点指针;
*      z_list_node_t * - 待插入的双链表节点指针;
*      int - 参照节点的前后位置标志;
*返回值: 成功返回0。
*功能: 向目标链表指定位置插入一个节点。
*详述: 根据int的值决定插入在参照节点的前面或者后面，非0 表示在指定节点的后面插入，0 表示在指定节点的前面插入。
*注意: 参照节点应是目标链表中的一个节点。
*/
Z_API int zL_insert_pos(z_list_t *, z_list_node_t *, z_list_node_t *, int);

/**
*参数: z_list_t * - 目标双链表指针;
*      z_list_node_t * - 待删除的双链表节点指针;
*返回值: 成功返回0。
*功能: 从目标链表删除一个节点。
*详述: 无。
*注意: 待删除节点应是目标链表中的一个节点。
*/
Z_API int zL_delete(z_list_t *, z_list_node_t *);

/**
*参数: z_list_t * - 目标双链表指针;
*      z_list_node_t * - 待交换的双链表节点指针;
*      z_list_node_t * - 待交换的双链表节点指针;
*返回值: 成功返回0。
*功能: 将目标链表中的两个指定节点的位置互换。
*详述: 无。
*注意: 待交换节点应是目标链表中的节点。
*/
Z_API int zL_swap(z_list_t *, z_list_node_t *, z_list_node_t *);


//==================================================================================================================================================================//
// ll and double api */
/**
*这是一个长整型和浮点型数据结构体管理模块。
*/

/**
*参数: 无;
*返回值: z_ll_t *。
*功能: 初始化一个长整型数据结构体。
*详述: 初始化一个z_ll_t结构体，不指定z_ll_t的存储值。//wangmao//z_ll_t->l_的值是否有默认值，malloc和calloc有区别。
*注意: 无。
*/
Z_API z_ll_t *zLL_init(void);

/**
*参数: l - z_ll_t中保存的长整型数值;//wangmao//保存的
*返回值: 长整型数据结构体指针。
*功能: 初始化一个长整型数据结构体。//wangmao//
*详述: 初始化一个z_ll_t结构体，指定z_ll_t的存储值为参数值。//wangmao//
*注意: 无。
*/
Z_API z_ll_t *zLL_init_ll(long long l);

/**
*参数: 无;
*返回值: 浮点型数据结构体指针。
*功能: 初始化一个浮点型数据结构体。
*详述: 初始化一个z_double_t结构体，不指定z_double_t->d_的值。//wangmao//
*注意: 无。
*/
Z_API z_double_t *zD_init(void);

/**
*参数: d - 数据结构体中保存的浮点型数值;
*返回值: 浮点型数据结构体指针。
*功能: 初始化一个浮点型数据结构体。
*详述: 初始化一个z_double_t结构体，指定z_double_t->d_的值为参数值。//wangmao//
*注意: 无。
*/
Z_API z_double_t *zD_init_double(double d);


//==================================================================================================================================================================//
/* string api */
/**
*这是一个字符串数据结构体api。
*其依托于 z_buffer_t 结构实现的。
*/

/**
*参数: 无;
*返回值: 字符串数据结构体指针。//wangmao//
*功能: 初始化一个z_string_t。
*详述: 初始化一个z_string_t结构体，其中存储的字符串是一个空串。
*注意: 无。
*/
Z_API z_string_t *zS_init(void);

/**
*参数: const char * - 源字符串指针;
*返回值: 字符串数据结构体指针。
*功能: 初始化一个字符串数据结构体，并将源字符串保存其中。
*详述: 初始化一个z_string_t结构体，并使z_string_t->b_中保存char *字符串。//wangmao//
*注意: 无。
*/
Z_API z_string_t *zS_init_str(const char *); 

/**
*参数: const char * - 源数据指针;//wangmao//
*      size_t - 源字符串大小;
*返回值: 字符串数据结构体指针。
*功能: 初始化一个字符串数据结构体，并将源字符串保存其中。
*详述: 初始化一个z_string_t结构体，并将char *的字符串保存到z_string_t->b_中，保存长度为size_t。
*注意: 无。
*/
Z_API z_string_t *zS_init_memory(const char *, size_t);

/**
*参数: z_buffer_t * - 源缓冲区结构体指针;
*返回值: 字符串数据结构体指针。
*功能: 初始化一个字符串数据结构体，并将缓冲区结构体保存其中。
*详述: 初始化一个z_string_t结构体，并将参数b 赋值给z_string_t中的成员。//wangmao//
*注意: 只赋值指针，没有拷贝内存。//wangmao//
*/
Z_API z_string_t *zS_init_buffer(z_buffer_t *b); 

/**
*参数: z_string_t * - 目标字符串结构体指针;
*返回值: 无。
*功能: 重置一个字符串结构体中保存的字符串。
*详述: 将z_string_t中的字符串重置为空串（结尾'\0'）。//wangmao//
*注意: 无。
*/
Z_API void zS_reset(z_string_t *);

/**
*参数: z_string_t * - 目标字符串结构体指针;
*返回值: 无。
*功能: 释放字符串结构体。
*详述: 将z_string_t 安全的释放掉，内部指针全部释放掉。
*注意: 内部指针全部释放掉。
*/
Z_API void zS_free(z_string_t *);

/**
*参数: const z_string_t * - 待比较字符串结构体指针;
*      const z_string_t * - 待比较字符串结构体指针;
*返回值: 一致返回0，否则返回非0。
*功能: 比较两个z_string_t的buffer的字符串是否一致，使用 zB_cmp()函数。//wangmao//字典序
*详述: 无。
*注意: 无。
*/
Z_API int zS_cmp(const z_string_t *, const z_string_t *);

/**
*参数: const z_string_t * - 目标字符串结构体指针;
*返回值: 字符串结构体中字符串的校验码。
*功能: 使用crc32获取字符串结构体中字符串的校验码。
*详述: 无。
*注意: 无。
*/
Z_API size_t zS_hash(const z_string_t *);

/**
*参数: const z_string_t * - 源字符串结构体指针;
*返回值: 新的字符串结构体指针。
*功能: 将源字符串结构体中的字符串复制到一个新的字符串结构体中。
*详述: 初始化一个新的z_string_t结构体，并将源结构体中的字符串追加拷贝到新z_string_t中。//wangmao//
*注意: 无。
*/
Z_API z_string_t *zS_copy(const z_string_t *);

/**
*参数: 字符串结构体指针;
*返回值: 无。//wangmao//
*功能: 将z_string_t*，转为指向其z_buffer_t*。
*详述: 无。
*注意: 无。//wangmao//
*/
#define string2buffer(s) ((s)->b_)

/**
*参数: 字符串结构体指针;//wangmao//
*返回值: 无。//wangmao//
*功能: 将字符串结构体指针，转为指向保存的字符串地址。
*详述: 无。
*注意: 无。
*/
#define string2str(s) (string2buffer(s)->ptr_)

//==================================================================================================================================================================//
/* array api */
/**
*这是一个数组数据结构体api。
*/

/**
*参数: 无;
*返回值: 一个数组数据结构体指针。
*功能: 初始化一个z_array_t结构体。
*详述: z_array_t预分配256个元素空间。//wangmao//
*注意: 无。
*/
Z_API z_array_t *zA_init(void);

/**
*参数: z_array_t * - 待重置数组数据结构体指针;
*返回值: 无。
*功能: z_array_t结构体元素的重置函数。
*详述: 释放掉z_array_t->data的所有元素，z_array_t->used_= 0。//wangmao//
*注意: 释放的是元素指向的空间，而不是数组空间。//wangmao//
*/
Z_API void zA_reset(z_array_t *);

/**
*参数: z_array_t * - 待释放数组数据结构体指针;
*返回值: 无。
*功能: z_array_t结构体的释放函数。
*详述: 无。
*注意: 无。
*/
Z_API void zA_free(z_array_t *);

/**
*参数: const z_array_t * - 待比较数组数据结构体指针;
*      const z_array_t * - 待比较数组数据结构体指针;
*返回值: 一致返回0，否则返回非0。
*功能: 两个z_array_t的元素比较函数。
*详述: 无。
*注意: 无。
*/
Z_API int zA_cmp(const z_array_t *, const z_array_t *);

/**
*参数: const z_array_t * - 目标数组数据结构体指针;
*返回值: 校验码。
*功能: 获取z_array_t的校验码。
*详述: 无。
*注意: 无。
*/
Z_API size_t zA_hash(const z_array_t *);

/**
*参数: const z_array_t * - 目标数组数据结构体指针;
*返回值: 新的数组结构体指针。
*功能: 复制目标数组结构体中的数据到一个新的结构体中。
*详述: 使用zA_init函数初始化一个新的z_array_t结构体，并将参数z_array_t的所有元素按顺序复制插入到新的z_array_t中。
*注意: 无。
*/
Z_API z_array_t *zA_copy(const z_array_t *);

/**
*参数: const z_array_t * - 待插入的数组数据结构体指针;
*      z_obj_t * - 待插入数组的元素指针;
*返回值: 成功返回0。
*功能: 将新元素插入到数组中。
*详述: z_array_t的插入元素函数，将z_obj_t插入到z_array_t现有元素的最后，如果z_array_t满了（size_ == used_），则realloc一块新的空间。
*注意: 无。
*/
Z_API int zA_insert(z_array_t *, z_obj_t *);

/**
*参数: const z_array_t * - 待插入的数组数据结构体指针;
*      double - 待插入数组的浮点型数值;
*返回值: 成功返回0。
*功能: 向数组中插入一个浮点型数据结构体。
*详述: 先将参数double存储为z_double_t结构体，然后将z_double_t插入到z_array_t现有元素的最后，如果z_array_t满了（size_ == used_），则realloc一块新的空间。
*注意: 无。
*/
Z_API int zA_insert_double(z_array_t *, double);

/**
*参数: const z_array_t * - 待插入的数组数据结构体指针;
*      long long - 待插入数组的长整型数值;
*返回值: 成功返回0。
*功能: 向数组中插入一个长整型数据结构体。
*详述: 先将参数long long存储为z_ll_t结构体，然后将z_ll_t插入到z_array_t现有元素的最后，如果z_array_t满了（size_ == used_），则realloc一块新的空间。
*注意: 无。
*/
Z_API int zA_insert_ll(z_array_t *, long long);

/**
*参数: const z_array_t * - 待插入的数组数据结构体指针;
*      const char * - 待插入数组的字符串指针;
*返回值: 成功返回0。
*功能: 向数组中插入一个字符串数据结构体。
*详述: 先将参数const char *存储为z_string_t结构体，然后将z_string_t插入到z_array_t现有元素的最后，如果z_array_t满了（size_ == used_），则realloc一块新的空间。
*注意: 无。
*/
Z_API int zA_insert_str(z_array_t *, const char *);

/**
*参数: const z_array_t * - 待插入的数组数据结构体指针;
*      const char * - 待插入数组的字符串指针;
*      size_t - 待插入数组的字符串的大小;
*返回值: 成功返回0。
*功能: 向数组中插入一个字符串数据结构体。
*详述: 先使用zS_init_memory函数将第二、三个参数存储为z_string_t结构体，然后将z_string_t插入到z_array_t现有元素的最后，如果z_array_t满了（size_ == used_），则realloc一块新的空间。
*注意: 无。
*/
Z_API int zA_insert_memory(z_array_t *, const char *, size_t);

/**
*参数: 数组数据结构体指针;
*返回值: 数组元素的个数。
*功能: z_array_t的元素个数获取函数。
*详述: 无。
*注意: 无。
*/
#define zA_count(a) (a->used_)

//==================================================================================================================================================================//
/* hash api */
/**
*这是一个哈希数据结构体管理模块。
*/

/**
*参数: 无;
*返回值: 新初始化的z_hash_t结构体指针。
*功能: 初始化一个z_hash_t结构体，默认最大键值对存储数为256。
*详述: 无。
*注意: 无。
*/
Z_API z_hash_t *zH_init(void);

/**
*参数: size_t - 需要存储键值对的数量;
*返回值: 新初始化的z_hash_t结构体指针。
*功能: 根据size_t数值，初始化一个满足size_t大小的z_hash_t结构体。
*详述: 无。
*注意: 无。
*/
Z_API z_hash_t *zH_init_size(size_t);

/**
*参数: z_hash_t * - 需要重置的结构体指针;
*返回值: 无。
*功能: 重置z_hash_t的函数，会释放所有存储的键值对。
*详述: 无。
*注意: 无。
*/
Z_API void zH_reset(z_hash_t *);

/**
*参数: z_hash_t * - 需要释放的结构体指针;
*返回值: 无。
*功能: 释放z_hash_t。会先重置本z_hash_t，然后释放掉z_hash_t。
*详述: 无。
*注意: 无。
*/
Z_API void zH_free(z_hash_t *);

/**
*参数: z_hash_t * - 待比较的结构体指针;
*      z_hash_t * - 待比较的结构体指针;
*返回值: 如果一致返回0，否则返回非0。
*功能: 比较两个z_hash_t结构体中键值对是否相同。
*详述: 先比较两个hash的used_是否一致，然后比较两个hash中每个键值对是否一致。
*注意: 无。
*/
Z_API int zH_cmp(const z_hash_t *, const z_hash_t *);

/**
*参数: z_hash_t * - 结构体指针;
*返回值: 该z_hash_t结构体的哈希码。
*功能: 生成该z_hash_t结构体的哈希码。
*详述: 无。
*注意: 无。
*/
Z_API size_t zH_hash(const z_hash_t *);

/**
*参数: z_hash_t * - 结构体指针;
*返回值: 新结构体的指针。
*功能: 复制z_hash_t结构体的函数，返回一个与参数相同键值对的z_hash_t结构体。
*详述: 无。
*注意: 无。
*/
Z_API z_hash_t *zH_copy(const z_hash_t *);

/**
*参数: z_hash_t * - 结构体指针;
*      z_obj_t * - 键值对的key;
*      z_obj_t * - 键值对的value;
*返回值: 成功返回0，失败返回-1。
*功能: 第一个z_obj_t是key，第二个z_obj_t是value。查找z_hash_t是否已存在该key的数据，如果已存在会释放掉该key和value，否则向z_hash_t插入该键值对。
*详述: base提供诸多自定义数据类型结构体（例如：z_ll_t、z_double_t、z_string_t、z_array_t），这些结构体均在第一位含有z_obj_t结构体，并且z_obj_t对本数据类型有正确的描述。
*      故而可以将这些自定义数据类型的结构体作为键值对存储到z_hash_t中
*注意: 无。
*/
Z_API int zH_insert(z_hash_t *, z_obj_t *, z_obj_t *);

/**
*参数: z_hash_t * - 结构体指针;
*      z_obj_t * - 键值对的key;
*      z_obj_t * - 键值对的value;
*返回值: 成功返回0，失败返回-1。
*功能: 第一个z_obj_t是key，第二个z_obj_t是value。向z_hash_t中插入该键值对。
*详述: 无。
*注意: 该函数未进行键值对的判断，所以会产生相同的key情况下新value覆盖旧value的情况，不建议使用该函数。
*/
Z_API int zH_insert_raw(z_hash_t *, z_obj_t *, z_obj_t *);

/**
*参数: z_hash_t * - 结构体指针;
*      z_obj_t * - 键值对的key;
*      z_obj_t * - 键值对的value;
*返回值: 成功返回0；失败返回-1。
*功能: 键值对的value替换函数。
*详述: 第一个z_obj_t是key，第二个z_obj_t是value。判断z_hash_t中是否已存在该key的键值对，是则将hash中该key的值替换成新的value然后释放key，否则将key和value都释放掉。
*注意: 该函数未进行键值对的判断，所以会产生相同的key情况下新value覆盖旧value的情况，不建议使用该函数。
*/
Z_API int zH_replace(z_hash_t *, z_obj_t *, z_obj_t *);

/**
*参数: z_hash_t * - 结构体指针;
*      z_obj_t * - 键值对的key;
*      z_obj_t * - 键值对的value;
*返回值: 成功返回0；失败返回-1。
*功能: 灵活的键值对插入或替换函数。
*详述: 第一个z_obj_t是key，第二个z_obj_t是value。先判断z_hash_t中是否已存在该key的键值对，存在即替换该key的值为value，不存在的话就将该key和value作为键值对插入z_hash_t中。
*注意: 无。
*/
Z_API int zH_insert_or_replace(z_hash_t *, z_obj_t *, z_obj_t *);

/**
*参数: z_hash_t * - 结构体指针;
*      const char * - 键值对的key的数据;
*      z_obj_t * - 键值对的value;
*返回值: 成功返回0；失败返回-1。
*功能: 将char*作为key，z_obj_t作为value，插入到z_hash_t中。插入前会判断key是否已存在，若已存在返回-1；不存在就插入到hash中，插入成功返回0。
*详述: 插入前会判断key是否已存在，若已存在则释放value并返回-1；不存在则将char*存储为z_string_t，然后将键值对存储z_hash_t。
*注意: 无。
*/
Z_API int zH_strinsert(z_hash_t *, const char *, z_obj_t *);

/**
*参数: z_hash_t * - 结构体指针;
*      const char * - 键值对的key的数据;
*      const char * - 键值对的value的数据;
*返回值: 成功返回0；失败返回-1。
*功能: 将键值对插入到z_hash_t中。插入前会判断key是否已存在，若已存在返回-1。
*详述: 第一个char *为key，第二个char* 为value。存入时会将char*存储为z_string_t类型。
*注意: 无。
*/
Z_API int zH_strinsert_str(z_hash_t *, const char *, const char *);

/**
*参数: z_hash_t * - 结构体指针;
*      const char * - 键值对的key的数据;
*      long long - 键值对的value的数据;
*返回值: 成功返回0；失败返回-1。
*功能: 与上类似，key是char*，value是long long的键值对插入函数。
*详述: 无。
*注意: 无。
*/
Z_API int zH_strinsert_ll(z_hash_t *, const char *, long long);

/**
*参数: z_hash_t * - 结构体指针;
*      const char * - 键值对的key的数据;
*      double - 键值对的value的数据;
*返回值: 成功返回0；失败返回-1。
*功能: 与上类似，key是char*，value是double的键值对插入函数。
*详述: 无。
*注意: 无。
*/
Z_API int zH_strinsert_double(z_hash_t *, const char *, double);

/**
*参数: z_hash_t * - 结构体指针;
*      long long - 键值对的key的数据;
*      z_obj_t * - 键值对的value;
*返回值: 成功返回0；失败返回-1。
*功能: 与上类似，将long long转换后作为key，z_obj_t作为value，插入到z_hash_t中。插入前会判断key是否已存在，若已存在返回-1；不存在就插入到hash中，插入成功返回0。
*详述: 无。
*注意: 无。
*/
Z_API int zH_llinsert(z_hash_t *, long long, z_obj_t *);

/**
*参数: z_hash_t * - 结构体指针;
*      long long - 键值对的key的数据;
*      const char * - 键值对的value的数据;
*返回值: 成功返回0；失败返回-1。
*功能: 与上类似，key是long long，value是char*的键值对插入函数。
*详述: 无。
*注意: 无。
*/
Z_API int zH_llinsert_str(z_hash_t *, long long, const char *);

/**
*参数: z_hash_t * - 结构体指针;
*      long long - 键值对的key的数据;
*      long long - 键值对的value的数据;
*返回值: 成功返回0；失败返回-1。
*功能: 与上类似，key是long long，value是long long的键值对插入函数。
*详述: 无。
*注意: 无。
*/
Z_API int zH_llinsert_ll(z_hash_t *, long long, long long);

/**
*参数: z_hash_t * - 结构体指针;
*      long long - 键值对的key的数据;
*      double - 键值对的value的数据;
*返回值: 成功返回0；失败返回-1。
*功能: 与上类似，key是long long，value是double的键值对插入函数。
*详述: 无。
*注意: 无。
*/
Z_API int zH_llinsert_double(z_hash_t *, long long, double);

/**
*参数: z_hash_t * - 结构体指针;
*      z_obj_t * - 查找的键值对的key;
*返回值: 找到返回value，未找到返回NULL。
*功能: z_hash_t中查找key是z_obj_t的函数。
*详述: 实际在z_hash_t中保存的是基本数据类型封装为z_ll_t、z_string_t、z_double_t、z_array_t之后的结构体。
*注意: 无。
*/
Z_API z_obj_t* zH_find(const z_hash_t *, const z_obj_t *);

/**
*参数: z_hash_t * - 结构体指针;
*      long long - 查找的键值对的key的值;
*返回值: 找到返回value，未找到返回NULL。
*功能: z_hash_t中查找key是long long的函数，找到返回value，未找到返回NULL。
*详述: 实际在z_hash_t中保存的是基本数据类型封装为z_ll_t、z_string_t、z_double_t、z_array_t之后的结构体。
*注意: 无。
*/
Z_API z_obj_t* zH_llfind(const z_hash_t *, long long);

/**
*参数: z_hash_t * - 结构体指针;
*      long long - 查找的键值对的key的值;
*      int * - 接收找到的值的指针;
*返回值: 查找到该key的话，将value结构体的中保存的值赋值给第三个参数，并返回value，否则返回NULL。
*功能: 获取z_hash_t中key是long long的键值对的value的值。
*详述: 实际在z_hash_t中保存的是基本数据类型封装为z_ll_t、z_string_t、z_double_t、z_array_t之后的结构体。
*注意: 只有当value中保存的值是z_ll_t或者z_string_t时才会正确返回数值，z_ll_t的值是原值返回并强转类型为int；z_string_t的值会将字符串格式化为long long型然后返回。
*/
Z_API z_obj_t* zH_llfind_int(const z_hash_t *, long long, int *);

/**
*参数: z_hash_t * - 结构体指针;
*      long long - 查找的键值对的key的值;
*      long long * - 接收找到的值的指针;
*返回值: 查找到该key的话，将value结构体的中保存的值赋值给第三个参数，并返回value，否则返回NULL。
*功能: 与上类似，将value结构体的中保存的值赋值给第三个参数。
*详述: 无。
*注意: 只有当value中保存的值是z_ll_t或者z_string_t时才会正确返回数值，z_ll_t的值是原值返回；z_string_t的值会将字符串格式化为long long型然后返回。
*/
Z_API z_obj_t* zH_llfind_ll(const z_hash_t *, long long, long long *);

/**
*参数: z_hash_t * - 结构体指针;
*      long long - 查找的键值对的key的值;
*      double * - 接收找到的值的指针;
*返回值: 查找到该key的话，将value结构体的中保存的值赋值给第三个参数，并返回value，否则返回NULL。
*功能: 与上类似，将value结构体的中保存的double值赋值给第三个参数。
*详述: 无。
*注意: 只有当value中保存的值是z_double_t、z_ll_t或者z_string_t时才会正确返回数值，z_ll_t的值是原值强转为double返回；z_string_t的值会将字符串格式化为double型然后返回。
*/
Z_API z_obj_t* zH_llfind_double(const z_hash_t *, long long, double *);

/**
*参数: z_hash_t * - 结构体指针;
*      long long - 查找的键值对的key的值;
*返回值: 查找到该key的话，将value返回，否则返回NULL。
*功能: z_hash_t中查找key是long long的键值对，如果value不是一个z_string_t*，则返回NULL，否则返回这个z_string_t*。
*详述: 无。
*注意: 无。
*/
Z_API z_string_t* zH_llfind_string(const z_hash_t *, long long);

/**
*参数: z_hash_t * - 结构体指针;
*      long long - 查找的键值对的key的值;
*返回值: 查找到该key的话，将value返回，否则返回NULL。
*功能: z_hash_t中查找key是long long的键值对，如果value不是一个z_array_t*，则返回NULL，否则返回这个z_array_t*。
*详述: 无。
*注意: 无。
*/
Z_API z_array_t* zH_llfind_array(const z_hash_t *, long long);

/**
*参数: z_hash_t * - 结构体指针;
*      long long - 查找的键值对的key的值;
*返回值: 查找到该key的话，将value返回，否则返回NULL。
*功能: z_hash_t中查找key是long long的键值对，如果value不是一个z_hash_t*，则返回NULL，否则返回这个z_array_t*。
*详述: 无。
*注意: 无。
*/
Z_API z_hash_t* zH_llfind_hash(const z_hash_t *, long long);

/**
*参数: z_hash_t * - 结构体指针;
*      char * - 查找的键值对的key的值;
*返回值: 查找到该key的话，将value返回，否则返回NULL。
*功能: z_hash_t中查找key是char*的键值对，如果找到则返回value，否则返回NULL。
*详述: 无。
*注意: 无。
*/
Z_API z_obj_t* zH_strfind(const z_hash_t *, const char *);

/**
*参数: z_hash_t * - 结构体指针;
*      char * - 查找的键值对的key的值;
*      int * -  接收找到的值的指针;
*返回值: 查找到该key的话，将value结构体的中保存的值赋值给第三个参数，并返回value。
*功能: z_hash_t中查找key是char*的键值对，并将找到的value的值返回。
*详述: 无。
*注意: 只有当value中保存的值是z_ll_t或者z_string_t时才会正确返回数值，z_ll_t的值是原值返回并强转类型为int；z_string_t的值会将字符串格式化为long long型然后返回。
*/
Z_API z_obj_t* zH_strfind_int(const z_hash_t *, const char *, int *);

/**
*参数: z_hash_t * - 结构体指针;
*      char * - 查找的键值对的key的值;
*      long long * -  接收找到的值的指针;
*返回值: 查找到该key的话，将value结构体的中保存的值赋值给第三个参数，并返回value。
*功能: 与上类似，将value结构体的中保存的值赋值给第三个参数。
*详述: 无。
*注意: 只有当value中保存的值是z_ll_t或者z_string_t时才会正确返回数值，z_ll_t的值是原值返回；z_string_t的值会将字符串格式化为long long型然后返回。
*/
Z_API z_obj_t* zH_strfind_ll(const z_hash_t *, const char *, long long *);

/**
*参数: z_hash_t * - 结构体指针;
*      char * - 查找的键值对的key的值;
*      double * -  接收找到的值的指针;
*返回值: 查找到该key的话，将value结构体的中保存的值赋值给第三个参数，并返回value。
*功能: 与上类似，将value结构体的中保存的double值赋值给第三个参数。
*详述: 无。
*注意: 只有当value中保存的值是z_double_t、z_ll_t或者z_string_t时才会正确返回数值，z_ll_t的值是原值强转为double返回；z_string_t的值会将字符串格式化为double型然后返回。
*/
Z_API z_obj_t* zH_strfind_double(const z_hash_t *, const char *, double *);

/**
*参数: z_hash_t * - 结构体指针;
*      char * - 查找的键值对的key的值;
*返回值: 查找到该key的话，将value返回，否则返回NULL。
*功能: z_hash_t中查找key是char*的键值对，如果value不是一个z_string_t*，则返回NULL，否则返回这个z_string_t*。
*详述: 无。
*注意: 无。
*/
Z_API z_string_t* zH_strfind_string(const z_hash_t *, const char *);

/**
*参数: z_hash_t * - 结构体指针;
*      char * - 查找的键值对的key的值;
*返回值: 查找到该key的话，将value返回，否则返回NULL。
*功能: z_hash_t中查找key是char*的键值对，如果value不是一个z_array_t*，则返回NULL，否则返回这个z_array_t*。
*详述: 无。
*注意: 无。
*/
Z_API z_array_t* zH_strfind_array(const z_hash_t *, const char *);

/**
*参数: z_hash_t * - 结构体指针;
*      char * - 查找的键值对的key的值;
*返回值: 查找到该key的话，将value返回，否则返回NULL。
*功能: z_hash_t中查找key是char*的键值对，如果value不是一个z_hash_t*，则返回NULL，否则返回这个z_hash_t*。
*详述: 无。
*注意: 无。
*/
Z_API z_hash_t* zH_strfind_hash(const z_hash_t *, const char *);

/**
*参数: h - 结构体指针;
*      k - 查找的键值对的key的值;
*返回值: 如果hash中没有key是char*的键值对，则返回NULL，否则将这个key对应的value返回。
*功能: z_hash_t中移除一个key是char *的键值对。返回这个键值对的value。
*详述: 无。
*注意: 无。
*/
z_obj_t *zH_remove_by_str(z_hash_t *h, const char *k);

/**
*参数: z_hash_t * - 结构体指针;
*      z_obj_t * - 查找的键值对的key;
*返回值: 成功返回0，否则返回非0。
*功能: 从hash中删除一个key是第二个参数的键值对。
*详述: 无。
*注意: 无。
*/
Z_API int zH_delete_by_key(z_hash_t *, const z_obj_t *);

/**
*参数: z_hash_t * - 结构体指针;
*      long long - 查找的键值对的key的值;
*返回值: 成功返回0，否则返回非0。
*功能: 从hash中删除一个key是第二个参数的键值对。
*详述: 无。
*注意: 无。
*/
Z_API int zH_delete_by_ll(z_hash_t *, long long);

/**
*参数: z_hash_t * - 结构体指针;
*      char * - 查找的键值对的key的值;
*返回值: 成功返回0，否则返回非0。
*功能: 从hash中删除一个key是第二个参数的键值对。
*详述: 无。
*注意: 无。
*/
Z_API int zH_delete_by_str(z_hash_t *, const char *);

/**
*参数: z_hash_t * - 结构体指针;
*      z_obj_t * - 查找的键值对的原key;
*      z_obj_t * - 查找的键值对的新key;
*返回值: 成功返回0，否则返回非0。
*功能: 变更hash中某一键值对key为新key。第二个参数为原key，第三个参数为新key。
*详述: 根据第二个参数作为key查找hash中对应的键值对，将value作为新key的value插入到hash中，将原key对应的键值对从hash中删除。
*注意: 无。
*/
Z_API int zH_rename(z_hash_t *, z_obj_t *, z_obj_t *);

/**
*参数: z_hash_t * - 结构体指针;
*返回值: 成功返回0，否则返回非0。
*功能: 对z_hash_t内的键值对进行排序。排序依据是键值对中key从小到大。
*详述: 无。
*注意: 无。
*/
Z_API int zH_sort(z_hash_t *);

/**
*参数: z_hash_t * - 结构体指针;
*返回值: 成功返回0，否则返回非0。
*功能: 也是排序，但不清楚是什么排序。
*详述: 无。
*注意: 无。
*/
Z_API int zH_sort_cmp(z_hash_t *, obj_cmp_t);

/**
*参数: z_hash_t * - 结构体指针;
*      z_pair_t * - 要查找的键值对;
*返回值: NULL或下一个键值对。
*功能: 得到参数z_pair_t在z_hash_t中的下一个键值对z_pair_t，如果没有下一个键值对则返回NULL。
*      如果参数z_pair_t == NULL，则返回z_hash_t中第一个键值对z_pair_t，z_hash_t为空返回NULL。
*详述: 无。
*注意: 参数z_pair_t应是参数z_hash_t中的一个键值对或NULL。
*/
Z_API z_pair_t* zH_foreach(const z_hash_t *, const z_pair_t *);

/**
*参数: z_hash_t * - 结构体指针;
*      z_pair_t * - 要查找的键值对;
*返回值: NULL或下一个键值对。
*功能: 得到参数z_pair_t在z_hash_t中的上一个键值对z_pair_t，如果没有上一个键值对则返回NULL。
*      如果参数z_pair_t == NULL，则返回z_hash_t中最后一个键值对z_pair_t，z_hash_t为空返回NULL。
*详述: 无。
*注意: 参数z_pair_t应是参数z_hash_t中的一个键值对或NULL。
*/
Z_API z_pair_t* zH_rev_foreach(const z_hash_t *, const z_pair_t *);

/**
*参数: h - 结构体指针;
*      k - 要查找的键值对的key;
*返回值: NULL或键值对。
*功能: 从z_hash_t中得到key是z_obj_t的键值对z_pair_t，如果没有此key的键值对，则返回NULL。
*详述: 无。
*注意: 此函数可以和zH_foreach或zH_rev_foreach函数配合使用，以达到遍历z_hash_t键值对的功能。
*/
Z_API z_pair_t *zH_foreach_from(const z_hash_t *h, const z_obj_t *k);

/**
*参数: z_hash_t结构体指针;
*返回值: 键值对的个数。
*功能: 得到z_hash_t已存储键值对的个数。
*详述: 无。
*注意: 无。
*/
#define zH_count(h) (h->used_)

//==================================================================================================================================================================//
/*************************************************************************
 * tool api
 ************************************************************************/

/* json */
/**
*与json格式相关的api
*/

/**
*参数: json - 保存有json格式字符串的缓冲区结构体指针;
*返回值: 成功返回哈希结构体指针，否则返回NULL。
*功能: 将参数z_buffer_t转换为一个新初始化的z_hash_t结构体。
*详述: 实例:if (strcmp(buffer->ptr_, " { \"str1\" : 1, 123 :{ 2 : -2, \"str2\" = [ \"str3\", 3, -4 ] } }") == 0) {
                z_hash_t h = z_json2hash(buffer);
                strcmp(((z_string_t *)(((z_pair_t *)((z_list_node_t *)(z_hash_t->hd_->head_) + 1))->key_))->b_, "str1") == 0;
            }
*注意: z_buffer_t->ptr_中不应包含\n \t \r 等特殊符号。字符串序列应是一个正确的json格式字符序列。
*/
Z_API z_hash_t *z_json2hash(const z_buffer_t *json);

/**
*参数: js - 待转换的z_buffer_t;
*      h - 待插入的z_hash_t;
*返回值: 成功返回0，否则返回-1。
*功能: 将参数js转换插入到现有的h结构体。其他与上同。
*详述: 无。
*注意: js->ptr_中不应包含\n \t \r 等特殊符号。字符串序列应是一个正确的json格式字符序列。
*/
Z_API int z_json2hash_append(const z_buffer_t *js, z_hash_t *h);

/**
*参数: hash - 待转换的z_hash_t;
*返回值: 成功返回0，否则返回-1。
*功能: 将参数hash中保存的键值对转换为一个新初始化的z_buffer_t结构体，结构体内的字符串非格式化。
*详述: 无。
*注意: 转换后的字符串(z_buffer_t->ptr_)内并不带有换行符和空格缩进。也就是说并不是格式化的json字符串。
*/
Z_API z_buffer_t *z_hash2json(const z_hash_t *hash);


/**
*参数: h - 待转换的z_hash_t;
*      js - 待插入的z_buffer_t;
*返回值: 成功返回0，否则返回-1。
*功能: 将参数h转换追加保存到现有的js结构体，其他与上同。
*详述: 无。
*注意: 转换后的字符串(z_buffer_t->ptr_)内并不带有换行符和空格缩进。也就是说并不是格式化的json字符串。
*/
Z_API int z_hash2json_append(const z_hash_t *h, z_buffer_t *js);

/**
*参数: hash - 待转换的z_hash_t;
*返回值: 成功返回z_buffer_t指针，否则返回NULL。
*功能: 将参数z_hash_t转换为一个新初始化的z_buffer_t结构体，结构体内的字符串是json格式化的。
*详述: 无。
*注意: 转换后的字符串(z_buffer_t->ptr_)内带有换行符和空格缩进。也就是说是格式化的json字符串。
*/
Z_API z_buffer_t *z_hash2fmtjson(const z_hash_t *hash);

/**
*参数: file_name - 字符串形式的文件路径和名称;
*返回值: 成功返回z_hash_t指针，否则返回NULL。
*功能: 将一个json格式的文件转换为一个z_hash_t结构体。
*详述: 无。
*注意: 这个json格式的文件内可以使用#做注释，#和其后直至\n的内容均不会保存到z_hash_t中。
*/
Z_API z_hash_t* z_json_file(const char *file_name);

/**
*参数: h - 待转换的z_hash_t;
*      g - 要存入的z_buffer_t;
*返回值: 成功返回0。
*功能: 将一个z_hash_t结构体内的键值对转换为gems协议格式追加保存到z_buffer_t中。
*详述: 无。
*注意: 关于gems协议的格式：[数据类型段][数据长度段][数据值段][数据类型段][数据长度段][数据值段]....
*          数据类型段：使用一个大写字母的ASCII码表示，'H'表示z_hash_t、'S'表示z_string_t、'L'表示z_ll_t、'D'表示z_double_t、'A'表示z_array_t；
*          数据长度段：长度为sizeof(size_t)，表示的数据长度即为本数据类型->used_。注意，当数据类型是L或D时，没有[数据长度]字段。
*          数据值段：对应数据类型的值。
*/
Z_API int z_hash2gems_append(const z_hash_t *h, z_buffer_t *g);

/**
*参数: hash - 待转换的z_hash_t;
*返回值: 返回该z_buffer_t*。
*功能: 与上类似，本函数自动初始化一个z_buffer_t并完成转换。
*详述: 无。
*注意: 同上。
*/
Z_API z_buffer_t *z_hash2gems(const z_hash_t *hash);

/**
*参数: g - 待转换的存储gems格式的z_buffer_t;
*      h - 待插入的z_hash_t;
*返回值: 成功返回0，否则返回-1。
*功能: 将一个gems格式的z_buffer_t转换插入到z_hash_t中。
*详述: 无。
*注意: 无。
*/
int z_gems2hash_append(const z_buffer_t *g, z_hash_t *h);

/**
*参数: g - 待转换的存储gems格式的z_buffer_t;
*      h - 待插入的z_hash_t;
*返回值: 成功返回完成的z_hash_t，否则返回NULL。
*功能: 与上类似，本函数会自行声明并初始化一个z_hash_t，转换后返回该z_hash_t*。
*详述: 无。
*注意: 无。
*/
z_hash_t *z_gems2hash(const z_buffer_t *gems);

//==================================================================================================================================================================//
/* stream */
/**
*流结构体
*主要被用于文件映射内存后的操作
*/

/**
*结构体字段描述:
*   ptr_ - 文件的存储映射部分的开始地址; 
size_ - 文件的大小;
pos_ - 地址偏移量;
read_char_ - 文件的读字符函数;
test_ - 文件的测试函数;
read_ - 可自定义的读函数;
write_ - 可自定义的写函数;
eof_ - 地址偏移量判断函数，若pos_大于等size_，未完待续;
*/
#define Z_STREAM_FIELDS \
    char *ptr_; size_t size_; size_t pos_; \
    char (*read_char_)(struct z_stream *); \
    int (*test_)(const struct z_stream *, char ); \
    int (*read_)(struct z_stream *, void *, size_t); \
    int (*write_)(struct z_stream *, void *, size_t); \
    int (*eof_)(const struct z_stream *); \
    void (*free_)(struct z_stream *); \
    char (*current_)(const struct z_stream *)
typedef struct z_stream { Z_STREAM_FIELDS; } z_stream_t;

/**
*参数: char * - 字符串形式的文件路径和名称;
*返回值: z_stream_t结构体指针。
*功能: 使用mmap函数映射给定的文件到内存，并使用一个z_stream_t结构体描述这个映射。
*详述: 无。
*注意: 无。
*/
Z_API z_stream_t* zFS_init(const char *);

//==================================================================================================================================================================//
/* timer */
/**
这是一个类似于管理计时器的结构体其中包含多个计时器：
*/

#define TIMER_MAX_BUF 4096
typedef struct z_timer z_timer_t;
typedef z_timer_t* (*z_timer_get_func_t)(void);

/**
*参数: get_func - 如何获取z_timer_t的回掉函数;
*返回值: 无。
*功能: 用来设置获取z_timer_t的自定义回调函数。
*详述: 无。
*注意: 无。
*/
Z_API void z_timer_set_callback(z_timer_get_func_t get_func);

/**
*参数: 无;
*返回值: z_timer_t指针。
*功能: 初始化一个z_timer_t。实际为calloc一个z_timer_t结构体空间。
*详述: 无。
*注意: 无。
*/
Z_API z_timer_t* z_timer_init(void);

/**
*参数: task_name - 新增的计时器的名字，你可以自己随意取一个;
*返回值: 操作成功返回0，z_timer_t未初始化返回-1，z_timer_t已满返回-2，如果已存在task_name对应的时间信息，返回-3。
*功能: 开始记录一个时间信息到z_timer_t中。
*详述: 本函数会使用z_timer_set_callback函数设定的函数来获取需要的z_timer_t，然后在z_timer_t中新增task_name对应的开始时间信息（1970年1月1日到现在的微秒数）到z_timer_t->start_[x]中。
*注意: 使用z_timer_init函数初始化一个z_timer_t之后，并且使用z_timer_set_callback函数设定了获取线程z_timer_t的函数之后，再使用本函数。
*/
Z_API int z_timer_task_start(const char *task_name);

/**
*参数: task_name - 你想结束的那个计时器的名字，与z_timer_task_start的参数对应;
*返回值: 操作成功返回0，z_timer_t未初始化返回-1，如果不存在task_name的计时器则返回-2，如果task_name计时器状态不是启动，返回-3。
*功能: 使用本函数结束计时，所有记录的总时间会保存在elapse_中（也可以理解为所有流逝的时间）。
*详述: 无。
*注意: 使用z_timer_init函数初始化一个z_timer_t之后，并且使用z_timer_set_callback函数设定了获取线程z_timer_t的函数之后，并且使用z_timer_task_start来开始记录一个时间信息到z_timer_t中，
*      然后再使用本函数来结束计时。
*/
Z_API int z_timer_task_end(const char *task_name);

/**
*参数: timer - 要释放的计时器管理结构体指针;
*返回值: 无。
*功能: 释放传参指定z_timer_t的函数。
*详述: 无。
*注意: 无。
*/
Z_API void z_timer_free_timer(z_timer_t *timer);

/**
*参数: 无;
*返回值: 无。
*功能: 释放z_timer_set_callback回调函数获取的z_timer_t的函数。
*详述: 无。
*注意: 无。
*/
Z_API void z_timer_free(void);

/**
*参数: 无;
*返回值: 无。
*功能: 重置z_timer_set_callback回调函数获取的z_timer_t的函数。
*详述: 无。
*注意: 无。
*/
Z_API void z_timer_reset(void);

/**
*参数: buf - 接收格式化后的字符串指针;
*返回值: 成功返回0，否则返回-1。
*功能: 将z_timer_t中的所有计数器的信息全部格式化为字符串保存到传入参数buf中。。
*详述: 实例：z_timer_t->name_[0] == "p0."; z_timer_t->count_[0] == 3; z_timer_t->elapse_ == 1495591629299281;
             z_timer_t->name_[1] == "p1."; z_timer_t->count_[0] == 2; z_timer_t->elapse_ == 1495591629299282;
             z_timer_t->name_[2] == "p2."; z_timer_t->count_[0] == 1; z_timer_t->elapse_ == 1495591629299283;
             z_timer_log_to_buffer(buf);
             puts(buf)；
       结果：[p0.:3:1495591629299281] [p1.:2:1495591629299282] [p2.:1:1495591629299283] 
*注意: 无。
*/
Z_API int z_timer_log_to_buffer(char *buf);

//==================================================================================================================================================================//
/* log */
/**
*这是一个日志管理的模块，日志的类型和对应的级别如下:
*DEBUG     1
*TRACE     2
*NOTICE    3
*WARNING   4
*ERROR     5
*FATAL     6
*MONITOR  17
*MASK     15
*应使用宏进行日志的打印，使用实例: Z_LOG_NOTICE("%s,one test%d", "this", 2);
*/

#define Z_LV_DEBUG     1
#define Z_LV_TRACE     2
#define Z_LV_NOTICE    3
#define Z_LV_WARNING   4
#define Z_LV_ERROR     5
#define Z_LV_FATAL     6

#define Z_LV_MONITOR  17

#define Z_LV_MASK     15

#define Z_LOG_ID_SYSTEM 100000000

#define Z_LOG_SET_CALLBACK(func) z_log_set_callback(func)
#define Z_LOG_INIT(file_name, level) z_log_init(file_name, level)
#define Z_LOG_FREE() z_log_free()
#ifdef PRO_F
#define Z_LOG_DEBUG(fmt, ...)
#define Z_LOG_TRACE(fmt, ...)
#define Z_LOG_NOTICE(fmt, ...)
#define Z_LOG_MONITOR(fmt, ...)
#define Z_LOG_WARNING(fmt, ...)
#define Z_LOG_ERROR(fmt, ...)
#define Z_LOG_FATAL(fmt, ...)
#define Z_LOG_FLUSH()
#define Z_TIMER_TASK_START(task_name)
#define Z_TIMER_TASK_END(task_name)
#define Z_TIMER_RESET()
#else
#define Z_LOG_FLUSH() z_log_flush()
#define Z_TIMER_TASK_START(task_name) z_timer_task_start(task_name)
#define Z_TIMER_TASK_END(task_name) z_timer_task_end(task_name)
#define Z_TIMER_RESET() z_timer_reset()
    #ifdef DEBUG_F
    #define Z_LOG_DEBUG(fmt, ...) do { z_log_debug(__FILE__, __LINE__, fmt, ##__VA_ARGS__); z_log_flush(); } while (0)
    #define Z_LOG_TRACE(fmt, ...) do { z_log_trace(__FILE__, __LINE__, fmt, ##__VA_ARGS__); z_log_flush(); } while (0)
    #define Z_LOG_NOTICE(fmt, ...) do { z_log_notice(__FILE__, __LINE__, fmt, ##__VA_ARGS__); z_log_flush(); } while (0)
    #define Z_LOG_MONITOR(fmt, ...) do { z_log_monitor(__FILE__, __LINE__, fmt, ##__VA_ARGS__); z_log_flush(); } while (0)
    #define Z_LOG_WARNING(fmt, ...) do { z_log_warning(__FILE__, __LINE__, fmt, ##__VA_ARGS__); z_log_flush(); } while (0)
    #define Z_LOG_ERROR(fmt, ...) do { z_log_error(__FILE__, __LINE__, fmt, ##__VA_ARGS__); z_log_flush(); } while (0)
    #define Z_LOG_FATAL(fmt, ...) do { z_log_fatal(__FILE__, __LINE__, fmt, ##__VA_ARGS__); z_log_flush(); } while (0)
    #else
    #define Z_LOG_DEBUG(fmt, ...) z_log_debug(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
    #define Z_LOG_TRACE(fmt, ...) z_log_trace(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
    #define Z_LOG_NOTICE(fmt, ...) z_log_notice(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
    #define Z_LOG_MONITOR(fmt, ...) z_log_monitor(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
    #define Z_LOG_WARNING(fmt, ...) z_log_warning(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
    #define Z_LOG_ERROR(fmt, ...) z_log_error(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
    #define Z_LOG_FATAL(fmt, ...) z_log_fatal(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
    #endif
#endif

typedef struct z_log z_log_t;
typedef z_log_t* (*z_log_get_func_t)(void);

/**
*参数: get_func - 如何获取z_log_t的回掉函数;
*返回值: 无。
*功能: 回调函数，用来设置获取z_log_t的自定义回调函数。。
*详述: 无。
*注意: 无。
*/
Z_API void z_log_set_callback(z_log_get_func_t get_func);

/**
*参数: file_name - 指定日志的文件名;
*      level - 日志的级别;
*返回值: z_log_t指针。
*功能: 初始化一个z_log_t结构体。
*详述: 根据 level 参数设定该z_log_t->level_，根据file_name打开/创建file_name + ".log" 和 file_name + ".log.wf"两个文件，并初始化两个文件的缓冲区结构体。
*注意: 无。
*/
Z_API z_log_t* z_log_init(const char *file_name, int level);

/**
*参数: z_log_t * - 要释放的日志结构体指针;
*返回值: 无。
*功能: 先将缓冲区（.log和log.wf）的内容全部flush到文件中，然后释放掉传入参数z_log_t。
*详述: 无。
*注意: 无。
*/
Z_API void z_log_free_log(z_log_t *);

/**
*参数: 无;
*返回值: 无。
*功能: 不需传入要释放的z_log_t，而是使用z_log_set_callback设定过的回调函数来获取z_log_t，然后不处理缓冲区直接释放掉这个z_log_t。
*详述: 无。
*注意: 无。
*/
Z_API void z_log_free(void);

/**
*参数: file - 可以认为是文件名的字符串;
*      line - 可以认为是日志产生的源文件中的行号;
*      fmt - 要将可变参数格式化的格式化样式;
*      ... - 可变参数;
*返回值: 成功返回0，否则返回-1。
*功能: 打印debug日志函数。
*详述: 无。
*注意: 不建议使用此函数，在开发时，需要打印日志时应使用对应日志级别对应的宏，例如：Z_LOG_DEBUG 、Z_LOG_TRACE、Z_LOG_NOTICE、Z_LOG_WARNING、Z_LOG_ERROR、Z_LOG_FATAL等。
*/
Z_API int z_log_debug(const char *file, unsigned int line, const char *fmt, ...);

/**
*参数: 同上;
*返回值: 同上。
*功能: 同上，日志级别是trace。
*详述: 无。
*注意: 同上。
*/
Z_API int z_log_trace(const char *file, unsigned int line, const char *fmt, ...);

/**
*参数: 同上;
*返回值: 同上。
*功能: 同上，日志级别与函数名对应。
*详述: 无。
*注意: 同上。
*/
Z_API int z_log_notice(const char *file, unsigned int line, const char *fmt, ...);

/**
*参数: 同上;
*返回值: 同上。
*功能: 同上，日志级别与函数名对应。
*详述: 无。
*注意: 同上。
*/
Z_API int z_log_monitor(const char *file, unsigned int line, const char *fmt, ...);

/**
*参数: 同上;
*返回值: 同上。
*功能: 同上，日志级别与函数名对应。
*详述: 无。
*注意: 同上。
*/
Z_API int z_log_warning(const char *file, unsigned int line, const char *fmt, ...);

/**
*参数: 同上;
*返回值: 同上。
*功能: 同上，日志级别与函数名对应。
*详述: 无。
*注意: 同上。
*/
Z_API int z_log_error(const char *file, unsigned int line, const char *fmt, ...);

/**
*参数: 同上;
*返回值: 同上。
*功能: 同上，日志级别与函数名对应。
*详述: 无。
*注意: 同上。
*/
Z_API int z_log_fatal(const char *file, unsigned int line, const char *fmt, ...);

/**
*参数: 无;
*返回值: 成功返回0，否则返回-1。
*功能: 将日志结构体中缓存的还未实际写入文件的内容全部写入文件中。
*详述: z_log_t->log_buffer_和wf_log_buffer_中的日志写到文件中去。
*注意: 无。
*/
Z_API int z_log_flush(void);

/**
*参数: unsigned int - 想要设定的日志id;
*返回值: 无。
*功能: 设定日志id函数，如果参数int为0，则设定一个伪随机数。
*详述: 无。
*注意: 无。
*/
Z_API void z_log_set_logid(unsigned int);

/**
*参数: 无;
*返回值: 返回一个日志id，如果日志id是0，则设定一个伪随机数，并返回这个数。
*功能: 返回一个日志id，如果日志id是0，则设定一个伪随机数，并返回这个数。
*详述: 无。
*注意: 无。
*/
Z_API unsigned int z_log_get_logid(void);

/**
*参数: 无;
*返回值: 无。
*功能: 重置日志id函数，将日志id设置为一个伪随机数。
*详述: 无。
*注意: 无。
*/
Z_API void z_log_reset_logid(void);

/**
*参数: 无;
*返回值: 伪随机数。
*功能: 产生一个伪随机数。
*详述: 无。
*注意: 无。
*/
Z_API double z_rand_double(void);

/**
*参数: min - 伪随机数的最小值;
*      max - 伪随机数的最大值;
*返回值: 伪随机数。
*功能: 在min和max之间产生一个伪随机数。
*详述: 无。
*注意: 无。
*/
Z_API int z_rand(int min, int max);

/**
*参数: MAX_CMD - 宏定义的最大cmd个数;
*返回值: 无。
*功能: 声明一个有MAX_CMD个元素的一维字符串指针数组。
*详述: 该数组其实用来明确cmd（是一个unsigned int数）与其名称之间的对应关系，例如你设定编号是0x1001的cmd名称叫做"sge_test_req"，
*      那么 g_cmd2name_mapping[]正确使用的结果应满足 strcmp(g_cmd2name_mapping[0x1001], "sge_test_req") == 0
*注意: 无。
*/
Z_API const char *g_cmd2name_mapping[MAX_CMD];

#ifdef REPLAY_F
Z_API char g_log_biz_clock[32];
#endif

//==================================================================================================================================================================//
/* net */
/**
*linux下对网络套接字的操作等于对文件描述符的操作，所以net部分使用描述符指代 socket descriptor 或 file descriptor。
*涉及select()机制、epoll机制
*/

/**
*参数: sd - 目标描述符;
*返回值: 如果操作成功或描述符原本已具有非阻塞I/O状态标志，则返回0；否则返回-1。
*功能: 变更描述符的状态标志，将该描述符设置为 非阻塞I/O。
*详述: 获取目标描述符的文件状态标志，判断是否已具有非阻塞I/O的标志，如果没有则加上非阻塞I/O标志。
*注意: 无。
*/
Z_API int z_setsocktonoblock(int sd);

/**
*参数: sd - 目标描述符;
*返回值: 如果操作成功或描述符原本已具有阻塞I/O状态标志，则返回0；否则返回-1。
*功能: 变更描述符的状态标志，将该描述符设置为 阻塞I/O。
*详述: 与上类似。
*注意: 无。
*/
Z_API int z_setsocktoblock(int sd);

/**
*参数: fd - 目标描述符;
*      ptr1 - 要写入的字符串地址;
*      nbytes - 要写入的字符串长度;
*      msecs - 如果需要指明select时的超时时间，则此参数应为大于0，它是一个毫秒数，否则等待无限长的时间;
*返回值: 如果操作成功，返回写入的字节数（即参数nbytes）。否则返回-1。
*功能: 可以理解为使用select机制进行非阻塞I/O式的描述符写操作的封装。写成功后会将描述符状态标志设定为阻塞I/O，不成功的话会还原描述符的状态标志。
*      通过参数指定目标描述符，写内容的地址，要写的长度和select调用时的超时时间。
*详述: 如果fd的状态标志是阻塞I/O，则先将其变更为非阻塞I/O,然后使用select获取该描述符是否可写（通过msecs设定超时时间），如果可写则将要写的内容（依据ptr1和nbytes）写入fd。返回写入的字节数量。
*注意: 无。
*/
Z_API int z_swriteo_ms_ex(int fd, void *ptr1, size_t nbytes, int msecs);

/**
*参数: fd - 目标描述符;
*      ptr1 - 要读出的字符串的存放地址;
*      nbytes - 要读出的字符串长度;
*      msecs - 如果需要指明等待的时间，则此参数应为大于0，它是一个毫秒数，否则等待无限长的时间;
*返回值: 如果操作成功，返回读出的字节数（可能是参数nbytes）。否则返回-1。
*功能: 可以理解为使用select机制进行描述符读操作的封装，不变更描述符的状态标志。
*      通过参数指定目标描述符，读内容的地址，要读的长度和select调用时等待的时间。
*详述: 使用select获取该描述符是否可读（通过msecs设定超时时间），如果可读则从描述符中读出内容（依据ptr1和nbytes）。返回实际读出的字节数量。
*注意: 无。
*/
Z_API int z_sreado_ms_ex(int fd, void *ptr1, size_t nbytes, int msecs);

/**
*参数: 无;
*返回值：操作成功返回创建的socket的描述符，否则返回-1。
*功能：创建一个使用PF_INET协议族、SOCK_STREAM类型的socket。并设置这个socket的选项，使该socket在使用时端口释放后立即就可以被再次使用。
*详述: 无。
*注意：如果设置socket选项时失败会返回-1，并close这个socket。
*/
Z_API int z_socket(void);

/**
*参数: fd - 目标描述符;
*返回值: 如果没有数据可读时返回0；如果有数据可读或连接已中止或其他错误时返回-1。
*功能: 用来检查某个可用的描述符是否已经无数据可读。
*详述: 仅本次非阻塞式的从目标描述符上尝试recv数据，如果没有数据可读时返回0，否则返回-1。
*注意: 无。
*/
Z_API int z_sock_check(int fd);

/**
*参数: port - 本服务端要监听的端口号;
*      queue - 设定监听时连接请求队列的大小;
*返回值: 操作成功返回socket。否则返回-1。
*功能: 创建一个使用PF_INET协议族、SOCK_STREAM类型的socket，并绑定到AF_INET协议组、不限地址、指定端口上，然后监听这个socket，连接请求队列的大小为queue参数值。
*详述: 无。
*注意: 无。
*/
Z_API int z_tcplisten(int port, int queue);

/**
*参数: fd - 目标描述符;
*返回值: 参照close函数。
*功能: close(fd)。
*详述: 无。
*注意: 无。
*/
Z_API int z_close(int fd);

/**
*参数: sockfd - 已经正在监听的socket描述符;
*      auth_ip - 相当于一个白名单，auth_ip->data[x]可以是z_string_t*，也可以是z_hash_t*。
*              白名单中或者以一个z_string_t*结构保存某个具体的白名单IP，或者以一个z_hash_t*结构保存某些白名单的IP范围。
*              例：
*              如果是z_string_t*，则((z_string_t *)(auth_ip->data[x]))->b_->ptr_应指向一个IP字符串地址，例如："127.0.0.1"
*              如果是z_hash_t*,则该结构中应以某个键值作为白名单的范围，键为范围的最小IP，值为范围的最大IP，且键和值均应为z_string_t*结构。
*              可以为NULL，为NULL则不检查链接的客户端IP地址。
*返回值: 成功接受一个客户端的链接请求且该客户端地址在白名单之上（若传入白名单）时返回该链接的描述符，否则返回-1。
*功能: 在指定socket描述符上等待接受客户端的链接请求，接受一个链接后判断该链接客户端地址是否属于白名单中的地址，如果auth_ip为NULL，则不判断。然后返回这个客户端链接的描述符。
*详述: 无。
*注意: 无。
*/
Z_API int z_accept(int sockfd, z_array_t *auth_ip);


/**
*参数: sockfd - 目标描述符;
*      ip - 目标服务器的IP，应是一个IPv4的点分十进制的IP地址字符串;
*      port - 目标服务器的端口号;
*      ms - 如果需要指明select时的超时时间，则此参数应为大于0，它是一个毫秒数，否则等待无限长的时间;
*返回值: 链接建立成功返回0，否则返回-1。
*功能: 通过目标描述符，尝试与指定的ip端口进行非阻塞式connect，允许ms毫秒的超时时间。
*详述: 描述符以非阻塞方式与指定的ip端口进行connect，然后使用select机制检查该描述符是否已可用，若可用则返回0，否则返回-1。
*注意: 不管该描述符的链接是否建立成功，都会还原该描述符原有的状态标志。
*/
Z_API int z_rpc_connect(int sockfd, const char *ip, int port, int ms);

/**
*参数: fd - 目标描述符;
*      ms - 如果需要指明select时的超时时间，则此参数应为大于0，它是一个毫秒数，否则等待无限长的时间;
*返回值: 描述符可读返回1，否则返回0或负值。
*功能: 使用select获取目标描述符的可读状态。
*详述: 无。
*注意: 无。
*/
Z_API int z_sreadable_ms(int fd, int ms);

/**
*参数: fd - 目标描述符;
*      buf - 读出的字符串的存放地址;
*      nbytes - 预期读出字符串的长度;
*返回值: 成功时返回实际读取的字节数，失败时返回-1。
*功能: 从目标描述符读取nbytes个字节的信息，将地址保存到buf中。
*详述: 无。
*注意: 无。
*/
Z_API int z_net_read(int fd, void *buf, size_t nbytes);

/**
*参数: fd - 目标描述符;
*      buf - 要写入的字符串的存放地址;
*      nbytes - 预期写入字符串的长度;
*返回值: 成功时返回实际写入的字节数，失败时返回-1。
*功能: 向目标描述符写入nbytes个字节的信息，若描述符不能一次全部写完，则会尝试写完余下的信息。
*详述: 无。
*注意: 无。
*/
Z_API int z_net_write(int fd, void *buf, size_t nbytes);

/**
*参数: fd - 目标描述符;
*      ptr1 - 要写入的字符串的存放地址;
*      nbytes - 预期写入字符串的长度;
*返回值: 成功时返回实际写入的字节数，失败时返回小于0。
*功能: 向目标描述符写入nbytes个字节的信息，若描述符不能一次全部写完，则不再尝试余下的信息。
*详述: 无。
*注意: 此接口名虽写着noblock，但实际此接口不具备非阻塞的写操作。
*/
Z_API int z_write_noblock(int fd, void *ptr1, size_t nbytes);

/**
*参数: fd - 目标描述符;
*返回值: 无。
*功能: 将目标描述符关联的对端ip地址和端口打印到日志中。
*详述: 正常打印级别是 Z_LV_TRACE ，失败时日志级别是 Z_LV_ERROR。
*注意: 无。
*/
Z_API void z_net_trace_fd_addr(int fd);

//==================================================================================================================================================================//
/* crypt */

/**
*参数: buf - 源字符串;
*返回值: 经过校验后的校验码。
*功能: 对源字符串进行crc32校验。
*详述: 无。
*注意: 无。
*/
Z_API uint32_t z_crc32_str(register const char *buf);

/**
*参数: buf - 源字符串;
*      buf_len - 指定校验源字符串的长度;
*返回值: 经过校验后的校验码。
*功能: 对源字符串的前buf_len字节进行crc32校验。
*详述: 无。
*注意: 无。
*/
Z_API uint32_t z_crc32(const char *buf, uint32_t buf_len);

/**
*参数: c - 源字符;
*返回值: 返回一个字符。
*功能: 获得源字符转为十六进制后前一位，以字符形式返回。
*详述: 例如c=00100001，则返回'2'，例如c=11100001，则返回'E'。
*注意: 无。
*/
Z_API char z_hex_char_high_encoding(char c);

/**
*参数: c - 源字符;
*返回值: 返回一个字符。
*功能: 获得源字符转为十六进制后后一位，以字符形式返回。
*详述: 例如c=00100101，则返回'5'，例如c=11101101，则返回'D'。
*注意: 无。
*/
Z_API char z_hex_char_low_encoding(char c);

/**
*参数: c - 源字符;
*返回值: 返回一个字符。
*功能: 无。
*详述: 如果源字符是一个数字，则返回该数字与0的差；如果是一个大写字母或小写字母，则返回该字母与'A'或'a'的差 + 10。
*注意: 无。
*/
Z_API char z_hex_char_decoding(char c);

/**
*参数: - ;
*返回值: 。
*功能: 。
*详述: 。
*注意: 。
*/
Z_API int z_hex_encoding(const char *in, size_t in_len, char *out, size_t out_len);

/**
*参数: - ;
*返回值: 。
*功能: 。
*详述: 。
*注意: 。
*/
Z_API int z_hex_decoding(const char *in, char *out, size_t out_len);


//==================================================================================================================================================================//
/* task cache */
/**
*z_task_cache_t 这是一个被用来当作任务缓存的队列结构体，
*该队列默认大小由 TC_SIZE 定义，使用时应注意在队列中的任务数量不要超过这个值，
*队列满与队列空分别使用 TC_ERR_FULL 和 TC_ERR_EMPTY 宏来定义。
*不要直接对结构体的变量进行操作，应只使用本部分提供的api。
*/
#define TC_SIZE       10000000
#define TC_ERR_FULL         -1
#define TC_ERR_EMPTY        -2

typedef struct task_cache {
    volatile int head_, tail_;
    void * volatile (task_[TC_SIZE]);
} z_task_cache_t;

/**
*参数: 无;
*返回值: 一个任务缓存队列结构体指针。
*功能: 初始化一个任务缓存队列结构体。
*详述: 无。
*注意: 任务缓存队列不用后需要自行free。
*/
Z_API z_task_cache_t* zTC_init(void);

/**
*参数: tc - 目标队列;
*      t - 待入队列的任务;
*返回值: 入队成功返回0，队满返回 -1。
*功能: 将一个任务加入到目标队列中。
*详述: 无。
*注意: 无。
*/
Z_API int zTC_push(z_task_cache_t *tc, void *t);

/**
*参数: tc - 目标队列;
*      t - 接收任务的指针;
*返回值: 获取成功返回0，队空返回 -2。
*功能: 从目标队列中获得一个任务，但该任务不出队列。
*详述: 无。
*注意: 无。
*/
Z_API int zTC_get(z_task_cache_t *tc, void **t);

/**
*参数: tc - 目标队列;
*      t - 接收任务的指针;
*返回值: 获取成功返回0，队空返回 -2。
*功能: 从目标队列中获得一个任务，任务出队列。
*详述: 无。
*注意: 无。
*/
Z_API int zTC_pop(z_task_cache_t *tc, void **t);

/**
*参数: tc - 待释放队列;
*返回值: 释放成功返回0，否则非0。
*功能: 释放任务缓存队列。
*详述: 无。
*注意: 无。
*/
Z_API void zTC_free(z_task_cache_t *tc);

/**
*参数: tc - 目标队列;
*返回值: 队列中的任务数量。
*功能: 获取队列中的任务数量。
*详述: 无。
*注意: 无。
*/
Z_API int zTC_count(z_task_cache_t *tc);

#endif /* __Z_BASE_API_H__ */

