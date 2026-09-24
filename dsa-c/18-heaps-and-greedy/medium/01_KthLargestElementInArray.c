/**
 * Problem: Kth Largest Element in an Array (LeetCode 215)
 * Asked in: Facebook, Amazon, Google, Microsoft, Apple
 * 
 * Given an integer array nums and an integer k, return the kth largest element in the array.
 * Note that it is the kth largest element in sorted order, not the kth distinct element.
 * 
 * Approach:
 * Min-Heap of size K:
 * Maintain a Min-Heap of size k.
 * For each num:
 * - Offer num to minHeap.
 * - If size > k, poll the smallest element.
 * The root of the heap is the k-th largest element!
 * 
 * Time Complexity: O(N log K)
 * Space Complexity: O(K)
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

int findKthLargest(int* nums, int k) {
        PriorityQueue<int> minHeap = new PriorityQueue<>(k);

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            minHeap.offer(num);
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }

        return minHeap.peek();
    }

    int main(void) {
        int* nums1 = {3, 2, 1, 5, 6, 4};
        printf("2nd largest: " + findKthLargest(nums1, 2) + " (Expected: 5)\n");

        int* nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
        printf("4th largest: " + findKthLargest(nums2, 4) + " (Expected: 4)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
