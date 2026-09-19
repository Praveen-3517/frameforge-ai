import java.util.HashSet;
import java.util.Set;

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
class BitwiseMaximumXOROfTwoNumbers {

    // Approach 1: Bitwise Prefix HashSet (Clean and highly interview-favored)
    public static int findMaximumXOR(int[] nums) {
        int maxXor = 0;
        int mask = 0;

        // Traverse bits from most significant (bit 30 for non-negative ints) to least
        for (int i = 30; i >= 0; i--) {
            mask |= (1 << i);
            Set<Integer> prefixes = new HashSet<>();

            for (int num : nums) {
                prefixes.add(num & mask);
            }

            // Greedily hypothesize that the i-th bit can be set to 1 in maxXor
            int candidate = maxXor | (1 << i);

            for (int prefix : prefixes) {
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

    public static int findMaximumXORTrie(int[] nums) {
        TrieNode root = new TrieNode();

        // 1. Insert all numbers into Trie
        for (int num : nums) {
            TrieNode curr = root;
            for (int i = 30; i >= 0; i--) {
                int bit = (num >>> i) & 1;
                if (curr.children[bit] == null) {
                    curr.children[bit] = new TrieNode();
                }
                curr = curr.children[bit];
            }
        }

        // 2. Query each number against the Trie for maximum XOR
        int maxXor = 0;
        for (int num : nums) {
            TrieNode curr = root;
            int currentXor = 0;
            for (int i = 30; i >= 0; i--) {
                int bit = (num >>> i) & 1;
                int oppositeBit = 1 - bit;

                // Prefer opposite bit to produce 1 in XOR
                if (curr.children[oppositeBit] != null) {
                    currentXor |= (1 << i);
                    curr = curr.children[oppositeBit];
                } else {
                    curr = curr.children[bit];
                }
            }
            maxXor = Math.max(maxXor, currentXor);
        }

        return maxXor;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 421: Maximum XOR of Two Numbers in an Array ===");

        int[][] testCases = {
            { 3, 10, 5, 25, 2, 8 },               // Max: 5 ^ 25 = 28
            { 14, 70, 53, 83, 49, 91, 36, 80, 92 },// Max: 127
            { 0 },
            { 8, 10, 2 }
        };

        for (int[] nums : testCases) {
            int ansHashSet = findMaximumXOR(nums);
            int ansTrie = findMaximumXORTrie(nums);
            System.out.printf("Array: %s%n ==> HashSet MaxXOR: %d | Trie MaxXOR: %d%n%n",
                    java.util.Arrays.toString(nums), ansHashSet, ansTrie);
        }
    }
}

/*
 * Time Complexity: O(32 * N) = O(N) - 31 passes over N elements.
 * Space Complexity: O(N) - Storage for the prefix HashSet / 32*N Trie nodes.
 */
