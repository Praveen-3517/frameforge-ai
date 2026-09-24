/*
 * Problem Statement:
 * Given an integer array nums and an integer k, return the k-th largest element in the array.
 * Note that it is the k-th largest element in sorted order, not the k-th distinct element.
 * 
 * Example 1:
 * Input: nums = [3,2,1,5,6,4], k = 2
 * Output: 5
 * 
 * Example 2:
 * Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 * Output: 4
 * 
 * Asked in: Facebook/Meta, Amazon, Microsoft, Apple, Google
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

/**
     * Approach:
     * Min-Heap of Size K:
     * - Maintain a min-heap of capacity K.
     * - Iterate through nums:
     *   - Add num to heap.
     *   - If heap size exceeds K, poll (evict) the smallest.
     * - After processing all elements, the root of the min-heap is the K-th largest element!
     */
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
        int k1 = 2;
        printf("Input: [3, 2, 1, 5, 6, 4], k = 2\n");
        printf("2nd largest: %d\n", findKthLargest(nums1, k1));

        int* nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
        int k2 = 4;
        printf("\nInput: [3, 2, 3, 1, 2, 4, 5, 5, 6], k = 4\n");
        printf("4th largest: %d\n", findKthLargest(nums2, k2));
        return 0;
}

/*
 * Time Complexity: O(N log K) - Each insertion into heap of size K takes O(log K).
 * Space Complexity: O(K) - Heap stores exactly K elements.
 */
