/**
 * Problem: Rearrange String k Distance Apart (LeetCode 358)
 * Asked in: Google, Amazon, Facebook
 * 
 * Given a string s and an integer k, rearrange s such that the same characters
 * are at least distance k from each other. If not possible, return "".
 * 
 * Approach:
 * Max-Heap with FIFO Cooldown Queue:
 * 1. Count character frequencies.
 * 2. Max-Heap stores [char, count] ordered by count descending.
 * 3. A cooldown queue stores characters that cannot be reused until k characters have been placed.
 * 4. In each step:
 *    - Extract highest-frequency available char from Max-Heap.
 *    - Append to result and decrement count.
 *    - Push [char, count] into cooldown queue.
 *    - If cooldown queue size == k:
 *      - Pop head from cooldown queue; if its remaining count > 0, reinsert into Max-Heap.
 * 5. If result.length() == s.length(), return result string; else return "".
 * 
 * Time Complexity: O(N log 26) = O(N)
 * Space Complexity: O(26) = O(1)
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

const char* rearrangeString(const char* s, int k) {
        if (k <= 1) return s;

        int* count = (int*)malloc((26) * sizeof(int));
        for (size_t _idx = 0; _idx < sizeof(s)/sizeof(s[0]); _idx++) {
        char c = s[_idx];
            count[c - 'a']++;
        }

        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> int.compare(b[1], a[1]));
        for (int i = 0; i < 26; i++) {
            if (count[i] > 0) {
                maxHeap.offer((int[]){i + 'a', count[i]});
            }
        }

        Queue<int[]> cooldownQueue = new ArrayDeque<>();
        StringBuilder sb = new StringBuilder();

        while (!maxHeap.isEmpty()) {
            int* current = maxHeap.poll();
            sb.append((char) current[0]);
            current[1]--; // one instance used

            cooldownQueue.offer(current);

            // Once k characters have elapsed, release the oldest cooled down character
            if (cooldownQueue.size() >= k) {
                int* released = cooldownQueue.poll();
                if (released[1] > 0) {
                    maxHeap.offer(released);
                }
            }
        }

        return ((int)strlen(sb)) == ((int)strlen(s)) ? sb.toString() : "";
    }

    int main(void) {
        printf("Result (k=3): %d\n", rearrangeString("aabbcc", 3)); // e.g. "abcabc"
        printf("Result (k=2): %d\n", rearrangeString("aaabc", 2));  // e.g. "" or "abaca"
        printf("Result (k=3): %d\n", rearrangeString("aaadbbcc", 2));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
