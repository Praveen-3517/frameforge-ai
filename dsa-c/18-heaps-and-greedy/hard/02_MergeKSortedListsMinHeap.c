/**
 * Problem: Merge k Sorted Lists (LeetCode 23)
 * Asked in: Facebook, Amazon, Google, Microsoft, Apple
 * 
 * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 * Merge all the linked-lists into one sorted linked-list and return it.
 * 
 * Approach:
 * Min-Heap of Size K:
 * 1. Insert the head of each non-empty linked list into a Min-Heap.
 * 2. While heap is not empty:
 *    - Extract node with smallest value (`curr = heap.poll()`).
 *    - Append `curr` to the merged result list.
 *    - If `curr.next != null`, push `curr.next` into the heap.
 * 
 * Time Complexity: O(N log K) where N is total nodes, K is number of lists.
 * Space Complexity: O(K) for Min-Heap.
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

        PriorityQueue<ListNode> minHeap = new PriorityQueue<>(Comparator.comparingInt(a -> a->val));

        for (ListNode* node : lists) {
            if (node != NULL) {
                minHeap.offer(node);
            }
        }

        ListNode* dummy = createNode(0);
        ListNode* tail = dummy;

        while (!minHeap.isEmpty()) {
            ListNode* smallest = minHeap.poll();
            tail->next = smallest;
            tail = tail->next;

            if (smallest->next != NULL) {
                minHeap.offer(smallest->next);
            }
        }

        return dummy->next;
    }

    int main(void) {
        // List 1: 1 -> 4 -> 5
        ListNode* l1 = createNode(1);
        l1->next = createNode(4);
        l1->next->next = createNode(5);

        // List 2: 1 -> 3 -> 4
        ListNode* l2 = createNode(1);
        l2->next = createNode(3);
        l2->next->next = createNode(4);

        // List 3: 2 -> 6
        ListNode* l3 = createNode(2);
        l3->next = createNode(6);

        ListNode* merged = mergeKLists(new ListNode[]{l1, l2, l3});

        printf("%s", "Merged List: ");
        while (merged != NULL) {
            printf("%s", merged->val + (merged->next != NULL ? " -> " : ""));
            merged = merged->next;
        }
        printf("\n");
        // Expected: 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
