/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode *tempA = headA;
    struct ListNode *tempB = headB;
    int lenA = 0, lenB = 0, r;
    while(NULL != tempA) {
        lenA++;
        tempA = tempA->next;
    }
    while(NULL != tempB) {
        lenB++;
        tempB = tempB->next;
    }
    r = lenA > lenB ? lenA - lenB : lenB - lenA;
    if (lenA > lenB) {
        while(r--) headA = headA->next;
    } else {
        while(r--) headB = headB->next;
    }
    while(headA != headB) {
        headA = headA->next;
        headB = headB->next;
    }
    return headA;
}
