/*
 * Problem Statement:
 * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 * Merge all the linked-lists into one sorted linked-list and return it.
 * (LeetCode 23: Merge k Sorted Lists)
 * 
 * Example:
 * Input: lists = [[1,4,5],[1,3,4],[2,6]]
 * Output: [1,1,2,3,4,4,5,6]
 * 
 * Asked in: Amazon, Facebook/Meta, Microsoft, Google, Apple, Bloomberg
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
     * Min-Heap PriorityQueue:
     * - Insert the head of each non-empty linked list into a Min-Heap of capacity k.
     * - In a loop, extract the smallest node from the heap, attach to merged result list.
     * - If the extracted node has a next node, offer next node to the heap.
     * - Repeat until heap is empty.
     */
    ListNode* mergeKLists(ListNode[] lists) {
        if (lists == NULL || n == 0) return NULL;

        PriorityQueue<ListNode> minHeap = new PriorityQueue<>((a, b) -> int.compare(a->val, b->val));

        // Seed heap with head of each list
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

        printf("--- Merging K Sorted Linked Lists ---\n");
        printf("%s", "List 1: "); printList(l1);
        printf("%s", "List 2: "); printList(l2);
        printf("%s", "List 3: "); printList(l3);

        ListNode* merged = mergeKLists(lists);
        printf("%s", "\nMerged Sorted List: ");
        printList(merged);
        return 0;
}

/*
 * Time Complexity: O(N log k) where N is total number of nodes across all lists, k is lists count.
 * Space Complexity: O(k) for the priority queue holding at most k list heads.
 */
