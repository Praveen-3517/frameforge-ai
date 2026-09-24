/*
 * Problem Statement:
 * Implement a first in first out (FIFO) queue using only two stacks.
 * The implemented queue should support all the functions of a normal queue
 * (push, peek, pop, and empty).
 * Can you implement each operation such that each operation is amortized O(1) time complexity?
 * (LeetCode 232: Implement Queue using Stacks)
 * 
 * Asked in: Amazon, Microsoft, Bloomberg, Apple
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

static class MyQueue {
        static const Deque<int> inStack = new ArrayDeque<>();
        static const Deque<int> outStack = new ArrayDeque<>();

        void push(int x) {
            inStack.push(x);
        }

        int pop() {
            shiftStacks();
            return outStack.pop();
        }

        int peek() {
            shiftStacks();
            return outStack.peek();
        }

        bool empty() {
            return inStack.isEmpty() && outStack.isEmpty();
        }

        static void shiftStacks() {
            if (outStack.isEmpty()) {
                while (!inStack.isEmpty()) {
                    outStack.push(inStack.pop());
                }
            }
        }
    }

    int main(void) {
        MyQueue queue = new MyQueue();

        printf("--- Queue via Two Stacks ---\n");
        queue.push(1);
        queue.push(2);
        printf("peek():  %d\n", queue.peek()); // returns 1
        printf("pop():   %d\n", queue.pop());  // returns 1
        printf("empty(): %d\n", queue.empty()); // returns false
        return 0;
}

/*
 * Time Complexity: push: O(1); pop & peek: Amortized O(1) (each element pushed and popped from outStack once).
 * Space Complexity: O(N) storage across the two stacks.
 */
