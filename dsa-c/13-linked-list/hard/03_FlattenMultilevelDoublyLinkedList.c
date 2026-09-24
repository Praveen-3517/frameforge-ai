/*
 * Problem Statement:
 * You are given a doubly linked list, which contains nodes that have a next pointer,
 * a previous pointer, and an additional child pointer. This child pointer may or may not
 * point to a separate doubly linked list, also containing these special nodes.
 * Flatten the list so that all the nodes appear in a single-level, doubly linked list.
 * (LeetCode 430: Flatten a Multilevel Doubly Linked List)
 * 
 * Asked in: Bloomberg, Amazon, Microsoft, Apple
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

/**
     * Approach:
     * Iterative Pointer Splicing:
     * While iterating:
     * 1. If curr has no child, proceed to curr.next.
     * 2. If curr has a child:
     *    - Find the tail of the child branch.
     *    - Connect child tail's next to curr.next (if curr.next != NULL).
     *    - Connect curr.next to curr.child.
     *    - Set curr.child.prev to curr.
     *    - Clear curr.child = NULL.
     */
    Node flatten(Node head) {
        if (head == NULL) return NULL;

        Node curr = head;
        while (curr != NULL) {
            if (curr.child != NULL) {
                Node next = curr.next;

                // Find tail of child list
                Node childTail = curr.child;
                while (childTail.next != NULL) {
                    childTail = childTail.next;
                }

                // Splice child list in between curr and next
                curr.next = curr.child;
                curr.child.prev = curr;

                if (next != NULL) {
                    childTail.next = next;
                    next.prev = childTail;
                }

                curr.child = NULL; // Clear child pointer
            }

            curr = curr.next;
        }

        return head;
    }

    int main(void) {
        Node n1 = new Node(1);
        Node n2 = new Node(2);
        Node n3 = new Node(3);
        n1.next = n2; n2.prev = n1;
        n2.next = n3; n3.prev = n2;

        Node c1 = new Node(7);
        Node c2 = new Node(8);
        c1.next = c2; c2.prev = c1;

        // Node 2 has child c1
        n2.child = c1;

        Node flattened = flatten(n1);
        printf("--- Flattened Doubly Linked List ---\n");
        Node curr = flattened;
        while (curr != NULL) {
            printf("%s", curr.val + (curr.next != NULL ? " <-> " : ""));
            curr = curr.next;
        }
        printf("\n");
        return 0;
}

/*
 * Time Complexity: O(N) where N is total nodes across all levels.
 * Space Complexity: O(1) in-place pointer stitching.
 */
