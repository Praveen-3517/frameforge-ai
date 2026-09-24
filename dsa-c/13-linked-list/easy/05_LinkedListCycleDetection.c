/*
 * Problem Statement:
 * Given head, the head of a linked list, determine if the linked list has a cycle in it.
 * There is a cycle in a linked list if there is some node in the list that can be reached
 * again by continuously following the next pointer.
 * Return true if there is a cycle in the linked list. Otherwise, return false.
 * (LeetCode 141: Linked List Cycle)
 * 
 * Asked in: Amazon, Microsoft, Bloomberg, Apple, Spotify
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
     * Floyd's Cycle-Finding Algorithm (Tortoise and Hare):
     * If there is no cycle, fast pointer will reach NULL.
     * If there is a cycle, the fast pointer will eventually lap and collide with
     * the slow pointer within the loop.
     */
    bool hasCycle(ListNode* head) {
        if (head == NULL || head->next == NULL) return false;

        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                return true;
            }
        }

        return false;
    }

    int main(void) {
        // List with cycle: 3 -> 2 -> 0 -> -4 -> (points back to 2)
        ListNode* n1 = createNode(3);
        ListNode* n2 = createNode(2);
        ListNode* n3 = createNode(0);
        ListNode* n4 = createNode(-4);

        n1->next = n2;
        n2->next = n3;
        n3->next = n4;
        n4->next = n2; // Creates cycle

        printf("Cyclic list has cycle? %d\n", hasCycle(n1));

        // Acyclic list: 1 -> 2 -> NULL
        ListNode* a1 = createNode(1);
        ListNode* a2 = createNode(2);
        a1->next = a2;

        printf("Acyclic list has cycle? %d\n", hasCycle(a1));
        return 0;
}

/*
 * Time Complexity: O(N) where N is the number of nodes.
 * Space Complexity: O(1) auxiliary space (no hash sets needed).
 */
