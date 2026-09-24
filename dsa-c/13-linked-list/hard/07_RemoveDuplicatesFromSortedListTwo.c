/*
 * Problem Statement:
 * Given the head of a sorted linked list, delete all nodes that have duplicate numbers,
 * leaving only distinct numbers from the original list. Return the linked list sorted as well.
 * (LeetCode 82: Remove Duplicates from Sorted List II)
 * 
 * Example:
 * Input: head = [1,2,3,3,4,4,5]
 * Output: [1,2,5]
 * 
 * Example 2:
 * Input: head = [1,1,1,2,3]
 * Output: [2,3]
 * 
 * Asked in: Microsoft, Amazon, Facebook/Meta
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

ListNode* deleteDuplicates(ListNode* head) {
        ListNode* dummy = createNode(0);
        dummy->next = head;
        ListNode* prev = dummy;

        while (head != NULL) {
            // If current node is the start of duplicates
            if (head->next != NULL && head->val == head->next->val) {
                // Skip all nodes with the same value
                while (head->next != NULL && head->val == head->next->val) {
                    head = head->next;
                }
                // Discard duplicate sequence
                prev->next = head->next;
            } else {
                prev = prev->next;
            }
            head = head->next;
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
        ListNode* list1 = buildList(7, (int[]){1, 2, 3, 3, 4, 4, 5});
        printf("%s", "Original list: "); printList(list1);

        ListNode* res1 = deleteDuplicates(list1);
        printf("%s", "Distinct only: "); printList(res1);

        ListNode* list2 = buildList(5, (int[]){1, 1, 1, 2, 3});
        printf("%s", "\nOriginal list: "); printList(list2);
        ListNode* res2 = deleteDuplicates(list2);
        printf("%s", "Distinct only: "); printList(res2);
        return 0;
}

/*
 * Time Complexity: O(N) single pass through the list.
 * Space Complexity: O(1) in-place pointer manipulation.
 */
