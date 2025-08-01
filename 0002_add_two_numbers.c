#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode* next;
};

// Solution 1 - Dummy Head Approach - O(n)
struct ListNode* addTwoNumbers_dummy_head(struct ListNode* l1, struct ListNode* l2) {
    // A dummy head node 'dummyHead' is defined, which always points to the head of the linked list.
    struct ListNode* dummyHead = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode*   current = dummyHead;
    
    int carry = 0;
    
    while (l1 != NULL || l2 != NULL || carry != 0) {
        int sum = carry;
        if (l1 != NULL) {
            sum += l1 -> val;
            l1 = l1 -> next;
        }
        if (l2 != NULL) {
            sum += l2 -> val;
            l2 = l2 -> next;
        }

        carry = sum / 10;
        
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        
        newNode -> val  = sum % 10;         // Why we need 'current':
        newNode -> next = NULL;             // If we don't use 'current', we cannot keep track of the end of the linked list.
        current -> next = newNode;          // Every time we add a node, we would have to traverse from the head to find the end, which would increase the time complexity to O(n^2).
        current = current -> next;          // Using 'current' ensures that insertion operations remain O(1) in time complexity.
    }
    
    struct ListNode* result = dummyHead -> next;
    free(dummyHead);
    
    return result;
}

// Solution 2 - Double Pointer Construction - O(n) ~ faster than Solution 1
struct ListNode* addTwoNumbers_double_pointer(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode*     head = NULL;
    struct ListNode** current = &head;
    int carry = 0;
    
    while (l1 != NULL || l2 != NULL || carry != 0) {
        int sum = carry;
        
        if(l1 != NULL) {
            sum += l1 -> val;
            l1 = l1 -> next;
        }
        
        if (l2 != NULL) {
            sum += l2 -> val
            l2 = l2 -> next;
        }
        
        carry = sum / 10;
        
        *current = (struct ListNode*)malloc(sizeof(struct ListNode));
        (*current) -> val  = sum % 10;
        (*current) -> next = NULL;
        
        current = &((*current) -> next);
    }
    
    return head;
}
