/*
 * Problem Statement:
 * Given the head of a linked list, remove the n-th node from the end of the list
 * and return its head. Solve this in one pass!
 * (LeetCode 19: Remove Nth Node From End of List)
 * 
 * Example:
 * Input: head = [1,2,3,4,5], n = 2
 * Output: [1,2,3,5]
 * 
 * Asked in: Facebook/Meta, Amazon, Apple, Microsoft
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
     * One-Pass Two Pointers with Sentinel Dummy Node:
     * 1. Advance `fast` pointer n + 1 steps ahead of `slow`.
     * 2. Move both `slow` and `fast` together until `fast` reaches NULL.
     * 3. Now `slow` is pointing right BEFORE the target node to delete!
     * 4. Perform deletion: `slow->next = slow->next->next`.
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = createNode(0);
        dummy->next = head;
        ListNode* slow = dummy;
        ListNode* fast = dummy;

        // Move fast n + 1 steps ahead
        for (int i = 0; i <= n; i++) {
            fast = fast->next;
        }

        // Move both until fast hits end
        while (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }

        // Delete the nth node from end
        slow->next = slow->next->next;

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
        ListNode* list1 = buildList(5, (int[]){1, 2, 3, 4, 5});
        printf("%s", "Original list: "); printList(list1);

        ListNode* res1 = removeNthFromEnd(list1, 2);
        printf("%s", "After removing 2nd from end: "); printList(res1);

        ListNode* list2 = buildList(1, (int[]){1});
        ListNode* res2 = removeNthFromEnd(list2, 1);
        printf("%s", "After removing 1st from end of single-node list: "); printList(res2);
        return 0;
}

/*
 * Time Complexity: O(N) single pass through the list.
 * Space Complexity: O(1) auxiliary pointers.
 */
