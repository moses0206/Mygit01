/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *p = head;
    struct ListNode *pre = NULL;
    struct ListNode *tmp = NULL;
    while(p != NULL) {
        tmp = p->next;
        p->next = pre;
        pre = p;
        p = tmp;
    }
    return pre;
}
