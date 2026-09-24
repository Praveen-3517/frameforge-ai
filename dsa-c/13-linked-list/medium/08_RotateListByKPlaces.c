/*
 * Problem Statement:
 * Given the head of a linked list, rotate the list to the right by k places.
 * (LeetCode 61: Rotate List)
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [4,5,1,2,3]
 * 
 * Example 2:
 * Input: head = [0,1,2], k = 4
 * Output: [2,0,1]
 * 
 * Asked in: Microsoft, Amazon, Google, Bloomberg
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
     * Ring / Cycle formation:
     * 1. Count length of list and connect tail to head (forming a circular ring).
     * 2. Effective rotation: k = k % length.
     * 3. New tail is at index (length - k - 1).
     * 4. New head is newTail->next; break circular link: newTail->next = NULL.
     */
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL || head->next == NULL || k == 0) return head;

        // 1. Calculate length and find tail
        int length = 1;
        ListNode* tail = head;
        while (tail->next != NULL) {
            tail = tail->next;
            length++;
        }

        // 2. Modulo k
        k = k % length;
        if (k == 0) return head;

        // 3. Connect tail to head
        tail->next = head;

        // 4. Find new tail
        int stepsToNewTail = length - k;
        ListNode* newTail = head;
        for (int i = 1; i < stepsToNewTail; i++) {
            newTail = newTail->next;
        }

        ListNode* newHead = newTail->next;
        newTail->next = NULL; // Break loop

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

        ListNode* rotated = rotateRight(list1, 2);
        printf("%s", "Rotated by 2:  "); printList(rotated);

        ListNode* list2 = buildList(3, (int[]){0, 1, 2});
        ListNode* rot2 = rotateRight(list2, 4);
        printf("%s", "Rotated by 4:  "); printList(rot2);
        return 0;
}

/*
 * Time Complexity: O(N) where N is the length of the linked list.
 * Space Complexity: O(1) in-place pointer adjustments.
 */
