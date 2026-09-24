/*
 * Problem Statement:
 * There is a singly-linked list and you are given only the node to be deleted node.
 * You will not be given access to the first node of the list.
 * All values of the linked list are unique, and it is guaranteed that the given node
 * is not the last node in the linked list.
 * (LeetCode 237: Delete Node in a Linked List)
 * 
 * Example:
 * Input: head = [4,5,1,9], node = 5
 * Output: [4,1,9]
 * 
 * Asked in: Amazon, Apple, Microsoft, Adobe
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
     * Value Overwrite / Identity Swap:
     * Since we do not have access to the previous node:
     * 1. Copy the value of the next node into the current node (`node->val = node->next->val`).
     * 2. Bypass the next node (`node->next = node->next->next`).
     * Effectively, the next node is deleted while the target node adopts its identity!
     */
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        node->next = node->next->next;
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
        ListNode* n1 = createNode(4);
        ListNode* n2 = createNode(5);
        ListNode* n3 = createNode(1);
        ListNode* n4 = createNode(9);

        n1->next = n2;
        n2->next = n3;
        n3->next = n4;

        printf("%s", "Original list: ");
        printList(n1);

        printf("Deleting node with value 5 directly...\n");
        deleteNode(n2);

        printf("%s", "Updated list:  ");
        printList(n1);
        return 0;
}

/*
 * Time Complexity: O(1) constant time value assignment and pointer change.
 * Space Complexity: O(1) auxiliary space.
 */
