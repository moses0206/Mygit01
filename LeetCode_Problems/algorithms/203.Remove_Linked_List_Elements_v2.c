struct ListNode {
    int val;
    struct ListNode *next;
};

#define NULL '\0'
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode **p = &head;

    while (*p != NULL) {
        if ((*p)->val == val) {
            *p = (*p)->next;
        } else {
            p = &((*p)->next);
        }
    }
    return head;
}

