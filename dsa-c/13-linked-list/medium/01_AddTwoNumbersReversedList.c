/*
 * Problem Statement:
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order, and each of their nodes contains a single digit.
 * Add the two numbers and return the sum as a linked list.
 * (LeetCode 2: Add Two Numbers)
 * 
 * Example:
 * Input: l1 = [2,4,3], l2 = [5,6,4] (342 + 465)
 * Output: [7,0,8] (807)
 * 
 * Asked in: Amazon, Microsoft, Apple, Google, Facebook/Meta
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

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = createNode(0);
        ListNode* curr = dummy;
        int carry = 0;

        while (l1 != NULL || l2 != NULL || carry != 0) {
            int sum = carry;
            if (l1 != NULL) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL) {
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10;
            curr->next = createNode(sum % 10);
            curr = curr->next;
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
        ListNode* l1 = buildList(3, (int[]){2, 4, 3}); // 342
        ListNode* l2 = buildList(3, (int[]){5, 6, 4}); // 465

        printf("%s", "List 1: "); printList(l1);
        printf("%s", "List 2: "); printList(l2);

        ListNode* sum = addTwoNumbers(l1, l2);
        printf("%s", "Sum:    "); printList(sum);
        return 0;
}

/*
 * Time Complexity: O(max(N, M)) where N and M are list lengths.
 * Space Complexity: O(max(N, M)) for output list.
 */
