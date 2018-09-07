struct ListNode {
    int val;
    struct ListNode *next;
};

#define NULL '\0'
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode *p, *pre;
    while (NULL != head && head->val == val) {
        head = head->next;
    }
    if (NULL == head) return NULL;
    pre = head;
    p = head->next;
    while (NULL != p) {
        if (p->val == val) {
            pre->next = p->next;
        } else {
            pre = p;
        }
        p = p->next;
    }
    return head;
}
