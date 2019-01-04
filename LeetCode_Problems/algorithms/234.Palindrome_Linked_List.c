/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <stdbool.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode_t;

#define MAX_SIZE (1 << 14)
bool isPalindrome(struct ListNode* head) {
    if(NULL == head) return true;
    int *arr = (int*)calloc(MAX_SIZE, sizeof(int));
    int i = 0;
    for(; NULL!= head && i < MAX_SIZE; ++i, head = head->next) {
        arr[i] = head->val;
    }
    if(i == MAX_SIZE) {
        free(arr);
        return false;
    }
    for(int j = 0; j < i/2 ; ++j) {
        if(arr[j] != arr[i-1-j]) {
            free(arr);
            return false;
        }
    }
    free(arr);
    return true;
}
