/**
 * Problem Statement:
 * The DNA sequence is composed of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.
 * Given a string `s` representing a DNA sequence, return all 10-letter-long sequences
 * (substrings) that occur more than once in a DNA molecule.
 * (LeetCode 187: Repeated DNA Sequences).
 *
 * Example:
 * s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
 * Output: ["AAAAACCCCC", "CCCCCAAAAA"]
 *
 * Asked in: Amazon, Google, LinkedIn, Apple
 *
 * Approach:
 * - 2-Bit Rolling Hash Bitmask (O(N) Time, O(N) Space):
 *   Since there are only 4 possible characters, encode each in 2 bits:
 *   'A' = 00_2 (0), 'C' = 01_2 (1), 'G' = 10_2 (2), 'T' = 11_2 (3).
 *   A 10-character sequence takes exactly `10 * 2 = 20 bits`, easily fitting in a 32-bit `int`!
 *   - 20-bit window mask: `(1 << 20) - 1 = 0xFFFFF`.
 *   - Rolling update:
 *     `hash = ((hash << 2) | charCode) & 0xFFFFF;`
 *   - Store integer hashes in `Set<Integer> seen` and duplicate hashes in `Set<Integer> added`.
 *   - Eliminates String substring allocations during hashing!
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

static int encode(char ch) {
        return switch (ch) {
            case 'A' -> 0;
            case 'C' -> 1;
            case 'G' -> 2;
            case 'T' -> 3;
            default  -> 0;
        };
    }

    int* findRepeatedDnaSequences(const char* s) {
        int* result = new ArrayList<>();
        if (s == NULL || ((int)strlen(s)) < 10) return result;

        int n = ((int)strlen(s));
        int hash = 0;
        int mask = (1 << 20) - 1; // 20-bit mask for 10 nucleotides

        // Compute initial hash for first 9 characters
        for (int i = 0; i < 9; i++) {
            hash = (hash << 2) | encode(s[i]);
        }

        Set<int> seenHashes = new HashSet<>();
        Set<int> duplicateHashes = new HashSet<>();

        for (int i = 9; i < n; i++) {
            // Slide window: shift left by 2 bits, add new nucleotide, mask to 20 bits
            hash = ((hash << 2) | encode(s[i])) & mask;

            if (!seenHashes.add(hash)) {
                // If hash was already seen, check if already added to results
                if (duplicateHashes.add(hash)) {
                    result.add(s.substring(i - 9, i + 1));
                }
            }
        }

        return result;
    }

    int main(void) {
        printf("=== LeetCode 187: Repeated DNA Sequences (2-Bit Rolling Hash) ===\n");

        const char* dna = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
        int* repeated = findRepeatedDnaSequences(dna);

        printf("DNA Sequence: %d\n", dna);
        printf("Repeated 10-mers: %d\n", repeated);
        return 0;
}

/*
 * Time Complexity: O(N) - Linear scan with O(1) bit-shift hash updates.
 * Space Complexity: O(N) - HashSets storing 32-bit primitive integer hashes.
 */
