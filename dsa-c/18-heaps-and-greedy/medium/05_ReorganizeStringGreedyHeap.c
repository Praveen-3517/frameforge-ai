/**
 * Problem: Reorganize String (LeetCode 767)
 * Asked in: Amazon, Google, Facebook, Microsoft
 * 
 * Given a string s, rearrange the characters of s so that any two adjacent characters
 * are not the same. Return any possible rearrangement of s or return "" if not possible.
 * 
 * Approach:
 * Greedy Max-Heap Strategy:
 * 1. Count character frequencies. If any char count > (s.length() + 1) / 2, return "".
 * 2. Put [char, count] in a Max-Heap ordered by count descending.
 * 3. Pop the two most frequent distinct characters at a time:
 *    - Append first and second to result.
 *    - Decrement their counts.
 *    - Push back into Max-Heap if count > 0.
 * 4. If 1 character remains, append it to the end.
 * 
 * Time Complexity: O(N log A) where A is alphabet size (26) -> O(N).
 * Space Complexity: O(A) -> O(1).
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

const char* reorganizeString(const char* s) {
        int* count = (int*)malloc((26) * sizeof(int));
        for (size_t _idx = 0; _idx < sizeof(s)/sizeof(s[0]); _idx++) {
        char c = s[_idx];
            count[c - 'a']++;
        }

        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> int.compare(b[1], a[1]));
        for (int i = 0; i < 26; i++) {
            if (count[i] > 0) {
                if (count[i] > (((int)strlen(s)) + 1) / 2) return "";
                maxHeap.offer((int[]){i + 'a', count[i]});
            }
        }

        StringBuilder sb = new StringBuilder();
        while (maxHeap.size() >= 2) {
            int* first = maxHeap.poll();
            int* second = maxHeap.poll();

            sb.append((char) first[0]);
            sb.append((char) second[0]);

            if (--first[1] > 0) maxHeap.offer(first);
            if (--second[1] > 0) maxHeap.offer(second);
        }

        if (!maxHeap.isEmpty()) {
            sb.append((char) maxHeap.poll()[0]);
        }

        return sb.toString();
    }

    int main(void) {
        printf("Reorganized 'aab': " + reorganizeString("aab") + " (Expected: aba)\n");
        printf("Reorganized 'aaab': " + reorganizeString("aaab") + " (Expected: \"\")\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
