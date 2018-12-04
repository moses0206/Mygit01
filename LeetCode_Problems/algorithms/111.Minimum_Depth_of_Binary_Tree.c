typedef struct wm_queue {
    struct TreeNode *node_;
    unsigned long depth_;
} wm_queue_t;

/**
  * 下面是非递归解法，按层遍历
  */

int minDepth(struct TreeNode* root) {
#define QUEUE_SIZE (1 << 12)
    if(root == NULL) return 0;
    struct TreeNode * visit_node = NULL;
    unsigned long visit_depth = 0;
    unsigned long cur_depth = 0;
    wm_queue_t *queue = calloc(1, QUEUE_SIZE * sizeof(wm_queue_t));
    int front = 0, rear = 0;
    queue[rear].node_ = root;
    queue[rear].depth_ = 1;
    rear = (rear + 1) % QUEUE_SIZE;
    while(front != rear) {
        visit_node = queue[front].node_;
        visit_depth = queue[front].depth_;
        front = (front + 1) % QUEUE_SIZE;
        if(visit_depth > cur_depth) cur_depth = visit_depth;
        if(visit_node->left == NULL && visit_node->right == NULL)
            goto END;
        if(visit_node->left != NULL) {
            queue[rear].node_ = visit_node->left;
            queue[rear].depth_ = visit_depth + 1;
            rear = (rear + 1) % QUEUE_SIZE;
        }
        if(visit_node->right != NULL) {
            queue[rear].node_ = visit_node->right;
            queue[rear].depth_ = visit_depth + 1;
            rear = (rear + 1) % QUEUE_SIZE;
        }
    }
END:
    free(queue);
    return (int)cur_depth;
}


/**
  * 下面是递归解法
  */
static int max_int(int a, int b) {
    if(a > b) return a;
    else return b;
}
static int min_int(int a, int b) {
    if(a < b) return a;
    else return b;
}
int minDepth(struct TreeNode* root) {
    if(root == NULL) return 0;
    int l = minDepth(root->left);
    int r = minDepth(root->right);
    return 1 + ( (l && r) ? min_int(l, r) : max_int(l, r)); 
    //如果左右子节点都非空，则计算这两个深度小的那个，如果有一个不是，那么就取大的那个值。左右子节点都为空的情况等同于有一个不是空的情况。
}
