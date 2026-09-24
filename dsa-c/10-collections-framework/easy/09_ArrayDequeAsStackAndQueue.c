/*
 * Problem Statement:
 * Demonstrate `java.util.ArrayDeque` as the preferred implementation for both Stacks and Queues:
 * - Why legacy `java.util.Stack` should be avoided:
 *   - Stack extends `Vector` (synchronized method overhead, breaks encapsulation by allowing index access).
 * - Using ArrayDeque as a LIFO Stack: `push()`, `pop()`, `peek()`.
 * - Using ArrayDeque as a FIFO Queue: `offer()`, `poll()`, `peek()`.
 * 
 * Asked in: Amazon, Google, Microsoft, Bloomberg
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
        // 1. ArrayDeque as a High-Performance LIFO Stack
        printf("--- 1. ArrayDeque as Stack (LIFO) ---\n");
        Deque<const char*> stack = new ArrayDeque<>();
        stack.push("Page 1");
        stack.push("Page 2");
        stack.push("Page 3");

        printf("Top of stack (peek): %d\n", stack.peek());
        while (!stack.isEmpty()) {
            printf("Popped from stack: %d\n", stack.pop());
        }

        // 2. ArrayDeque as a FIFO Queue
        printf("\n--- 2. ArrayDeque as Queue (FIFO) ---\n");
        Deque<int> queue = new ArrayDeque<>();
        queue.offer(100);
        queue.offer(200);
        queue.offer(300);

        printf("Front of queue (peek): %d\n", queue.peek());
        while (!queue.isEmpty()) {
            printf("Served from queue: %d\n", queue.poll());
        }
        return 0;
}

/*
 * Time Complexity: Amortized O(1) for push, pop, offer, poll, and peek operations.
 * Space Complexity: O(N) circular array buffer memory.
 */
