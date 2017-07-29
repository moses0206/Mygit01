#include <stdio.h>
#include <stdlib.h>

 struct ListNode {
     int val;
     struct ListNode *next;
 };
 

struct ListNode* sumVal(struct ListNode* l1, struct ListNode* l2, int c) {
    if(l1 == NULL && l2 == NULL && c == 0) return NULL;

    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* nn = NULL;
    struct ListNode* mm = NULL;
    int v1 = 0, v2 = 0;
    if(l1 != NULL) {
        nn = l1->next;
        v1 = l1->val;
    }
    if(l2 != NULL) {
        mm = l2->next;
        v2 = l2->val;
    }
    node->val = (v1 + v2 + c)%10;
    node->next = sumVal(nn, mm, (v1 + v2 + c)/10);
    return node;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* rt;
    rt = sumVal(l1, l2, 0);
    return rt;
}

void main(void) {

}

