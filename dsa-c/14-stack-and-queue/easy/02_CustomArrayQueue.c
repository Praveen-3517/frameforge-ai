/*
 * Problem Statement:
 * Implement a custom Queue data structure from scratch using a Circular Array:
 * - enqueue(int x): Insert at tail; throw Overflow if full.
 * - dequeue(): Remove from front; throw Underflow if empty.
 * - front(): Inspect front element.
 * - isEmpty(), isFull(), size().
 * 
 * Asked in: Amazon, Oracle, Wipro, TCS
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

static class CircularArrayQueue {
        static const int* arr;
        static int front;
        static int rear;
        static int count;
        static const int capacity;

        CircularArrayQueue(int capacity) {
            this.capacity = capacity;
            this.arr = (int*)malloc((capacity) * sizeof(int));
            this.front = 0;
            this.rear = 0;
            this.count = 0;
        }

        void enqueue(int x) {
            if (isFull()) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            arr[rear] = x;
            rear = (rear + 1) % capacity;
            count++;
        }

        int dequeue() {
            if (isEmpty()) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            int val = arr[front];
            front = (front + 1) % capacity;
            count--;
            return val;
        }

        int front() {
            if (isEmpty()) fprintf(stderr, "Exception: invalid argument
"); return 0;
            return arr[front];
        }

        bool isEmpty() { return count == 0; }
        bool isFull() { return count == capacity; }
        int size() { return count; }
    }

    int main(void) {
        CircularArrayQueue q = new CircularArrayQueue(3);

        printf("--- Custom Circular Array Queue Testing ---\n");
        q.enqueue(100);
        q.enqueue(200);
        q.enqueue(300);

        printf("Front element: %d\n", q.front());
        printf("Dequeued: %d\n", q.dequeue()); // frees space at index 0

        q.enqueue(400); // wraps around to index 0!
        printf("Enqueued 400 with wrap around. Front: %d\n", q.front());

        while (!q.isEmpty()) {
            printf("Dequeued: %d\n", q.dequeue());
        }
        return 0;
}

/*
 * Time Complexity: O(1) for enqueue, dequeue, front, size.
 * Space Complexity: O(capacity) array storage.
 */
