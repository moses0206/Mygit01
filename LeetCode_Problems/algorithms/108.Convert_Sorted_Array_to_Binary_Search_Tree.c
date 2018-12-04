struct TreeNode* recursion_A2BST(int *nums, int l, int r) {
    if(l > r) return NULL;
    int m = (l + r) / 2;
    struct TreeNode *node = calloc(1, sizeof(struct TreeNode));
    node->val = nums[m];
    node->left = recursion_A2BST(nums, l, m-1);
    node->right = recursion_A2BST(nums, m+1, r);
    return node;
}

struct TreeNode* sortedArrayToBST(int *nums, int numsSize) {
    if(numsSize < 1) return NULL;
    int middle = numsSize / 2;
    struct TreeNode *root = calloc(1, sizeof(struct TreeNode));
    root->val = nums[middle];
    root->left = recursion_A2BST(nums, 0, middle - 1);
    root->right = recursion_A2BST(nums, middle+1, numsSize-1);
    return root;
}
