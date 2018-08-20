#include <stdlib.h>
typedef struct {
    int size;
    int top;
} MinStack;

/** initialize your data structure here. */
MinStack* minStackCreate(int maxSize) {
    if (maxSize < 0) return NULL;
    MinStack *obj = (MinStack *)calloc(1, sizeof(MinStack) + maxSize * sizeof(int));
    obj->size = maxSize;
    obj->top = -1;
    return obj;
}

void minStackPush(MinStack* obj, int x) {
    if (obj->top >= obj->size - 1) return;
    obj->top++;
    int *p = (int *)(obj + 1) + obj->top;
    *p = x;
}

void minStackPop(MinStack* obj) {
    if (obj->top < 0) return;
    obj->top--;
}

int minStackTop(MinStack* obj) {
    if (obj->top < 0) return 0;
    return *((int *)(obj + 1) + obj->top);
}

int minStackGetMin(MinStack* obj) {
    if (obj->top < 0) return 0;
    int *p = (int *)(obj + 1);
    int i, min = p[0];
    for(i = 1; i <= obj->top; i++) {
        if (min > p[i]) min = p[i];
    }
    return min;
}

void minStackFree(MinStack* obj) {
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * struct MinStack* obj = minStackCreate(maxSize);
 * minStackPush(obj, x);
 * minStackPop(obj);
 * int param_3 = minStackTop(obj);
 * int param_4 = minStackGetMin(obj);
 * minStackFree(obj);
 */
