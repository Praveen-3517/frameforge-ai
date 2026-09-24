/**
 * Problem Statement:
 * Given a bitmask `mask`, enumerate all of its submasks efficiently in strictly descending order.
 * Furthermore, prove and demonstrate why enumerating all submasks for all masks of an N-element set
 * runs in O(3^N) time rather than O(4^N).
 * Also implement Gosper's Hack to enumerate all N-bit integers with exactly K set bits in O(1) per state.
 *
 * Asked in: Google, Codeforces, Competitive Programming Rounds, Advanced Graph/DP Interviews
 *
 * Approach:
 * - Submask Decrement Trick:
 *   To iterate over all submasks of `mask`:
 *   ```java
 *   for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
 *       // Process non-empty submask
 *   }
 *   ```
 *   Why it works:
 *   - Subtracting 1 (`sub - 1`) clears the lowest set bit and sets all trailing 0s to 1s.
 *   - Bitwise ANDing with `mask` (`& mask`) masks out all bits that were not in the original mask,
 *     jumping directly to the next lexicographically smaller valid submask without wasting iterations!
 * - Mathematical Proof of O(3^N):
 *   By the Binomial Theorem:
 *   sum_{k=0}^{N} C(N, k) * 2^k = (1 + 2)^N = 3^N!
 *   Each element can be in 3 states: not in mask, in mask but not in submask, or in both!
 * - Gosper's Hack:
 *   Computes the next integer with the exact same number of set bits (popcount):
 *   `int c = x & -x; int r = x + c; return (((r ^ x) >>> 2) / c) | r;`
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

void enumerateSubmasks(int mask) {
        printf("--- Submasks of Mask %d (Binary: %s) ---\n",
                mask, toBinaryString(mask));

        int count = 0;
        int sub = mask;
        while (true) {
            printf("  Submask #%2d: %3d | Binary: %5s\n",
                    ++count, sub, const char*.format("%5s", toBinaryString(sub)).replace(' ', '0'));

            if (sub == 0) break;
            sub = (sub - 1) & mask;
        }
        printf("Total Submasks: " + count + " (Matches 2^" + int.bitCount(mask) + ")\n");
    }

    // Gosper's Hack: Generates next higher integer with identical count of set bits
    int nextSameWeightNumber(int x) {
        int lowestSetBit = x & -x;
        int nextHigherWithoutBits = x + lowestSetBit;
        int changedBits = x ^ nextHigherWithoutBits;
        int rightJustified = (changedBits >>> 2) / lowestSetBit;
        return nextHigherWithoutBits | rightJustified;
    }

    void demonstrateGospersHack(int k, int n) {
        printf("\n--- Gosper's Hack: All masks of length %d with exactly %d set bits ---\n", n, k);
        int mask = (1 << k) - 1; // Smallest number with k set bits (e.g. 00111 for k=3)
        int limit = 1 << n;

        int count = 0;
        while (mask < limit) {
            printf("  Combination #%2d: %s (Val: %d)\n",
                    ++count, const char*.format("%" + n + "s", toBinaryString(mask)).replace(' ', '0'), mask);
            mask = nextSameWeightNumber(mask);
        }
    }

    int main(void) {
        printf("=== Advanced Bitmask Enumeration (Submask Trick & Gosper's Hack) ===\n");
        enumerateSubmasks(22); // 22 = 10110_2 (3 set bits -> 2^3 = 8 submasks)
        demonstrateGospersHack(3, 5); // 5 choose 3 = 10 combinations
        return 0;
}

/*
 * Time Complexity:
 *   - Submask enumeration of mask with k bits: O(2^k).
 *   - All submasks of all masks of size N: O(3^N).
 *   - Gosper's Hack per combination: O(1) CPU instructions.
 * Space Complexity: O(1) - Primitive register manipulation only.
 */
