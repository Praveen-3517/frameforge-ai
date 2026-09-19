import java.util.HashMap;
import java.util.Map;

/**
 * Problem Statement:
 * Given an array of integers `arr`.
 * We want to select three indices `i`, `j` and `k` where `(0 <= i < j <= k < arr.length)`.
 * Define `a` and `b` as:
 *   a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
 *   b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
 * Return the number of triplets (i, j, k) where `a == b`.
 * (LeetCode 1442: Count Triplets That Can Form Two Arrays of Equal XOR).
 *
 * Asked in: Amazon, Adobe, Google, Microsoft
 *
 * Approach:
 * - Fundamental XOR Property:
 *   a == b  <=>  a ^ b == 0
 *   Therefore: `arr[i] ^ arr[i + 1] ^ ... ^ arr[k] == 0`.
 *   Notice that `j` does not even affect whether the subarray has XOR 0!
 *   If any subarray `arr[i..k]` has XOR sum 0, ANY choice of `j` strictly between `i` and `k`
 *   (i < j <= k) will divide it into two equal XOR halves `a` and `b`.
 *   The number of valid choices for `j` is simply: `k - i`.
 * - Approach 1: Prefix XOR Array (O(N^2) time, O(N) space):
 *   `prefix[x] = arr[0] ^ ... ^ arr[x-1]`.
 *   Subarray `arr[i..k]` has XOR 0 if and only if `prefix[i] == prefix[k + 1]`.
 *   For every such pair, add `(k - i)` to the total answer.
 * - Approach 2: One-Pass Hash Map Optimization (O(N) time, O(N) space):
 *   Track frequency and sum of previous indices for each prefix XOR value.
 */
class CountTripletsEqualXOR {

    // Approach 1: Prefix XOR Array - O(N^2)
    public static int countTripletsPrefix(int[] arr) {
        int n = arr.length;
        int[] prefix = new int[n + 1];

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] ^ arr[i];
        }

        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int k = i + 1; k < n; k++) {
                if (prefix[i] == prefix[k + 1]) {
                    count += (k - i);
                }
            }
        }

        return count;
    }

    // Approach 2: Single-Pass Hash Map - O(N)
    public static int countTripletsOptimal(int[] arr) {
        int n = arr.length;
        int currentXor = 0;
        int totalTriplets = 0;

        // Map prefixXor -> total count of occurrences
        Map<Integer, Integer> countMap = new HashMap<>();
        // Map prefixXor -> sum of indices where it occurred
        Map<Integer, Integer> totalIndexMap = new HashMap<>();

        // Base case: prefix 0 occurs at index -1 (in 0-indexed terms)
        countMap.put(0, 1);
        totalIndexMap.put(0, -1);

        for (int k = 0; k < n; k++) {
            currentXor ^= arr[k];

            if (countMap.containsKey(currentXor)) {
                int count = countMap.get(currentXor);
                int totalIndex = totalIndexMap.get(currentXor);
                totalTriplets += count * (k - 1) - totalIndex;
            }

            countMap.put(currentXor, countMap.getOrDefault(currentXor, 0) + 1);
            totalIndexMap.put(currentXor, totalIndexMap.getOrDefault(currentXor, 0) + k);
        }

        return totalTriplets;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 1442: Count Triplets with Equal XOR ===");

        int[][] testArrays = {
            { 2, 3, 1, 6, 7 },     // 4 triplets
            { 1, 1, 1, 1, 1 },     // 10 triplets
            { 2, 3 },              // 0 triplets
            { 1, 3, 5, 7, 9 }      // 3 triplets
        };

        for (int[] arr : testArrays) {
            int ansPrefix = countTripletsPrefix(arr);
            int ansOptimal = countTripletsOptimal(arr);
            System.out.printf("Array: %s%n ==> Prefix: %d | Optimal O(N): %d%n%n",
                    java.util.Arrays.toString(arr), ansPrefix, ansOptimal);
        }
    }
}

/*
 * Time Complexity:
 *   - Approach 1: O(N^2) with prefix array.
 *   - Approach 2: O(N) single pass with hash maps.
 * Space Complexity: O(N) - Storage for prefix XOR frequency tables.
 */
