#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int* data_;
    int top_;
    int size_;
} mStack_t;

mStack_t * mStack_init(int maxSize) {
    if(maxSize <= 0) return NULL;
    mStack_t *s = calloc(1, sizeof(mStack_t));
    s->top_ = -1;
    s->size_ = maxSize;
    s->data_ = (int*)calloc(s->size_, sizeof(int));
    return s;
}

bool mStack_push(mStack_t *s, int d) {
    if(s->top_ + 1 == s->size_) return false;
    s->top_++;
    s->data_[s->top_] = d;
    return true;
}

bool mStack_is_empty(mStack_t *s) {
    if(s->top_ < 0) return true;
    return false;
}

bool mStack_pop(mStack_t *s, int *out) {
    if(s->top_ < 0) return false;
    *out = s->data_[s->top_];
    s->top_--;
    return true;
}

bool mStack_get(mStack_t *s, int *out) {
    if(s->top_ < 0) return false;
    *out =  s->data_[s->top_];
    return true;
}

void mStack_free(mStack_t *s) {
    if(NULL != s) {
        if(NULL != s->data_) free(s->data_);
        free(s);
    }
}

typedef struct {
    mStack_t *a_;
    mStack_t *b_;
} MyQueue;

/** Initialize your data structure here. */
MyQueue* myQueueCreate(int maxSize) {
    MyQueue *myQue = (MyQueue*)calloc(1, sizeof(MyQueue));
    myQue->a_ = mStack_init(maxSize);
    myQue->b_ = mStack_init(maxSize);
    return myQue;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
    mStack_push(obj->a_, x);
}

int myQueuePeek(MyQueue* obj);
/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
    myQueuePeek(obj);
    int a = 0;
    mStack_pop(obj->b_, &a);
    return a;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
    int a = 0;
    if(mStack_is_empty(obj->b_)) {
        while(! mStack_is_empty(obj->a_)) {
            mStack_pop(obj->a_, &a);
            mStack_push(obj->b_, a);
        }
    }
    mStack_get(obj->b_, &a);
    return a;
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
    return mStack_is_empty(obj->a_) && mStack_is_empty(obj->b_);
}

void myQueueFree(MyQueue* obj) {
    if(NULL != obj) {
        mStack_free(obj->a_);
        mStack_free(obj->b_);
        free(obj);
    }
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * struct MyQueue* obj = myQueueCreate(maxSize);
 * myQueuePush(obj, x);
 * int param_2 = myQueuePop(obj);
 * int param_3 = myQueuePeek(obj);
 * bool param_4 = myQueueEmpty(obj);
 * myQueueFree(obj);
 */
