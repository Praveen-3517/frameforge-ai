/*
 * Problem Statement:
 * You are given the head of a singly linked-list. The list can be represented as:
 * L0 -> L1 -> ... -> Ln - 1 -> Ln
 * Reorder the list to be on the following form:
 * L0 -> Ln -> L1 -> Ln - 1 -> L2 -> Ln - 2 -> ...
 * You may not modify the values in the list's nodes. Only nodes themselves may be changed.
 * (LeetCode 143: Reorder List)
 * 
 * Example:
 * Input: head = [1,2,3,4,5]
 * Output: [1,5,2,4,3]
 * 
 * Asked in: Facebook/Meta, Amazon, Microsoft, ByteDance
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
     * 3-Step In-Place Algorithm:
     * 1. Find midpoint of list using fast and slow pointers.
     * 2. Split into two halves and reverse the second half.
     * 3. Interleave/merge the two halves together node-by-node.
     */
    void reorderList(ListNode* head) {
        if (head == NULL || head->next == NULL) return;

        // Step 1: Find middle
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next != NULL && fast->next->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2: Reverse second half
        ListNode* secondHalf = reverse(slow->next);
        slow->next = NULL; // Break link between halves

        // Step 3: Interleave p1 (first half) and p2 (reversed second half)
        ListNode* p1 = head;
        ListNode* p2 = secondHalf;

        while (p2 != NULL) {
            ListNode* next1 = p1->next;
            ListNode* next2 = p2->next;

            p1->next = p2;
            p2->next = next1;

            p1 = next1;
            p2 = next2;
        }
    }

    static ListNode* reverse(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* curr = head;
        while (curr != NULL) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
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
        ListNode* list1 = buildList(5, (int[]){1, 2, 3, 4, 5});
        printf("%s", "Original list: "); printList(list1);
        reorderList(list1);
        printf("%s", "Reordered list: "); printList(list1);

        ListNode* list2 = buildList(4, (int[]){1, 2, 3, 4});
        printf("%s", "\nOriginal list: "); printList(list2);
        reorderList(list2);
        printf("%s", "Reordered list: "); printList(list2);
        return 0;
}

/*
 * Time Complexity: O(N) - Linear pass through list.
 * Space Complexity: O(1) in-place pointer manipulation.
 */
