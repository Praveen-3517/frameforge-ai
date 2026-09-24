/*
 * Problem Statement:
 * Given the head of a singly linked list and an integer k, split the linked list into
 * k consecutive linked list parts. The length of each part should be as equal as possible:
 * no two parts should have a size differing by more than one. This may lead to some parts
 * being null. The parts should be in the order of occurrence in the input list, and parts
 * occurring earlier should always have a size greater than or equal to parts occurring later.
 * (LeetCode 725: Split Linked List in Parts)
 * 
 * Example:
 * Input: head = [1,2,3,4,5,6,7,8,9,10], k = 3
 * Output: [[1,2,3,4],[5,6,7],[8,9,10]]
 * 
 * Asked in: Amazon, Google, Microsoft
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

ListNode[] splitListToParts(ListNode* head, int k) {
        ListNode[] parts = new ListNode[k];

        // 1. Calculate total length
        int totalLen = 0;
        ListNode* curr = head;
        while (curr != NULL) {
            totalLen++;
            curr = curr->next;
        }

        // 2. Base size per part and remaining extra elements to distribute to earliest parts
        int baseSize = totalLen / k;
        int extra = totalLen % k;

        curr = head;
        for (int i = 0; i < k; i++) {
            if (curr == NULL) {
                parts[i] = NULL;
                continue;
            }

            parts[i] = curr;
            int currentPartSize = baseSize + (i < extra ? 1 : 0);

            // Traverse to the end of this part
            for (int j = 1; j < currentPartSize; j++) {
                curr = curr->next;
            }

            // Sever the link to start next part
            ListNode* nextPartHead = curr->next;
            curr->next = NULL;
            curr = nextPartHead;
        }

        return parts;
    }

    

    static void printList(ListNode* head) {
        if (head == NULL) {
            printf("[]\n");
            return;
        }
        ListNode* curr = head;
        printf("%s", "[");
        while (curr != NULL) {
            printf("%s", curr->val + (curr->next != NULL ? ", " : ""));
            curr = curr->next;
        }
        printf("]\n");
    }

    int main(void) {
        ListNode* list = buildList(10, (int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        int k = 3;

        printf("--- Splitting List into " + k + " Balanced Parts ---\n");
        ListNode[] parts = splitListToParts(list, k);
        for (int i = 0; i < n; i++) {
            printf("%s", "Part #" + (i + 1) + ": ");
            printList(parts[i]);
        }
        return 0;
}

/*
 * Time Complexity: O(N + k) where N is total nodes in list.
 * Space Complexity: O(k) for output array of heads.
 */
