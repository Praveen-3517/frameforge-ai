/*
 * Problem Statement:
 * Given the head of a linked list, return the node where the cycle begins.
 * If there is no cycle, return null. Do not modify the linked list.
 * Can you solve it using O(1) memory?
 * (LeetCode 142: Linked List Cycle II)
 * 
 * Asked in: Amazon, Microsoft, Goldman Sachs, Google
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
     * Floyd's Cycle Finding Phase 1 and Phase 2:
     * Phase 1: Determine collision point inside loop using fast and slow pointers.
     * Phase 2: Reset slow pointer to head. Keep fast at intersection.
     * Advance both one step at a time. The point where they meet is the exact cycle entry node!
     */
    ListNode* detectCycle(ListNode* head) {
        if (head == NULL || head->next == NULL) return NULL;

        ListNode* slow = head;
        ListNode* fast = head;
        bool hasCycle = false;

        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                hasCycle = true;
                break;
            }
        }

        if (!hasCycle) return NULL;

        // Phase 2: Reset slow to head
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }

        return slow; // Cycle start node
    }

    int main(void) {
        ListNode* n1 = createNode(3);
        ListNode* n2 = createNode(2);
        ListNode* n3 = createNode(0);
        ListNode* n4 = createNode(-4);

        n1->next = n2;
        n2->next = n3;
        n3->next = n4;
        n4->next = n2; // Loop starts at node 2

        ListNode* cycleStart = detectCycle(n1);
        printf("Cycle starts at node with value: " + (cycleStart != NULL ? cycleStart->val : "NULL") + " (Expected: 2)\n");
        return 0;
}

/*
 * Time Complexity: O(N) linear time to detect and find cycle start.
 * Space Complexity: O(1) auxiliary space.
 */
