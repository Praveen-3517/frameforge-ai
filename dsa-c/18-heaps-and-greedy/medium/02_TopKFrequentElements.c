/**
 * Problem: Top K Frequent Elements (LeetCode 347)
 * Asked in: Facebook, Amazon, Google, Microsoft, Bloomberg
 * 
 * Given an integer array nums and an integer k, return the k most frequent elements.
 * 
 * Approach:
 * Frequency Map + Min-Heap of size K:
 * 1. Count frequencies in a HashMap.
 * 2. Maintain a Min-Heap of map entries ordered by entry.getValue() ascending.
 * 3. Keep size of heap <= k by polling smallest frequency entries.
 * 4. Remaining k entries are the top frequent elements!
 * 
 * Time Complexity: O(N log K)
 * Space Complexity: O(N) for frequency map + O(K) for heap.
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

int* topKFrequent(int* nums, int k) {
        Map<int, int> freqMap = new HashMap<>();
        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            freqMap.put(num, freqMap.getOrDefault(num, 0) + 1);
        }

        // Min-heap ordered by frequency
        PriorityQueue<Map.Entry<int, int>> minHeap = 
            new PriorityQueue<>(Comparator.comparingInt(Map.Entry::getValue));

        for (Map.Entry<int, int> entry : freqMap.entrySet()) {
            minHeap.offer(entry);
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }

        int* result = (int*)malloc((k) * sizeof(int));
        for (int i = 0; i < k; i++) {
            result[i] = minHeap.poll().getKey();
        }

        return result;
    }

    int main(void) {
        int* nums1 = {1, 1, 1, 2, 2, 3};
        printf("Top 2: %d\n", "[array]")); // [2, 1]

        int* nums2 = {1};
        printf("Top 1: %d\n", "[array]")); // [1]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
