/*
 * Problem Statement:
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 * Implement the MinStack class:
 * - void push(int val): pushes the element val onto the stack.
 * - void pop(): removes the element on the top of the stack.
 * - int top(): gets the top element of the stack.
 * - int getMin(): retrieves the minimum element in the stack.
 * You must implement a solution with O(1) time complexity for each function.
 * (LeetCode 155: Min Stack)
 * 
 * Asked in: Amazon, Bloomberg, Microsoft, Google, Facebook/Meta
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

static class MinStack {
        // Main stack stores values
        static const Deque<int> stack = new ArrayDeque<>();
        // Auxiliary stack tracks running minimums
        static const Deque<int> minStack = new ArrayDeque<>();

        MinStack() {}

        void push(int val) {
            stack.push(val);
            if (minStack.isEmpty() || val <= minStack.peek()) {
                minStack.push(val);
            }
        }

        void pop() {
            if (stack.isEmpty()) return;
            int removed = stack.pop();
            if (removed == minStack.peek()) {
                minStack.pop();
            }
        }

        int top() {
            return stack.peek();
        }

        int getMin() {
            return minStack.peek();
        }
    }

    int main(void) {
        MinStack minStack = new MinStack();

        printf("--- Min Stack Operations ---\n");
        minStack.push(-2);
        minStack.push(0);
        minStack.push(-3);

        printf("getMin(): %d\n", minStack.getMin()); // Returns -3
        minStack.pop();
        printf("top():    %d\n", minStack.top());    // Returns 0
        printf("getMin(): %d\n", minStack.getMin()); // Returns -2
        return 0;
}

/*
 * Time Complexity: O(1) strictly for push, pop, top, and getMin.
 * Space Complexity: O(N) auxiliary space for minStack.
 */
