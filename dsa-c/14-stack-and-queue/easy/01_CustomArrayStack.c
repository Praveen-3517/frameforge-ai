/*
 * Problem Statement:
 * Implement a custom Stack data structure from scratch using a fixed-size array:
 * - push(int x): Push element onto stack; throw Overflow error if full.
 * - pop(): Remove and return top element; throw Underflow error if empty.
 * - peek(): Return top element without removing.
 * - isEmpty(), isFull(), size().
 * 
 * Asked in: Infosys, TCS, Wipro, Cognizant
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

static class ArrayStack {
        static const int* arr;
        static int top;
        static const int capacity;

        ArrayStack(int capacity) {
            this.capacity = capacity;
            this.arr = (int*)malloc((capacity) * sizeof(int));
            this.top = -1;
        }

        void push(int x) {
            if (isFull()) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            arr[++top] = x;
        }

        int pop() {
            if (isEmpty()) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            return arr[top--];
        }

        int peek() {
            if (isEmpty()) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            return arr[top];
        }

        bool isEmpty() { return top == -1; }
        bool isFull() { return top == capacity - 1; }
        int size() { return top + 1; }
    }

    int main(void) {
        ArrayStack stack = new ArrayStack(3);

        printf("--- Custom Array Stack Testing ---\n");
        stack.push(10);
        stack.push(20);
        stack.push(30);

        printf("Top element (peek): %d\n", stack.peek());
        printf("Stack size: %d\n", stack.size());
        printf("Is full? %d\n", stack.isFull());

        while (!stack.isEmpty()) {
            printf("Popped: %d\n", stack.pop());
        }

        printf("Is empty now? %d\n", stack.isEmpty());
        return 0;
}

/*
 * Time Complexity: O(1) for push, pop, peek, isEmpty, isFull.
 * Space Complexity: O(capacity) array storage.
 */
