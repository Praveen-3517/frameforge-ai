/*
 * Problem Statement:
 * Given the head of a linked list and an integer val, remove all the nodes of the
 * linked list that has Node.val == val, and return the new head.
 * (LeetCode 203: Remove Linked List Elements)
 * 
 * Example:
 * Input: head = [1,2,6,3,4,5,6], val = 6
 * Output: [1,2,3,4,5]
 * 
 * Asked in: Apple, Amazon, Microsoft
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
     * Sentinel Dummy Node:
     * Create dummy node pointing to head to seamlessly handle deletions of head nodes.
     */
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummy = createNode(0);
        dummy->next = head;
        ListNode* curr = dummy;

        while (curr->next != NULL) {
            if (curr->next->val == val) {
                curr->next = curr->next->next; // Delete node
            } else {
                curr = curr->next;
            }
        }

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
        ListNode* list = buildList(7, (int[]){1, 2, 6, 3, 4, 5, 6});
        printf("%s", "Original list: "); printList(list);

        ListNode* filtered = removeElements(list, 6);
        printf("%s", "After removing 6: "); printList(filtered);

        ListNode* list2 = buildList(4, (int[]){7, 7, 7, 7});
        ListNode* filtered2 = removeElements(list2, 7);
        printf("%s", "All 7s removed: "); printList(filtered2);
        return 0;
}

/*
 * Time Complexity: O(N) single pass through the list.
 * Space Complexity: O(1) in-place deletion.
 */
