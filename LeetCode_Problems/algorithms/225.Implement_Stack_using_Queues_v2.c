#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int size_;
    int used_;
    int front_;
    int rear_;
    int *arr_;
} MyStack;
    
/** Initialize your data structure here. */
MyStack* myStackCreate(int maxSize) {
    MyStack *s = (MyStack *)calloc(1, sizeof(MyStack));
    s->size_ = maxSize;
    s->used_ = 0;
    s->front_ = s->rear_ = 0;
    s->arr_ = (int *)malloc(maxSize * sizeof(int));
    return s;
}

/** Push element x onto stack. */
void myStackPush(MyStack* s, int x) {
    if(s->size_ <= s->used_) return;
    s->arr_[s->rear_] = x;
    s->rear_ = (s->rear_ + 1) % s->size_;
    s->used_ = s->used_ + 1;
    for(int i = 0; i < s->used_ - 1; ++i) {
        int tmp = s->arr_[s->front_];
        s->front_ = (s->front_ + 1) % s->size_;
        s->used_ = s->used_ - 1;
        s->arr_[s->rear_] = tmp;
        s->rear_ = (s->rear_ + 1) % s->size_;
        s->used_ = s->used_ + 1;
    }
}   

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* s) {
    int tmp = s->arr_[s->front_];
    s->front_ = (s->front_ + 1) % s->size_;
    s->used_ = s->used_ - 1;
    return tmp;
}

/** Get the top element. */
int myStackTop(MyStack* s) {
    return s->arr_[s->front_];
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* s) {
    if(s->front_ == s->rear_) return true;
    return false;
}

void myStackFree(MyStack* s) {
    free(s->arr_);
    free(s);
}
