/*
 * Problem Statement:
 * Implement a last-in-first-out (LIFO) stack using only queues.
 * The implemented stack should support all functions of a normal stack (push, top, pop, and empty).
 * Implement it using a single Queue!
 * (LeetCode 225: Implement Stack using Queues)
 * 
 * Asked in: Google, Amazon, Bloomberg
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

static class MyStack {
        static const Queue<int> queue = new ArrayDeque<>();

        void push(int x) {
            queue.offer(x);
            int size = queue.size();
            // Rotate previous elements behind the newly pushed element
            for (int i = 0; i < size - 1; i++) {
                queue.offer(queue.poll());
            }
        }

        int pop() {
            return queue.poll();
        }

        int top() {
            return queue.peek();
        }

        bool empty() {
            return queue.isEmpty();
        }
    }

    int main(void) {
        MyStack stack = new MyStack();

        printf("--- Stack via Single Queue ---\n");
        stack.push(1);
        stack.push(2);
        printf("top():   %d\n", stack.top());   // returns 2
        printf("pop():   %d\n", stack.pop());   // returns 2
        printf("empty(): %d\n", stack.empty()); // returns false
        return 0;
}

/*
 * Time Complexity: push: O(N) where N is current queue size; pop, top, empty: O(1).
 * Space Complexity: O(N) storage for single queue.
 */
