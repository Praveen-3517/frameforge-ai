/*
 * Problem Statement:
 * A linked list of length n is given such that each node contains an additional random pointer,
 * which could point to any node in the list, or null.
 * Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes.
 * None of the pointers in the new list should point to nodes in the original list.
 * Return the head of the copied linked list.
 * Can you solve it in O(1) auxiliary space?
 * (LeetCode 138: Copy List with Random Pointer)
 * 
 * Asked in: Facebook/Meta, Amazon, Microsoft, Bloomberg
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
     * 3-Pass O(1) Auxiliary Space Interleaving Strategy:
     * Pass 1: Create a clone of each node and interleave it directly next to original:
     *         A -> A' -> B -> B' -> C -> C'
     * Pass 2: Assign random pointers for the copied nodes:
     *         curr.next.random = curr.random.next (if curr.random != NULL)
     * Pass 3: Detangle original list and cloned list.
     */
    Node copyRandomList(Node head) {
        if (head == NULL) return NULL;

        // Pass 1: Interleave cloned nodes
        Node curr = head;
        while (curr != NULL) {
            Node copy = new Node(curr.val);
            copy.next = curr.next;
            curr.next = copy;
            curr = copy.next;
        }

        // Pass 2: Set random pointers
        curr = head;
        while (curr != NULL) {
            if (curr.random != NULL) {
                curr.next.random = curr.random.next;
            }
            curr = curr.next.next;
        }

        // Pass 3: Separate original and cloned lists
        curr = head;
        Node copyHead = head.next;
        Node copyCurr = copyHead;

        while (curr != NULL) {
            curr.next = curr.next.next;
            curr = curr.next;

            if (copyCurr.next != NULL) {
                copyCurr.next = copyCurr.next.next;
                copyCurr = copyCurr.next;
            }
        }

        return copyHead;
    }

    int main(void) {
        Node n1 = new Node(7);
        Node n2 = new Node(13);
        Node n3 = new Node(11);

        n1.next = n2;
        n2.next = n3;

        n1.random = NULL;
        n2.random = n1;
        n3.random = n2;

        Node clone = copyRandomList(n1);
        printf("--- Copy List with Random Pointer ---\n");
        printf("Original Head val: %d, Clone Head val: %d\n", n1.val, clone.val);
        printf("Are heads distinct objects? %d\n", (n1 != clone));
        printf("Clone node 2 random val: " + clone.next.random.val + " (Expected: 7)\n");
        return 0;
}

/*
 * Time Complexity: O(N) three linear passes.
 * Space Complexity: O(1) auxiliary space (excluding the output list).
 */
