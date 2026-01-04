/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* mergeInBetween(struct ListNode* list1, int a, int b, struct ListNode* list2) {
    struct ListNode* prevA = list1;
    struct ListNode* afterB = list1;
    
    // Find node before position a (0-indexed)
    for (int i = 0; i < a - 1; i++)
        prevA = prevA->next;
    
    // Find node at position b
    for (int i = 0; i < b; i++)
        afterB = afterB->next;
    
    // Connect prevA to head of list2
    prevA->next = list2;
    
    // Move to the end of list2
    struct ListNode* tail2 = list2;
    while (tail2->next != NULL)
        tail2 = tail2->next;
    
    // Connect end of list2 to afterB->next
    tail2->next = afterB->next;
    
    return list1;
}
