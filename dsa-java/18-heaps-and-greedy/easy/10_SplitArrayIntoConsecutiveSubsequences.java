import java.util.HashMap;
import java.util.Map;

/**
 * Problem: Split Array into Consecutive Subsequences (LeetCode 659)
 * Asked in: Google, Amazon
 * 
 * You are given an integer array nums that is sorted in non-decreasing order.
 * Determine if it is possible to split nums into one or more subsequences such
 * that both of the following conditions are true:
 * 1. Each subsequence is a consecutive increasing sequence.
 * 2. Each subsequence has a length of 3 or more.
 * 
 * Approach:
 * Greedy Choice with Frequency & Need Maps:
 * - countMap: frequency of each remaining number.
 * - needMap: number of existing valid sequences that need num to extend them.
 * For each num in nums:
 * - If countMap[num] == 0, already consumed -> skip.
 * - If needMap[num] > 0:
 *   - Greedily append num to existing sequence! needMap[num]--, needMap[num + 1]++.
 * - Else if countMap[num + 1] > 0 and countMap[num + 2] > 0:
 *   - Form a new sequence of length 3: [num, num+1, num+2].
 *   - needMap[num + 3]++.
 * - Otherwise: Cannot place num -> return false.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
class SplitArrayIntoConsecutiveSubsequences {

    public static boolean isPossible(int[] nums) {
        Map<Integer, Integer> countMap = new HashMap<>();
        Map<Integer, Integer> needMap = new HashMap<>();

        for (int num : nums) {
            countMap.put(num, countMap.getOrDefault(num, 0) + 1);
        }

        for (int num : nums) {
            if (countMap.get(num) == 0) continue;

            if (needMap.getOrDefault(num, 0) > 0) {
                // Greedily append to an existing sequence
                needMap.put(num, needMap.get(num) - 1);
                needMap.put(num + 1, needMap.getOrDefault(num + 1, 0) + 1);
            } else if (countMap.getOrDefault(num + 1, 0) > 0 && countMap.getOrDefault(num + 2, 0) > 0) {
                // Form a new sequence of length 3
                countMap.put(num + 1, countMap.get(num + 1) - 1);
                countMap.put(num + 2, countMap.get(num + 2) - 1);
                needMap.put(num + 3, needMap.getOrDefault(num + 3, 0) + 1);
            } else {
                return false;
            }

            countMap.put(num, countMap.get(num) - 1);
        }

        return true;
    }

    public static void main(String[] args) {
        int[] nums1 = {1, 2, 3, 3, 4, 5};
        System.out.println("Possible 1: " + isPossible(nums1) + " (Expected: true)"); // [1,2,3], [3,4,5]

        int[] nums2 = {1, 2, 3, 3, 4, 4, 5, 5};
        System.out.println("Possible 2: " + isPossible(nums2) + " (Expected: true)");

        int[] nums3 = {1, 2, 3, 4, 4, 5};
        System.out.println("Possible 3: " + isPossible(nums3) + " (Expected: false)");
    }
}
