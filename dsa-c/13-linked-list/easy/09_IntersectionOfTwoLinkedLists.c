/*
 * Problem Statement:
 * Given the heads of two singly linked-lists headA and headB, return the node at which
 * the two lists intersect. If the two linked lists have no intersection at all, return null.
 * Note that the linked lists must retain their original structure after the function returns.
 * Could you write a solution that runs in O(m + n) time and use only O(1) memory?
 * (LeetCode 160: Intersection of Two Linked Lists)
 * 
 * Asked in: Amazon, Microsoft, Bloomberg, Apple, Facebook/Meta
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
     * Two Pointers Wrapping Around:
     * Pointer pA traverses listA then wraps to headB.
     * Pointer pB traverses listB then wraps to headA.
     * Since len(A) + len(B) == len(B) + len(A), both pointers traverse the exact same total length.
     * They will either collide at the intersection node or both hit NULL simultaneously!
     */
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        if (headA == NULL || headB == NULL) return NULL;

        ListNode* pA = headA;
        ListNode* pB = headB;

        while (pA != pB) {
            pA = (pA == NULL) ? headB : pA->next;
            pB = (pB == NULL) ? headA : pB->next;
        }

        return pA; // Intersection node or NULL
    }

    int main(void) {
        // Shared tail: 8 -> 4 -> 5
        ListNode* common = createNode(8);
        common->next = createNode(4);
        common->next->next = createNode(5);

        // List A: 4 -> 1 -> common
        ListNode* headA = createNode(4);
        headA->next = createNode(1);
        headA->next->next = common;

        // List B: 5 -> 6 -> 1 -> common
        ListNode* headB = createNode(5);
        headB->next = createNode(6);
        headB->next->next = createNode(1);
        headB->next->next->next = common;

        ListNode* intersection = getIntersectionNode(headA, headB);
        printf("Intersection node value: " + (intersection != NULL ? intersection->val : "NULL") + " (Expected: 8)\n");
        return 0;
}

/*
 * Time Complexity: O(M + N) where M and N are lengths of lists A and B.
 * Space Complexity: O(1) auxiliary pointers.
 */
