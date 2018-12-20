#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * 此解法较笨些，思想是在出栈动作时将队列中所有元素重新入一次队列，将队列最后元素出栈
 */

typedef struct {
    int size_;
    int used_;
    int front_;
    int rear_;
    int *top_;
    int **arr_;
} MyStack;

/** Initialize your data structure here. */
MyStack* myStackCreate(int maxSize) {
    MyStack *s = (MyStack *)calloc(1, sizeof(MyStack));
    s->used_ = 0;
    s->front_ = 0;
    s->rear_ = 0;
    s->top_ = 0;
    s->size_ = maxSize + 1;
    s->arr_ = (int **)calloc(1, s->size_ * sizeof(int*));
    return s;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
    if(obj->size_ <= obj->used_ + 1) return;
    int *e = (int *)malloc(sizeof(int));
    *e = x;
    obj->arr_[obj->rear_] = e; obj->rear_ = (obj->rear_ + 1) % obj->size_;
    obj->used_ = obj->used_ + 1;
    obj->top_ = e;
}

void myStackPushNULL(MyStack* obj) {
    if(obj->size_ <= obj->used_) return;
    obj->arr_[obj->rear_] = NULL; obj->rear_ = (obj->rear_ + 1) % obj->size_;
    obj->used_ = obj->used_ + 1;
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
    if(obj->rear_ == obj->front_) return 0;
    myStackPushNULL(obj);
    int *e = NULL;
    e = obj->arr_[obj->front_];
    obj->arr_[obj->front_] = NULL;
    obj->used_ = obj->used_ - 1;
    obj->front_ = (obj->front_ + 1) % obj->size_;
    int val = *e; free(e);
    e = obj->arr_[obj->front_];
    while(NULL != e) {
        myStackPush(obj, val);
        obj->arr_[obj->front_] = NULL;
        obj->used_ = obj->used_ - 1;
        obj->front_ = (obj->front_ + 1) % obj->size_;
        val = *e; free(e);
        e = obj->arr_[obj->front_];
    }
    obj->used_ = obj->used_ - 1;
    obj->front_ = (obj->front_ + 1) % obj->size_;
    return val;
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
    if(obj->rear_ == obj->front_) return 0;
    return *(obj->top_);
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
    if(obj->front_ == obj->rear_) return true;
    else return false;
}

void myStackFree(MyStack* obj) {
    int * e = NULL;
    while(obj->front_ != obj->rear_) {
        e = obj->arr_[obj->front_];
        obj->arr_[obj->front_] = NULL;
        obj->front_ = (obj->front_ + 1) % obj->size_;
        free(e);
    }
    free(obj->arr_);
    free(obj);
}

int main(void) {
    int maxSize = 10;
    MyStack *obj = myStackCreate(maxSize);
    myStackPush(obj, 3);
    myStackPush(obj, 2);
    myStackPush(obj, 1);
    int param_1 = myStackPop(obj);
    int param_2 = myStackPop(obj);
    int param_3 = myStackTop(obj);
    printf("param_1 = %d\n", param_1);
    printf("param_2 = %d\n", param_2);
    printf("param_3 = %d\n", param_3);
    if(true == myStackEmpty(obj)) {
        puts("Is empty");
    } else {
        puts("Not empty");
    }
 	myStackFree(obj);
    return 0;
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * struct MyStack* obj = myStackCreate(maxSize);
 * myStackPush(obj, x);
 * int param_2 = myStackPop(obj);
 * int param_3 = myStackTop(obj);
 * bool param_4 = myStackEmpty(obj);
 * myStackFree(obj);
 */
