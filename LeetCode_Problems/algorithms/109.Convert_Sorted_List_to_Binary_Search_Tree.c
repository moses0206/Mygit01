BSTreeNode_t * convertList(int *arr, int left, int right){
    if(left > right) return NULL;
    BSTreeNode_t *curr = calloc(1, sizeof(BSTreeNode_t));
    int pos = (left + right) / 2;
    curr->val_ = arr[pos];
    curr->left_ = convertList(arr, left, pos - 1);
    curr->right_ = convertList(arr, pos + 1, right);
    return curr;
}

BSTreeNode_t * sortedListToBST(ListNode_t *head) {
    if(head == NULL) return NULL;
    int i = 0, arr_size = 1 << 14;      //注意，Leetcode上尽量不要用realloc，所以尽量一次性开足够的空间。
    int * arr  = calloc((unsigned int)arr_size, sizeof(int));
    ListNode_t * p = NULL;
    for(i = 0, p = head; p != NULL; i++, p = p->next_) {
        if(i == arr_size) {
            arr_size = arr_size << 1;
            arr = realloc(arr, arr_size);   //此处，在LeetCode上会有问题，在验证LeetCode的testcase时，不要走到这里。
        }
        arr[i] = p->val_;
    }
    BSTreeNode_t * tree = convertList(arr, 0, i-1);
    free(arr);
    return tree;
}

//////////////////////////////////////////////////////
//  下面是将二元查找树转变成排序的双向链表的算法
//////////////////////////////////////////////////////
BSTreeNode_t * tree_to_linked(BSTreeNode_t *this, BSTreeNode_t ** rt_max) {
    if(this == NULL) {
        *rt_max = NULL;
        return NULL;
    }
    BSTreeNode_t *l_rt_max = NULL, *r_rt_max = NULL, *l_rt_min = NULL, *r_rt_min = NULL;
    l_rt_min = tree_to_linked(this->left_, &l_rt_max);
    r_rt_min = tree_to_linked(this->right_, &r_rt_max);

    this->left_ = l_rt_max;
    this->right_ = r_rt_min;
    if(l_rt_max != NULL) l_rt_max->right_ = this;
    if(r_rt_min != NULL) r_rt_min->left_ = this;

    if(r_rt_max != NULL) *rt_max = r_rt_max;
    else *rt_max = this;

    if(l_rt_min != NULL) return l_rt_min;
    else return this;
}

