/*
 * Problem Statement:
 * Merge k sorted linked lists and return it as one sorted list using Pairwise Divide and Conquer:
 * - Instead of a Min-Heap, merge pairs of lists iteratively:
 *   lists[0] with lists[1], lists[2] with lists[3], and so on.
 * - In each round, the number of lists is halved (k -> k/2 -> k/4 -> ... -> 1).
 * (LeetCode 23: Merge k Sorted Lists via Divide and Conquer)
 * 
 * Asked in: Google, Facebook/Meta, Amazon, Microsoft
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

ListNode* mergeKLists(ListNode[] lists) {
        if (lists == NULL || n == 0) return NULL;
        return mergeRange(lists, 0, n - 1);
    }

    static ListNode* mergeRange(ListNode[] lists, int left, int right) {
        if (left == right) return lists[left];
        int mid = left + (right - left) / 2;

        ListNode* l1 = mergeRange(lists, left, mid);
        ListNode* l2 = mergeRange(lists, mid + 1, right);

        return mergeTwo(l1, l2);
    }

    static ListNode* mergeTwo(ListNode* l1, ListNode* l2) {
        ListNode* dummy = createNode(0);
        ListNode* tail = dummy;

        while (l1 != NULL && l2 != NULL) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        if (l1 != NULL) tail->next = l1;
        if (l2 != NULL) tail->next = l2;

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
        ListNode* l1 = buildList(3, (int[]){1, 4, 5});
        ListNode* l2 = buildList(3, (int[]){1, 3, 4});
        ListNode* l3 = buildList(2, (int[]){2, 6});

        ListNode[] lists = {l1, l2, l3};
        ListNode* merged = mergeKLists(lists);

        printf("--- Divide and Conquer Merge of K Sorted Lists ---\n");
        printf("%s", "Merged Result: ");
        printList(merged);
        return 0;
}

/*
 * Time Complexity: O(N log k) where N is total nodes and k is number of lists.
 * Space Complexity: O(log k) recursion tree depth.
 */
