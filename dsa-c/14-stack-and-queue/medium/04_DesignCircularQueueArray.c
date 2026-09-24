/*
 * Problem Statement:
 * Design your implementation of the circular queue (LeetCode 622: Design Circular Queue):
 * - MyCircularQueue(k): Initializes the object with the size of the queue to be k.
 * - int Front(): Gets the front item from the queue. If empty, return -1.
 * - int Rear(): Gets the last item from the queue. If empty, return -1.
 * - boolean enQueue(int value): Inserts an element into the circular queue. Return true if successful.
 * - boolean deQueue(): Deletes an element from the circular queue. Return true if successful.
 * - boolean isEmpty(), boolean isFull().
 * 
 * Asked in: Facebook/Meta, Amazon, Microsoft, Goldman Sachs
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

static class MyCircularQueue {
        static const int* data;
        static int head;
        static int tail;
        static int count;
        static const int capacity;

        MyCircularQueue(int k) {
            this.capacity = k;
            this.data = (int*)malloc((k) * sizeof(int));
            this.head = 0;
            this.tail = 0;
            this.count = 0;
        }

        bool enQueue(int value) {
            if (isFull()) return false;
            data[tail] = value;
            tail = (tail + 1) % capacity;
            count++;
            return true;
        }

        bool deQueue() {
            if (isEmpty()) return false;
            head = (head + 1) % capacity;
            count--;
            return true;
        }

        int Front() {
            return isEmpty() ? -1 : data[head];
        }

        int Rear() {
            if (isEmpty()) return -1;
            // tail points to next write position, so last element is at (tail - 1 + capacity) % capacity
            int lastIdx = (tail - 1 + capacity) % capacity;
            return data[lastIdx];
        }

        bool isEmpty() {
            return count == 0;
        }

        bool isFull() {
            return count == capacity;
        }
    }

    int main(void) {
        MyCircularQueue cq = new MyCircularQueue(3);

        printf("--- Testing Circular Queue (k = 3) ---\n");
        printf("enQueue(1): %d\n", cq.enQueue(1)); // true
        printf("enQueue(2): %d\n", cq.enQueue(2)); // true
        printf("enQueue(3): %d\n", cq.enQueue(3)); // true
        printf("enQueue(4): %d\n", cq.enQueue(4)); // false (full)

        printf("Rear():     %d\n", cq.Rear());     // 3
        printf("isFull():   %d\n", cq.isFull());   // true
        printf("deQueue():  %d\n", cq.deQueue());  // true (removes 1)
        printf("enQueue(4): %d\n", cq.enQueue(4)); // true
        printf("Rear():     %d\n", cq.Rear());     // 4
        return 0;
}

/*
 * Time Complexity: O(1) for all operations.
 * Space Complexity: O(k) fixed circular buffer.
 */
