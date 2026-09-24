/*
 * Problem Statement:
 * Given the head of a singly linked list, return the middle node of the linked list.
 * If there are two middle nodes, return the second middle node.
 * (LeetCode 876: Middle of the Linked List)
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5]
 * Output: [3,4,5] (node with value 3)
 * 
 * Example 2:
 * Input: head = [1,2,3,4,5,6]
 * Output: [4,5,6] (second middle node)
 * 
 * Asked in: Amazon, Adobe, Google, Microsoft
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
     * Tortoise and Hare (Fast & Slow Pointers):
     * Initialize both slow and fast at head.
     * While fast != NULL and fast->next != NULL:
     *   slow = slow->next;
     *   fast = fast->next->next;
     * When fast reaches the end, slow is exactly at the middle node!
     */
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    

    int main(void) {
        ListNode* l1 = buildList(5, (int[]){1, 2, 3, 4, 5});
        printf("Odd length list [1,2,3,4,5] middle value: " + middleNode(l1).val + " (Expected: 3)\n");

        ListNode* l2 = buildList(6, (int[]){1, 2, 3, 4, 5, 6});
        printf("Even length list [1,2,3,4,5,6] middle value: " + middleNode(l2).val + " (Expected: 4)\n");
        return 0;
}

/*
 * Time Complexity: O(N) single pass through the list.
 * Space Complexity: O(1) auxiliary pointers.
 */
