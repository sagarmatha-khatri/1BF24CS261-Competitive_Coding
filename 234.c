#include <stdbool.h>
#include <stddef.h>

bool isPalindrome(struct ListNode* head) {
    int vals[100000]; // Constraint: max 10^5 nodes
    int size = 0;

    // 1. Copy linked list values to array
    struct ListNode* curr = head;
    while (curr != NULL) {
        vals[size++] = curr->val;
        curr = curr->next;
    }

    // 2. Two-pointer check from outside in
    int left = 0, right = size - 1;
    while (left < right) {
        if (vals[left] != vals[right]) {
            return false;
        }
        left++;
        right--;
    }

    return true;
}