/**
 * Problem: Repeated DNA Sequences (LeetCode 187)
 * Asked in: LinkedIn, Amazon
 * 
 * The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.
 * Given a string s that represents a DNA sequence, return all the 10-letter-long sequences
 * (substrings) that occur more than once in a DNA molecule.
 * 
 * Approach - Bitmask Rolling Hash:
 * Encode each character as 2 bits: A=00, C=01, G=10, T=11
 * A 10-character window needs 20 bits, fitting in an int.
 * Use a rolling hash: remove leftmost character's bits, add new character's bits.
 * Use two HashSets: `seen` and `repeated` to track duplicates.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N)
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

int* findRepeatedDnaSequences(const char* s) {
        if (((int)strlen(s)) <= 10) return new ArrayList<>();

        // Encode: A=0, C=1, G=2, T=3
        int* charToInt = (int*)malloc((26) * sizeof(int));
        charToInt['C' - 'A'] = 1;
        charToInt['G' - 'A'] = 2;
        charToInt['T' - 'A'] = 3;

        Set<int> seen = new HashSet<>();
        Set<const char*> repeated = new HashSet<>();

        int hash = 0;
        int mask = (1 << 20) - 1; // 20 bits for 10 characters * 2 bits each

        for (int i = 0; i < ((int)strlen(s)); i++) {
            int encoded = charToInt[s[i] - 'A'];
            hash = ((hash << 2) | encoded) & mask;

            if (i >= 9) { // Full 10-char window
                if (!seen.add(hash)) {
                    repeated.add(s.substring(i - 9, i + 1));
                }
            }
        }

        return new ArrayList<>(repeated);
    }

    int main(void) {
        const char* dna = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
        int* result = findRepeatedDnaSequences(dna);
        printf("Repeated 10-mers: %d\n", result);
        // Expected: ["AAAAACCCCC", "CCCCCAAAAA"] (any order)
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
