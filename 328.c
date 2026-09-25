struct ListNode* oddEvenList(struct ListNode* head) {
    if (!head || !head->next) return head;

    struct ListNode *odd = head, *even = head->next, *evenHead = even;

    while (even && even->next) {
        odd->next = even->next;
        odd = odd->next;
        
        even->next = odd->next;
        even = even->next;
    }

    odd->next = evenHead; // Connect odds to evens
    return head;
}