/*
 * Problem Statement:
 * Given the head of a linked list, reverse the nodes of the list k at a time,
 * and return the modified list.
 * k is a positive integer and is less than or equal to the length of the linked list.
 * If the number of nodes is not a multiple of k then left-out nodes, in the end,
 * should remain as it is.
 * You may not alter the values in the list's nodes, only nodes themselves may be changed.
 * (LeetCode 25: Reverse Nodes in k-Group)
 * 
 * Example:
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [2,1,4,3,5]
 * 
 * Asked in: Microsoft, Amazon, Facebook/Meta, Apple, Google
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

ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == NULL || k <= 1) return head;

        ListNode* dummy = createNode(0);
        dummy->next = head;
        ListNode* prevGroupEnd = dummy;

        while (true) {
            // Check if there are at least k nodes remaining
            ListNode* kth = getKthNode(prevGroupEnd, k);
            if (kth == NULL) break;

            ListNode* nextGroupStart = kth->next;

            // Reverse current k-group
            ListNode* prev = nextGroupStart;
            ListNode* curr = prevGroupEnd->next;
            while (curr != nextGroupStart) {
                ListNode* temp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = temp;
            }

            // Connect previous group end to the newly reversed group head
            ListNode* temp = prevGroupEnd->next;
            prevGroupEnd->next = kth;
            prevGroupEnd = temp;
        }

        return dummy->next;
    }

    static ListNode* getKthNode(ListNode* curr, int k) {
        while (curr != NULL && k > 0) {
            curr = curr->next;
            k--;
        }
        return curr;
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

        ListNode* res1 = reverseKGroup(list1, 2);
        printf("%s", "k = 2 group:   "); printList(res1);

        ListNode* list2 = buildList(5, (int[]){1, 2, 3, 4, 5});
        ListNode* res2 = reverseKGroup(list2, 3);
        printf("%s", "k = 3 group:   "); printList(res2);
        return 0;
}

/*
 * Time Complexity: O(N) where N is number of nodes. Each node visited at most twice.
 * Space Complexity: O(1) in-place pointer manipulation.
 */
