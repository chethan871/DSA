/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *prev = NULL, *curr = head, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

struct ListNode* doubleIt(struct ListNode* head) {
    head = reverseList(head);

    struct ListNode* curr = head;
    int carry = 0;

    while (curr) {
        int sum = curr->val * 2 + carry;
        curr->val = sum % 10;
        carry = sum / 10;

        if (!curr->next && carry) {
            curr->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            curr->next->val = carry;
            curr->next->next = NULL;
            carry = 0;
            break;
        }
        curr = curr->next;
    }

    return reverseList(head);
}
