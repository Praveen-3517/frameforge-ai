/*
 * Problem Statement:
 * Given the head of a linked list, return the list after sorting it in ascending order.
 * Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?
 * (LeetCode 148: Sort List)
 * 
 * Example:
 * Input: head = [4,2,1,3]
 * Output: [1,2,3,4]
 * 
 * Asked in: Facebook/Meta, Google, Amazon, Microsoft
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

static ListNode* createNode(int val) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) exit(1);
    node->val = val;
    node->next = NULL;
    return node;
}

static void freeList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        free(tmp);
    }
}

static ListNode* buildList(int count, int vals[]) {
    if (count <= 0) return NULL;
    ListNode* head = createNode(vals[0]);
    ListNode* curr = head;
    for (int i = 1; i < count; i++) {
        curr->next = createNode(vals[i]);
        curr = curr->next;
    }
    return head;
}

/**
     * Approach:
     * Top-Down Divide and Conquer Merge Sort:
     * 1. Base case: if head == NULL || head->next == NULL, return head.
     * 2. Split list into two halves using fast and slow pointers.
     * 3. Recursively sort each half.
     * 4. Merge the two sorted halves using standard merge subroutine.
     */
    ListNode* sortList(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;

        // Split list into two halves
        ListNode* prev = NULL;
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != NULL && fast->next != NULL) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        prev->next = NULL; // Break first half from second half

        // Recursively sort halves
        ListNode* l1 = sortList(head);
        ListNode* l2 = sortList(slow);

        // Merge sorted halves
        return merge(l1, l2);
    }

    static ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode* dummy = createNode(0);
        ListNode* tail = dummy;

        while (l1 != NULL && l2 != NULL) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        if (l1 != NULL) tail->next = l1;
        if (l2 != NULL) tail->next = l2;

        return dummy->next;
    }

    

    static void printList(ListNode* head) {
        ListNode* curr = head;
        while (curr != NULL) {
            printf("%s", curr->val + (curr->next != NULL ? " -> " : ""));
            curr = curr->next;
        }
        printf("\n");
    }

    int main(void) {
        ListNode* list = buildList(4, (int[]){4, 2, 1, 3});
        printf("%s", "Original list: "); printList(list);

        ListNode* sorted = sortList(list);
        printf("%s", "Sorted list:   "); printList(sorted);
        return 0;
}

/*
 * Time Complexity: O(N log N) divide and conquer MergeSort.
 * Space Complexity: O(log N) recursion call stack depth.
 */
