/*
 * Problem Statement:
 * Given a linked list, swap every two adjacent nodes and return its head.
 * You must solve the problem without modifying the values in the list's nodes
 * (i.e., only nodes themselves may be changed.)
 * (LeetCode 24: Swap Nodes in Pairs)
 * 
 * Example:
 * Input: head = [1,2,3,4]
 * Output: [2,1,4,3]
 * 
 * Asked in: Amazon, Microsoft, Facebook/Meta, Apple
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

ListNode* swapPairs(ListNode* head) {
        ListNode* dummy = createNode(0);
        dummy->next = head;
        ListNode* prev = dummy;

        while (prev->next != NULL && prev->next->next != NULL) {
            ListNode* first = prev->next;
            ListNode* second = prev->next->next;

            // Perform pointer swaps
            first->next = second->next;
            second->next = first;
            prev->next = second;

            // Move prev pointer forward two nodes
            prev = first;
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
        ListNode* list1 = buildList(4, (int[]){1, 2, 3, 4});
        printf("%s", "Original list: "); printList(list1);

        ListNode* swapped = swapPairs(list1);
        printf("%s", "Swapped pairs: "); printList(swapped);

        ListNode* list2 = buildList(5, (int[]){1, 2, 3, 4, 5});
        printf("%s", "\nOdd list:      "); printList(list2);
        printf("%s", "Swapped pairs: "); printList(swapPairs(list2));
        return 0;
}

/*
 * Time Complexity: O(N) single pass through the list.
 * Space Complexity: O(1) auxiliary pointers.
 */
