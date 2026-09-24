/*
 * Problem Statement:
 * Given the head of a singly linked list, return true if it is a palindrome or false otherwise.
 * Could you do it in O(n) time and O(1) space?
 * (LeetCode 234: Palindrome Linked List)
 * 
 * Example 1:
 * Input: head = [1,2,2,1]
 * Output: true
 * 
 * Example 2:
 * Input: head = [1,2]
 * Output: false
 * 
 * Asked in: Amazon, Facebook/Meta, Microsoft, Apple
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
     * O(N) Time and O(1) Space In-Place Strategy:
     * 1. Find midpoint of the list using fast and slow pointers.
     * 2. Reverse the second half of the list.
     * 3. Compare the first half and the reversed second half node by node.
     * 4. (Optional) Restore the original list by reversing the second half back.
     */
    bool isPalindrome(ListNode* head) {
        if (head == NULL || head->next == NULL) return true;

        // 1. Find middle node (slow)
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next != NULL && fast->next->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 2. Reverse second half
        ListNode* secondHalfHead = reverse(slow->next);

        // 3. Compare values
        ListNode* p1 = head;
        ListNode* p2 = secondHalfHead;
        bool isPal = true;

        while (p2 != NULL) {
            if (p1->val != p2->val) {
                isPal = false;
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }

        // 4. Restore list structure
        slow->next = reverse(secondHalfHead);

        return isPal;
    }

    static ListNode* reverse(ListNode* head) {
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

    

    int main(void) {
        ListNode* l1 = buildList(4, (int[]){1, 2, 2, 1});
        printf("[1, 2, 2, 1] is palindrome? %d\n", isPalindrome(l1));

        ListNode* l2 = buildList(5, (int[]){1, 2, 3, 2, 1});
        printf("[1, 2, 3, 2, 1] is palindrome? %d\n", isPalindrome(l2));

        ListNode* l3 = buildList(3, (int[]){1, 2, 3});
        printf("[1, 2, 3] is palindrome? %d\n", isPalindrome(l3));
        return 0;
}

/*
 * Time Complexity: O(N) - Half-list traversal + reversal + comparison.
 * Space Complexity: O(1) auxiliary space.
 */
