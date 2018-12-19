#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int val_;
    int idx_;
    struct Node *next_;
};

struct Set {
    int setSize_;
    struct Node **table_;
};

int newSet(struct Set **out, int setSize) {
    if(setSize < 1) return -1;
    struct Set * s = calloc(1, sizeof(struct Set));
    s->setSize_ = setSize;
    s->table_ = malloc(sizeof(struct Node*) * setSize);
    memset(s->table_, 0, sizeof(struct Node*) * setSize);
    *out = s;
    return 0;
}

bool addValue(struct Set *s, int val, int i, int k) {
    int idx = val > 0 ? val : -val;
    idx = (idx % s->setSize_);
    struct Node * ptr = s->table_[idx];
    while(NULL != ptr) {
        if(ptr->val_ == val) {
            if(i - ptr->idx_ <= k) {
                return false;
            }
        }
        ptr = ptr->next_;
    }
    struct Node * n = calloc(1, sizeof(struct Node));
    n->val_ = val;
    n->idx_ = i;
    n->next_ = s->table_[idx];
    s->table_[idx] = n;
    return true;
}

void releaseSet(struct Set *s) {
    if(NULL == s) return;
    for(int i = 0; i < s->setSize_; ++i) {
        struct Node *ptr = s->table_[i], *tmp = NULL;
        while(NULL != ptr) {
            tmp = ptr;
            ptr = ptr->next_;
            free(tmp);
        }
    }
    free(s->table_);
    free(s);
    return;
}

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    if(numsSize < 2) return false;
    struct Set * s = NULL;
    if(0 != newSet(&s, numsSize)) return false;
    for(int i = 0; i < numsSize; ++i) {
        if(!addValue(s, nums[i], i, k)) {
            releaseSet(s);
            return true;
        }
    }
    releaseSet(s);
    return false;
}
