#include <stdlib.h>
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;
    struct ListNode *n1 = l1, *n2 = l2, *out = NULL;
    if(l1->val < l2->val) {out = l1; n1 = l1->next;}
    else {out = l2; n2 = l2->next;}
    struct ListNode *p = out;
    while( n1 && n2) {
        if(n1->val < n2->val) {
            p->next = n1;
            n1 = n1->next;
        }else {
            p->next = n2;
            n2 = n2->next;
        }
        p = p->next;
    }
    if(n1 != NULL) p->next = n1;
    else p->next = n2;
    return out;
}
