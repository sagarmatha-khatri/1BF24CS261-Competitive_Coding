/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* swapNodes(struct ListNode* head, int k) {
    struct ListNode *first = head;
    struct ListNode *second = head;
    struct ListNode *fast = head;

    // Step 1: Advance fast pointer to the k-th node
    for (int i = 1; i < k; i++) {
        fast = fast->next;
    }
    
    // Save reference to the k-th node from start
    first = fast;

    // Step 2: Move fast to the end to locate the k-th node from the end
    while (fast->next != NULL) {
        fast = fast->next;
        second = second->next;
    }

    // Step 3: Swap values between the two nodes
    int temp = first->val;
    first->val = second->val;
    second->val = temp;

    return head;
}