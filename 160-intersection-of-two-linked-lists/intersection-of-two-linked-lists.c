/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if (!headA || !headB) return NULL;
    
    struct ListNode *pa = headA;
    struct ListNode *pb = headB;
    
    // Traverse both lists; switch head when reaching end
    while (pa != pb) {
        pa = (pa != NULL) ? pa->next : headB;
        pb = (pb != NULL) ? pb->next : headA;
    }
    
    // Either intersection node or NULL
    return pa;
}
