/*
 * Problem Statement:
 * Demonstrate `java.util.LinkedList` operating as both a Queue (FIFO) and a Deque (Double-Ended Queue):
 * - Adding and removing from both ends in O(1) time: addFirst, addLast, removeFirst, removeLast.
 * - Peeking elements without removal: peekFirst, peekLast.
 * - Converting between Queue and Deque interfaces.
 * 
 * Asked in: Amazon, Oracle, Goldman Sachs, Cognizant
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
        // 1. LinkedList as a Standard FIFO Queue
        printf("--- 1. LinkedList as FIFO Queue ---\n");
        Queue<const char*> printQueue = new LinkedList<>();
        printQueue.offer("Doc_Invoice.pdf");
        printQueue.offer("Doc_Resume.docx");
        printQueue.offer("Doc_Presentation.pptx");

        printf("Next document in queue (peek): %d\n", printQueue.peek());
        while (!printQueue.isEmpty()) {
            printf("Printing: %d\n", printQueue.poll());
        }

        // 2. LinkedList as a double-Ended Queue (Deque)
        printf("\n--- 2. LinkedList as Deque (Front & Back Operations) ---\n");
        Deque<int> deque = new LinkedList<>();
        deque.addFirst(10); // [10]
        deque.addLast(20);  // [10, 20]
        deque.addFirst(5);  // [5, 10, 20]
        deque.addLast(25);  // [5, 10, 20, 25]

        printf("Deque state: %d\n", deque);
        printf("First element: %d, Last element: %d\n", deque.peekFirst(), deque.peekLast());

        printf("Removed from front: %d\n", deque.removeFirst()); // 5
        printf("Removed from back:  %d\n", deque.removeLast());  // 25
        printf("Remaining deque:    %d\n", deque);
        return 0;
}

/*
 * Time Complexity: O(1) for all addFirst, addLast, removeFirst, removeLast, peek operations.
 * Space Complexity: O(N) where N is number of node elements.
 */
