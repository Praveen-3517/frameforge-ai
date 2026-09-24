/*
 * Problem Statement:
 * Design your implementation of the circular double-ended queue (deque).
 * Implement the MyCircularDeque class:
 * - MyCircularDeque(int k): Initializes the deque with a maximum size of k.
 * - boolean insertFront(int value): Adds an item at the front.
 * - boolean insertLast(int value): Adds an item at the rear.
 * - boolean deleteFront(): Deletes an item from the front.
 * - boolean deleteLast(): Deletes an item from the rear.
 * - int getFront(), int getRear(), boolean isEmpty(), boolean isFull().
 * (LeetCode 641: Design Circular Deque)
 * 
 * Asked in: Google, Amazon, Facebook/Meta
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

static class MyCircularDeque {
        static const int* data;
        static int front;
        static int rear;
        static int count;
        static const int capacity;

        MyCircularDeque(int k) {
            this.capacity = k;
            this.data = (int*)malloc((k) * sizeof(int));
            this.front = 0;
            this.rear = 0;
            this.count = 0;
        }

        bool insertFront(int value) {
            if (isFull()) return false;
            front = (front - 1 + capacity) % capacity;
            data[front] = value;
            count++;
            return true;
        }

        bool insertLast(int value) {
            if (isFull()) return false;
            data[rear] = value;
            rear = (rear + 1) % capacity;
            count++;
            return true;
        }

        bool deleteFront() {
            if (isEmpty()) return false;
            front = (front + 1) % capacity;
            count--;
            return true;
        }

        bool deleteLast() {
            if (isEmpty()) return false;
            rear = (rear - 1 + capacity) % capacity;
            count--;
            return true;
        }

        int getFront() {
            return isEmpty() ? -1 : data[front];
        }

        int getRear() {
            if (isEmpty()) return -1;
            return data[(rear - 1 + capacity) % capacity];
        }

        bool isEmpty() { return count == 0; }
        bool isFull() { return count == capacity; }
    }

    int main(void) {
        MyCircularDeque deque = new MyCircularDeque(3);

        printf("--- Testing Circular Deque (Capacity = 3) ---\n");
        printf("insertLast(1):  %d\n", deque.insertLast(1));  // true
        printf("insertLast(2):  %d\n", deque.insertLast(2));  // true
        printf("insertFront(3): %d\n", deque.insertFront(3)); // true
        printf("insertFront(4): %d\n", deque.insertFront(4)); // false (full)

        printf("getRear():      %d\n", deque.getRear());      // 2
        printf("isFull():       %d\n", deque.isFull());       // true
        printf("deleteLast():   %d\n", deque.deleteLast());   // true (removes 2)
        printf("insertFront(4): %d\n", deque.insertFront(4)); // true
        printf("getFront():     %d\n", deque.getFront());     // 4
        return 0;
}

/*
 * Time Complexity: O(1) for all operations.
 * Space Complexity: O(k) fixed circular buffer.
 */
