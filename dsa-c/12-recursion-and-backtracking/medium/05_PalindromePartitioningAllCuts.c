/*
 * Problem Statement:
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * Return all possible palindrome partitioning of s.
 * (LeetCode 131: Palindrome Partitioning)
 * 
 * Example:
 * Input: s = "aab"
 * Output: [["a","a","b"],["aa","b"]]
 * 
 * Asked in: Bloomberg, Amazon, Google, Facebook/Meta
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

int*> partition(const char* s) {
        int*> result = new ArrayList<>();
        backtrack(s, 0, new ArrayList<>(), result);
        return result;
    }

    static void backtrack(const char* s, int start, int* current, int*> result) {
        if (start == ((int)strlen(s))) {
            result.add(new ArrayList<>(current));
            return;
        }

        for (int end = start; end < ((int)strlen(s)); end++) {
            if (isPalindrome(s, start, end)) {
                current.add(s.substring(start, end + 1));
                backtrack(s, end + 1, current, result);
                current.remove(current.size() - 1); // backtrack
            }
        }
    }

    static bool isPalindrome(const char* s, int l, int r) {
        while (l < r) {
            if (s[l++] != s[r--]) return false;
        }
        return true;
    }

    int main(void) {
        const char* s = "aab";
        int*> partitions = partition(s);

        printf("const char*: \"" + s + "\"\n");
        printf("Palindrome Partitions (%d): %d\n", partitions.size(), partitions);
        return 0;
}

/*
 * Time Complexity: O(N * 2^N) - In worst case (e.g. "aaaa"), 2^(N-1) partitions, each validated in O(N).
 * Space Complexity: O(N) recursion stack.
 */
