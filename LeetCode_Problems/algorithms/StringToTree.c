#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define READ_SIZE 12
#define QUEUE_SIZE 1024

#define ERR_CALLOC -1
#define ERR_FOPEN -2
#define ERR_F_EMPTY -3
#define ERR_FILE_INCORRECT -4

#define SET_RT_FLAG_THEN_GOTO(_rt_flag, _err) do { rt_flag = _rt_flag; goto _err;} while(0)

typedef struct s2t_rt_code {
    int rt_code;
    const char *rt_msg;
} s2t_rt_code_t;


s2t_rt_code_t rt[] = {
    {ERR_CALLOC, "call calloc queue failed."},
    {ERR_FOPEN, "Open TreeNode_List file failed."},
    {ERR_F_EMPTY, "TreeNode_List file is empty."},
    {ERR_FILE_INCORRECT, "TreeNode_List file is incorrect."},
    {0, NULL}
};

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct tmp_queue {
    struct TreeNode *node_;
    int is_has_lchild_;
} tmp_queue_t;

typedef struct TreeNode TreeNode_t;

int string_to_tree(TreeNode_t **rt_node, const char * file_name) {
    FILE * fd = NULL;
    int front = 0, rear = 0;
    int rt_flag = 0, read_len = 0, offset = 0, i = 0, num = 0, sign = 0;
    tmp_queue_t *que = NULL, *tmp_q = NULL;
    TreeNode_t *root = NULL, *new_node = NULL;
    if(NULL == (que = calloc(1, QUEUE_SIZE * sizeof(tmp_queue_t)))) SET_RT_FLAG_THEN_GOTO(ERR_CALLOC, END);   //创建队列结构体
    if(NULL == (fd = fopen(file_name, "r+b"))) SET_RT_FLAG_THEN_GOTO(ERR_FOPEN, END);
    fseek(fd, 0, SEEK_SET);
    char ch[READ_SIZE] = { 0 };
    read_len = fread(ch, 1, READ_SIZE, fd);         //读取 READ_SIZE 个字节
    if(read_len < 3) SET_RT_FLAG_THEN_GOTO(ERR_F_EMPTY, END);   //如果文件少于2个字节(文件至少应该是有一个元素，例如"2,")则失败
    if(ch[0] == 'n' || ch[0] == 'N') SET_RT_FLAG_THEN_GOTO(ERR_FILE_INCORRECT, END);    //如果根节点是空，则失败
    if(ch[0] == '-') sign = -1;
    else sign = 1;
    //读取根节点的数值
    for(i = 0, num = 0; i < read_len; i++) {
        if(ch[i] == ',' ) break;
        if(ch[i] == '-' ) continue;
        if(ch[i] == '\n') break;
        num = num * 10 + (ch[i] - '0');
    }
    if(i == read_len) SET_RT_FLAG_THEN_GOTO(ERR_FILE_INCORRECT, END);       //如果只有一个根节点，则失败
    offset += (i + 1);
    fseek(fd, offset, SEEK_SET);
    //创建根节点
    root = calloc(1 ,sizeof(TreeNode_t));
    root->val = num * sign;
    *rt_node = root; rt_flag = 1;

    //根结点入队列
    (que[rear]).node_ = root;
    (que[rear]).is_has_lchild_ = 0;
    rear = (rear + 1) % QUEUE_SIZE;

    while(1) {
        read_len = fread(ch, 1, READ_SIZE, fd);
        if(read_len <= 1) break;
        if(ch[0] == 'n' || ch[0] == 'N') {
            offset += 5;
            new_node = NULL;
        } else {
            if(ch[0] == '-') sign = -1;
            else sign = 1;
            for(i = 0, num = 0; i < read_len; i++) {
                if(ch[i] == ',') break;
                if(ch[i] == '-') continue;
                if(ch[i] == '\n') break;
                num = num * 10 + (ch[i] - '0');
            }
            if(i == read_len) offset += i;
            else offset += (i + 1);
            new_node = calloc(1, sizeof(TreeNode_t));
            new_node->val = num * sign;
        }
        if(front != rear) {
            tmp_q = &(que[front]);      //获取队头元素
            if(tmp_q->is_has_lchild_ == 0) {     //如果该元素未绑定过左子节点
                tmp_q->node_->left = new_node;
                tmp_q->is_has_lchild_ = 1;
            } else {                    //如果该元素已绑定过左子节点
                tmp_q->node_->right = new_node;
                //队头出队
                memset(&(que[front]), '\0', sizeof(tmp_queue_t));
                front = (front + 1) % QUEUE_SIZE;
            }
        } else {
            free(new_node);
            goto END;
        }
        if(new_node != NULL) {          //非空新结点入队
            (que[rear]).node_ = new_node;
            (que[rear]).is_has_lchild_ = 0;
            rear = (rear + 1) % QUEUE_SIZE;
            rt_flag++;
        }
        fseek(fd, offset, SEEK_SET);
    }
END:
    if(que) free(que);
    if(fd) fclose(fd);
    return rt_flag;
}
