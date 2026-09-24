/*
 * Problem Statement:
 * Given an integer array nums and an integer k, return the k most frequent elements.
 * You may return the answer in any order.
 * 
 * Example:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1, 2]
 * 
 * Asked in: Amazon, Facebook/Meta, Google, Bloomberg, Microsoft
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
     * 1. Count frequencies using HashMap: O(N).
     * 2. Maintain a Min-Heap of size K comparing entry frequencies.
     * 3. For every key in map, offer to heap; if size exceeds K, poll smallest frequency.
     * 4. Remaining K elements in heap are top K frequent: O(U log K).
     */
    int* topKFrequent(int* nums, int k) {
        Map<int, int> countMap = new HashMap<>();
        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int n = nums[_idx];
            countMap.merge(n, 1, int::sum);
        }

        // Min-Heap ordered by frequency (lowest frequency on top)
        PriorityQueue<int> heap = new PriorityQueue<>(
                (a, b) -> int.compare(countMap.get(a), countMap.get(b))
        );

        for (int key : countMap.keySet()) {
            heap.offer(key);
            if (heap.size() > k) {
                heap.poll();
            }
        }

        int* result = (int*)malloc((k) * sizeof(int));
        for (int i = k - 1; i >= 0; i--) {
            result[i] = heap.poll();
        }
        return result;
    }

    int main(void) {
        int* nums = {1, 1, 1, 2, 2, 3};
        int k = 2;

        int* topK = topKFrequent(nums, k);
        printf("Array: [array], k = %d\n", k);
        printf("Top " + k + " frequent elements: " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: O(N log K) where N is array length and K is heap size.
 * Space Complexity: O(N) for hash map frequency storage and min-heap.
 */
