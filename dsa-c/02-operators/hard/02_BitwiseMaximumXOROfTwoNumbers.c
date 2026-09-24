/**
 * Problem Statement:
 * Given an integer array `nums`, return the maximum result of `nums[i] XOR nums[j]`,
 * where 0 <= i <= j < n.
 * Solve in O(N) runtime complexity.
 * (LeetCode 421: Maximum XOR of Two Numbers in an Array).
 *
 * Asked in: Google, Amazon, Microsoft, ByteDance
 *
 * Approach 1: Bitwise Prefix Greedy with HashSet (O(31 * N) = O(N)):
 * - We greedily build the maximum XOR from MSB (bit 30) down to LSB (bit 0).
 * - For each bit position `i`:
 *   1. Extend our prefix mask: `mask = mask | (1 << i)`.
 *   2. Collect all prefixes in a HashSet: `prefix = num & mask`.
 *   3. Greedily assume the i-th bit can be 1: `candidate = maxXor | (1 << i)`.
 *   4. Mathematical XOR identity: If `a ^ b = candidate`, then `a ^ candidate = b`.
 *      Check if there exists a prefix `p` such that `candidate ^ p` is in the set.
 *      If yes, `maxXor = candidate`.
 *
 * Approach 2: Binary Trie (Bit-level prefix tree):
 * - Store numbers bit-by-bit (0/1 branches) from bit 30 to 0.
 * - For each number, greedily follow the opposite bit branch to maximize XOR at each step.
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

// Approach 1: Bitwise Prefix HashSet (Clean and highly interview-favored)
    int findMaximumXOR(int* nums) {
        int maxXor = 0;
        int mask = 0;

        // Traverse bits from most significant (bit 30 for non-negative ints) to least
        for (int i = 30; i >= 0; i--) {
            mask |= (1 << i);
            Set<int> prefixes = new HashSet<>();

            for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
                prefixes.add(num & mask);
            }

            // Greedily hypothesize that the i-th bit can be set to 1 in maxXor
            int candidate = maxXor | (1 << i);

            for (size_t _idx = 0; _idx < sizeof(prefixes)/sizeof(prefixes[0]); _idx++) {
        int prefix = prefixes[_idx];
                // If prefix ^ candidate exists in prefixes, then two numbers produce candidate!
                if (prefixes.contains(prefix ^ candidate)) {
                    maxXor = candidate;
                    break;
                }
            }
        }

        return maxXor;
    }

    // Approach 2: Binary Trie Node
    static class TrieNode {
        TrieNode[] children = new TrieNode[2];
    }

    int findMaximumXORTrie(int* nums) {
        TrieNode root = new TrieNode();

        // 1. Insert all numbers into Trie
        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            TrieNode curr = root;
            for (int i = 30; i >= 0; i--) {
                int bit = (num >>> i) & 1;
                if (curr.children[bit] == NULL) {
                    curr.children[bit] = new TrieNode();
                }
                curr = curr.children[bit];
            }
        }

        // 2. Query each number against the Trie for maximum XOR
        int maxXor = 0;
        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            TrieNode curr = root;
            int currentXor = 0;
            for (int i = 30; i >= 0; i--) {
                int bit = (num >>> i) & 1;
                int oppositeBit = 1 - bit;

                // Prefer opposite bit to produce 1 in XOR
                if (curr.children[oppositeBit] != NULL) {
                    currentXor |= (1 << i);
                    curr = curr.children[oppositeBit];
                } else {
                    curr = curr.children[bit];
                }
            }
            maxXor = MAX(maxXor, currentXor);
        }

        return maxXor;
    }

    int main(void) {
        printf("=== LeetCode 421: Maximum XOR of Two Numbers in an Array ===\n");

        int** testCases = {
            { 3, 10, 5, 25, 2, 8 },               // Max: 5 ^ 25 = 28
            { 14, 70, 53, 83, 49, 91, 36, 80, 92 },// Max: 127
            { 0 },
            { 8, 10, 2 }
        };

        for (int* nums : testCases) {
            int ansHashSet = findMaximumXOR(nums);
            int ansTrie = findMaximumXORTrie(nums);
            printf("Array: %s\n ==> HashSet MaxXOR: %d | Trie MaxXOR: %d\n\n",
                    java.util."[array]", ansHashSet, ansTrie);
        }
        return 0;
}

/*
 * Time Complexity: O(32 * N) = O(N) - 31 passes over N elements.
 * Space Complexity: O(N) - Storage for the prefix HashSet / 32*N Trie nodes.
 */
