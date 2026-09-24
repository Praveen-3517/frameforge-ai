/*
 * Problem Statement:
 * Given the head of a linked list and a value x, partition it such that all nodes
 * less than x come before nodes greater than or equal to x.
 * You should preserve the original relative order of the nodes in each of the two partitions.
 * (LeetCode 86: Partition List)
 * 
 * Example:
 * Input: head = [1,4,3,2,5,2], x = 3
 * Output: [1,2,2,4,3,5]
 * 
 * Asked in: Microsoft, Adobe, Amazon
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
     * Dual Dummy Sentinel Lists:
     * 1. Create two lists: `lessList` (for values < x) and `greaterList` (for values >= x).
     * 2. Iterate through original list, distributing nodes based on value.
     * 3. Join tail of `lessList` to head of `greaterList`.
     * 4. Set tail of `greaterList` to NULL.
     */
    ListNode* partition(ListNode* head, int x) {
        ListNode* lessDummy = createNode(0);
        ListNode* greaterDummy = createNode(0);

        ListNode* less = lessDummy;
        ListNode* greater = greaterDummy;

        ListNode* curr = head;
        while (curr != NULL) {
            if (curr->val < x) {
                less->next = curr;
                less = less->next;
            } else {
                greater->next = curr;
                greater = greater->next;
            }
            curr = curr->next;
        }

        greater->next = NULL; // Terminate greater list
        less->next = greaterDummy->next; // Stitch lists together

        return lessDummy->next;
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
        ListNode* list = buildList(6, (int[]){1, 4, 3, 2, 5, 2});
        printf("%s", "Original list: "); printList(list);

        ListNode* partitioned = partition(list, 3);
        printf("%s", "Partitioned around 3: "); printList(partitioned);
        return 0;
}

/*
 * Time Complexity: O(N) single pass through the list.
 * Space Complexity: O(1) in-place pointer stitching.
 */
