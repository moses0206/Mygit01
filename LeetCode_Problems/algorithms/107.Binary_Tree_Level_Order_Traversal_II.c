#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "StringToTree.c"

/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
*/
int getTreeDeep(struct TreeNode *node, int up_deep, int *size) {
    if(!node) return up_deep;
    printf("node->val = %d\n", node->val);
    up_deep++;
    (*size)++;    
    int l_deep = getTreeDeep(node->left, up_deep, size);
    int r_deep = getTreeDeep(node->right, up_deep, size);
    return l_deep > r_deep ? l_deep : r_deep;
}

typedef struct wm_queue {
    struct TreeNode *node_;
    int deep_;
} wm_queue_t;

typedef struct wm_array {
    int val_;
    int is_null_;
} wm_array_t;

//typedef struct TreeNode TreeNode_t;

static int preFill(TreeNode_t *node, wm_array_t *arr) {
    wm_queue_t *que = malloc(16 * sizeof(wm_queue_t));
    wm_queue_t *que_node = calloc(1, sizeof(wm_queue_t));
    int i = 0 , deep = 1;
    int front = 0, rear = 0;
    //将根节点入队
    (que[rear]).node_ = node;
    (que[rear]).deep_ = deep;
    rear = (rear + 1) % 16;
    int pos = 0;
    int count = 0;
    arr[i].is_null_ = 1;
    i++;
    while(front != rear) {
        //从队列中取出结点
        memcpy(que_node, &(que[front]), sizeof(wm_queue_t));
        memset(&(que[front]), '\0', sizeof(wm_queue_t));
        front = (front + 1) % 16;
        if(que_node->node_ != NULL) {
            //访问取出的结点
            if(que_node->deep_ > deep) {      //如果该结点是下一层结点，则在arr中插入一个空结点
                arr[pos].val_ = count;
                arr[i].is_null_ = 1;
                pos = i;
                i++;
                count = 0;
                deep = que_node->deep_;
            }
            count++;
            arr[i++].val_ = que_node->node_->val;     //访问取出的结点，让val存到arr中。
            //将左子节点入队列
            (que[rear]).node_ = que_node->node_->left;
            (que[rear]).deep_ = que_node->deep_ + 1;
            rear = (rear + 1) % 16;
            //将右子节点入队列
            (que[rear]).node_ = que_node->node_->right;
            (que[rear]).deep_ = que_node->deep_ + 1;
            rear = (rear + 1) % 16;
        }
    }
    free(que);
    arr[pos].val_ = count;
    return i;
}

int** levelOrderBottom(struct TreeNode* root, int** columnSizes, int* returnSize) {
    if(root == NULL) return NULL;
    int tree_size = 0;
    int deep = getTreeDeep(root, 0, &tree_size);
    wm_array_t * arr = calloc(1, (tree_size + deep + 1) * sizeof(wm_array_t));
    if(arr == NULL) return NULL;
    int size = preFill(root, arr);
    int i = 0, j = 0, k = 0;
    int * t = NULL;
    int *col_size = calloc(1, deep * sizeof(int));
    int **rt = calloc(1, deep * sizeof(int *));
    for(i = 0; i < size; i++) {
        if(arr[i].is_null_ == 1) {
            t = calloc(1, arr[i].val_ * sizeof(int));
            k++;
            rt[deep-k] = t;
            col_size[deep-k] = arr[i].val_;
            j = 0;
            continue;
        }
        t[j++] = arr[i].val_;
    }
    free(arr);
    *returnSize = deep;
    *columnSizes = col_size;
    return rt;
}

int main(void) {
    TreeNode_t * root = NULL;
    int tree_size = 0;
    tree_size = string_to_tree(&root, "wangmao.txt");
    if(tree_size <= 0) {
        printf("err_code = %d\n", tree_size);
        return -1;
    }
    int * cs = NULL;
    int rs = 0;
    int ** rt =  levelOrderBottom(root, &cs, &rs);
    int i, j;
    printf("Begin\n");
    for(i = 0; i < rs; i++) {
        for(j = 0; j < cs[i]; j++) {
            printf("rt[%d][%d] = %d, ", i, j, rt[i][j]);
        }
        printf("\n");
    }
    printf("END\n");
}
