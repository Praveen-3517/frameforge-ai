/**
 * Problem Statement:
 * Implement the Rabin-Karp Substring Search Algorithm using a polynomial rolling hash function.
 * Given a `text` and a `pattern`, find all starting indices of `pattern` inside `text`.
 *
 * Example:
 * text = "GEEKS FOR GEEKS", pattern = "GEEK" -> Indices: [0, 10]
 *
 * Asked in: Amazon, Google, Microsoft, Adobe
 *
 * Approach:
 * - Polynomial Rolling Hash:
 *   Let base $B = 256$ (number of characters in extended ASCII) and prime modulus $Q = 1000000007$.
 *   - Hash formula:
 *     $H(s) = (s[0] \cdot B^{M-1} + s[1] \cdot B^{M-2} + ... + s[M-1]) \pmod Q$.
 *   - Precompute high power: $H_{pow} = B^{M-1} \pmod Q$.
 *   - Rolling update when window shifts right:
 *     Subtract leading character: `hash = (hash - text[i] * H_pow) % Q`.
 *     Multiply by base: `hash = (hash * B) % Q`.
 *     Add trailing character: `hash = (hash + text[i + M]) % Q`.
 *     If `hash < 0`, add `Q`.
 *   - Hash Collision Check: When `windowHash == patternHash`, perform an explicit `O(M)` character
 *     comparison to eliminate spurious false-positive hash collisions.
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

static const int BASE = 256;
    static const long long MOD = 1000000007L;

    int search(const char* text, const char* pattern) {
        int n = ((int)strlen(text));
        int m = ((int)strlen(pattern));
        if (m > n) return -1;

        long long patternHash = 0;
        long long windowHash = 0;
        long long hPow = 1;

        // Precompute hPow = BASE^(m - 1) % MOD
        for (int i = 0; i < m - 1; i++) {
            hPow = (hPow * BASE) % MOD;
        }

        // Calculate initial hash for pattern and first window of text
        for (int i = 0; i < m; i++) {
            patternHash = (patternHash * BASE + pattern[i]) % MOD;
            windowHash = (windowHash * BASE + text[i]) % MOD;
        }

        // Slide window over text
        for (int i = 0; i <= n - m; i++) {
            if (patternHash == windowHash) {
                // Potential match: verify character-by-character against collision
                bool match = true;
                for (int j = 0; j < m; j++) {
                    if (text[i + j] != pattern[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    return i; // Match found
                }
            }

            // Compute rolling hash for next window
            if (i < n - m) {
                windowHash = (windowHash - text[i] * hPow) % MOD;
                windowHash = (windowHash * BASE + text[i + m]) % MOD;
                if (windowHash < 0) {
                    windowHash += MOD;
                }
            }
        }

        return -1;
    }

    int main(void) {
        printf("=== Rabin-Karp Substring Search (Polynomial Rolling Hash) ===\n");

        const char* text = "GEEKS FOR GEEKS";
        const char* pattern = "GEEK";

        int firstIndex = search(text, pattern);
        printf("Text   : \"%s\"\nPattern: \"%s\"\nMatch Index: %d\n",
                text, pattern, firstIndex);
        return 0;
}

/*
 * Time Complexity: O(N + M) average time, O(N * M) worst-case with malicious hash collisions.
 * Space Complexity: O(1) - Primitive rolling hash registers.
 */
