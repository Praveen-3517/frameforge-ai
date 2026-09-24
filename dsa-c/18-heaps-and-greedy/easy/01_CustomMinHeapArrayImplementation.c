/**
 * Problem: Custom Min-Heap Implementation using Array
 * Asked in: Amazon, Google, Microsoft, Adobe
 * 
 * Implement a complete Min-Heap data structure from scratch using an array supporting:
 * - insert(val): Add element and heapify up in O(log N).
 * - extractMin(): Remove and return root and heapify down in O(log N).
 * - peek(): Return root without removing in O(1).
 * - size() and isEmpty().
 * 
 * Time Complexity:
 * - insert: O(log N)
 * - extractMin: O(log N)
 * - peek: O(1)
 * Space Complexity: O(N) for internal array.
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

static int* heap;
    static int size;
    static int capacity;

    CustomMinHeapArrayImplementation(int capacity) {
        this.capacity = capacity;
        this.size = 0;
        this.heap = (int*)malloc((capacity) * sizeof(int));
    }

    void insert(int val) {
        if (size == capacity) {
            capacity *= 2;
            heap = Arrays.copyOf(heap, capacity);
        }
        heap[size] = val;
        heapifyUp(size);
        size++;
    }

    int extractMin() {
        if (size == 0) fprintf(stderr, "Exception: invalid argument
"); return 0;
        int min = heap[0];
        heap[0] = heap[size - 1];
        size--;
        if (size > 0) {
            heapifyDown(0);
        }
        return min;
    }

    int peek() {
        if (size == 0) fprintf(stderr, "Exception: invalid argument
"); return 0;
        return heap[0];
    }

    int size() {
        return size;
    }

    static void heapifyUp(int idx) {
        int parent = (idx - 1) / 2;
        while (idx > 0 && heap[idx] < heap[parent]) {
            swap(idx, parent);
            idx = parent;
            parent = (idx - 1) / 2;
        }
    }

    static void heapifyDown(int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest != idx) {
            swap(idx, smallest);
            heapifyDown(smallest);
        }
    }

    static void swap(int i, int j) {
        int temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    int main(void) {
        CustomMinHeapArrayImplementation minHeap = new CustomMinHeapArrayImplementation(5);
        int* vals = {15, 10, 20, 17, 8};
        for (int v : vals) minHeap.insert(v);

        printf("Peek: " + minHeap.peek() + " (Expected: 8)\n");
        printf("Extract: " + minHeap.extractMin() + " (Expected: 8)\n");
        printf("Peek: " + minHeap.peek() + " (Expected: 10)\n");
        printf("Extract: " + minHeap.extractMin() + " (Expected: 10)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
