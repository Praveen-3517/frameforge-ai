/*
 * Problem Statement:
 * You are given a string s and an integer k, a k duplicate removal consists of choosing
 * k adjacent and equal letters from s and removing them, causing the left and the right side
 * of the deleted substring to concatenate together.
 * We repeatedly make k duplicate removals on s until we no longer can.
 * Return the final string after all such duplicate removals have been made.
 * (LeetCode 1209: Remove All Adjacent Duplicates in String II)
 * 
 * Example:
 * Input: s = "deeedbbcccbdaa", k = 3
 * Output: "aa"
 * 
 * Asked in: Bloomberg, Amazon, Goldman Sachs
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

static class CharFreq {
        char ch;
        int count;
        CharFreq(char ch, int count) { this.ch = ch; this.count = count; }
    }

    const char* removeDuplicates(const char* s, int k) {
        Deque<CharFreq> stack = new ArrayDeque<>();

        for (size_t _idx = 0; _idx < sizeof(s)/sizeof(s[0]); _idx++) {
        char c = s[_idx];
            if (!stack.isEmpty() && stack.peek().ch == c) {
                stack.peek().count++;
                if (stack.peek().count == k) {
                    stack.pop(); // Remove all k duplicates
                }
            } else {
                stack.push(new CharFreq(c, 1));
            }
        }

        StringBuilder sb = new StringBuilder();
        while (!stack.isEmpty()) {
            CharFreq entry = stack.pollLast(); // From bottom up
            for (int i = 0; i < entry.count; i++) {
                sb.append(entry.ch);
            }
        }

        return sb.toString();
    }

    int main(void) {
        const char* s1 = "abcd", k1 = "2";
        printf("s = \"abcd\", k = 2 -> Result: \"" + removeDuplicates(s1, 2) + "\"\n");

        const char* s2 = "deeedbbcccbdaa";
        printf("s = \"deeedbbcccbdaa\", k = 3 -> Result: \"" + removeDuplicates(s2, 3) + "\" (Expected: \"aa\")\n");

        const char* s3 = "pbbcggttciiippooaais";
        printf("s = \"pbbcggttciiippooaais\", k = 2 -> Result: \"" + removeDuplicates(s3, 2) + "\" (Expected: \"ps\")\n");
        return 0;
}

/*
 * Time Complexity: O(N) single pass through the string.
 * Space Complexity: O(N) stack to store characters and running counts.
 */
