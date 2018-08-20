#include <stdlib.h>
typedef struct {
    int size;
    int top;
    int min_top;
} MinStack;

#define GET_S1(x) ((int*)((MinStack*)x + 1))
#define GET_S2(x) ((int*)GET_S1(x) + (x->size))

/** initialize your data structure here. */
MinStack* minStackCreate(int maxSize) {
    if (maxSize < 0) return NULL;
    MinStack *obj = (MinStack *)calloc(1, sizeof(MinStack) + maxSize * sizeof(int) * 2);
    obj->size = maxSize;
    obj->top = -1;
    obj->min_top = -1;
    return obj;
}

void minStackPush(MinStack* obj, int x) {
    if (!obj || obj->top >= obj->size - 1) return;
    obj->top++;
    GET_S1(obj)[obj->top] = x;
    if (obj->min_top < 0 || x <= minStackGetMin(obj)) {
        obj->min_top++;
        GET_S2(obj)[obj->min_top] = x;
    }
}

void minStackPop(MinStack* obj) {
    if (!obj || obj->top < 0) return;
    if (minStackTop(obj) == minStackGetMin(obj))
        obj->min_top--;
    obj->top--;
}

int minStackTop(MinStack* obj) {
    if (!obj || obj->top < 0) return 0;
    return GET_S1(obj)[obj->top];
}

int minStackGetMin(MinStack* obj) {
    if (!obj || obj->top < 0) return 0;
    return GET_S2(obj)[obj->min_top];
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
