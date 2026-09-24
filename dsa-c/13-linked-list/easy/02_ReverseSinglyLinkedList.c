/*
 * Problem Statement:
 * Given the head of a singly linked list, reverse the list, and return the reversed list.
 * Implement both:
 * 1. Iterative Approach (three pointers: prev, curr, next).
 * 2. Recursive Approach.
 * (LeetCode 206: Reverse Linked List)
 * 
 * Example:
 * Input: head = [1,2,3,4,5]
 * Output: [5,4,3,2,1]
 * 
 * Asked in: Amazon, Apple, Google, Microsoft, Facebook/Meta
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

// 1. Iterative Reversal
    ListNode* reverseListIterative(ListNode* head) {
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

    // 2. Recursive Reversal
    ListNode* reverseListRecursive(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;

        ListNode* newHead = reverseListRecursive(head->next);
        head->next->next = head;
        head->next = NULL;
        return newHead;
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

        ListNode* rev1 = reverseListIterative(list1);
        printf("%s", "Reversed (Iterative): "); printList(rev1);

        ListNode* rev2 = reverseListRecursive(rev1);
        printf("%s", "Reversed back (Recursive): "); printList(rev2);
        return 0;
}

/*
 * Time Complexity: O(N) linear pass over all N nodes.
 * Space Complexity: Iterative: O(1) in-place; Recursive: O(N) call stack.
 */
