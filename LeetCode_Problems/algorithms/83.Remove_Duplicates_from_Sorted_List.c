/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
// 此题是给定已排序的链表，不是未排序的，一开始没想出来怎么解是因为以为是未排序的
struct ListNode* deleteDuplicates(struct ListNode* head) {
    if(head == NULL) return NULL;
    struct ListNode * p = head, *tmp = NULL;
    while(p->next) {
        if(p->val == p->next->val) {
            tmp = p->next;
            p->next = tmp->next;
            free(tmp);
        }
        else p = p->next;
    }
    return head;
}
