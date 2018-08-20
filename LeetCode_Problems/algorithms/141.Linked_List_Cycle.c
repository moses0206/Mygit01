/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool hasCycle(struct ListNode *head) {
    if (head == NULL) return false;
    bool flag = false;
    struct ListNode *p = head, *q = head;
    while((NULL != q->next) && (NULL != q->next->next)) {
        p = p->next;
        q = q->next->next;
        if (p == q) {
            flag = true;
            break;
        }
    }
    return flag;
}
