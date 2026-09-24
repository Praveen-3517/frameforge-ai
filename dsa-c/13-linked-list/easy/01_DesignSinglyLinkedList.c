/*
 * Problem Statement:
 * Design your implementation of the linked list (LeetCode 707: Design Linked List):
 * - MyLinkedList(): Initializes the MyLinkedList object.
 * - int get(int index): Get the value of the index-th node in the linked list. If invalid, return -1.
 * - void addAtHead(int val): Add a node of value val before the first element.
 * - void addAtTail(int val): Append a node of value val as the last element.
 * - void addAtIndex(int index, int val): Add a node of value val before the index-th node.
 * - void deleteAtIndex(int index): Delete the index-th node in the linked list.
 * 
 * Asked in: Amazon, Apple, Microsoft, Bloomberg
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

int main(void) {
        MyLinkedList list = new MyLinkedList();

        printf("--- Testing Custom Linked List ---\n");
        list.addAtHead(1);
        list.addAtTail(3);
        list.addAtIndex(1, 2); // Linked list becomes 1 -> 2 -> 3
        list.printList();

        printf("get(1): %d\n", list.get(1)); // returns 2

        list.deleteAtIndex(1);  // Now 1 -> 3
        list.printList();
        printf("get(1) after delete: %d\n", list.get(1)); // returns 3
        return 0;
}

/*
 * Time Complexity: addAtHead: O(1), get/addAtIndex/deleteAtIndex: O(N).
 * Space Complexity: O(N) for stored nodes.
 */
