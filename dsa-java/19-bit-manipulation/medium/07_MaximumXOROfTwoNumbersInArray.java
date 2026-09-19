/**
 * Problem: Maximum XOR of Two Numbers in an Array (LeetCode 421)
 * Asked in: Google, Amazon, Facebook
 * 
 * Given an integer array nums, return the maximum result of nums[i] XOR nums[j],
 * where 0 <= i <= j < n.
 * 
 * Approach - Greedy Bit-by-Bit with Prefix Set:
 * From the most significant bit to the least:
 * 1. Compute a prefix of all numbers using the current bit mask.
 * 2. Assume we can achieve max XOR by setting this bit to 1 (candidate = ans | (1 << bit)).
 * 3. For the candidate to be achievable, there must exist two prefixes a, b in the prefix set
 *    such that a ^ b == candidate, i.e. for every prefix a, check if a ^ candidate is in set.
 * 4. If achievable, update ans = candidate.
 * 
 * Time Complexity: O(N * 32) = O(N)
 * Space Complexity: O(N) for the prefix set.
 */
import java.util.HashSet;
import java.util.Set;

class MaximumXOROfTwoNumbersInArray {

    public static int findMaximumXOR(int[] nums) {
        int maxXOR = 0;
        int mask = 0;

        for (int bit = 31; bit >= 0; bit--) {
            mask |= (1 << bit);

            Set<Integer> prefixes = new HashSet<>();
            for (int num : nums) {
                prefixes.add(num & mask);
            }

            int candidate = maxXOR | (1 << bit);

            for (int prefix : prefixes) {
                if (prefixes.contains(candidate ^ prefix)) {
                    maxXOR = candidate;
                    break;
                }
            }
        }

        return maxXOR;
    }

    public static void main(String[] args) {
        int[] nums1 = {3, 10, 5, 25, 2, 8};
        System.out.println("Max XOR: " + findMaximumXOR(nums1) + " (Expected: 28)");
        // 5 XOR 25 = 28

        int[] nums2 = {14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70};
        System.out.println("Max XOR: " + findMaximumXOR(nums2) + " (Expected: 127)");
    }
}
