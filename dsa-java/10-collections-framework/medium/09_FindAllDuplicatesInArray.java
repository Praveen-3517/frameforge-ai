/*
 * Problem Statement:
 * Given an integer array nums of length n where all the integers of nums are in the
 * range [1, n] and each integer appears once or twice, return an array of all the
 * integers that appears twice.
 * Show:
 * 1. HashSet approach (O(N) time, O(N) space).
 * 2. In-place index negation approach (O(N) time, O(1) auxiliary space).
 * 
 * Example:
 * Input: nums = [4,3,2,7,8,2,3,1]
 * Output: [2, 3]
 * 
 * Asked in: Amazon, Microsoft, Pocket Gems, Facebook/Meta
 */

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

class FindAllDuplicatesInArray {

    // Approach 1: HashSet Detection
    public static List<Integer> findDuplicatesHashSet(int[] nums) {
        List<Integer> result = new ArrayList<>();
        Set<Integer> seen = new HashSet<>();

        for (int num : nums) {
            if (seen.contains(num)) {
                result.add(num);
            } else {
                seen.add(num);
            }
        }
        return result;
    }

    // Approach 2: In-place Index Negation (O(1) extra space)
    public static List<Integer> findDuplicatesInPlace(int[] nums) {
        List<Integer> result = new ArrayList<>();

        for (int i = 0; i < nums.length; i++) {
            int val = Math.abs(nums[i]);
            int index = val - 1;

            if (nums[index] < 0) {
                // Already visited, so val is a duplicate!
                result.add(val);
            } else {
                // Mark as visited by negating
                nums[index] = -nums[index];
            }
        }

        // Restore original array values
        for (int i = 0; i < nums.length; i++) {
            nums[i] = Math.abs(nums[i]);
        }

        return result;
    }

    public static void main(String[] args) {
        int[] nums = {4, 3, 2, 7, 8, 2, 3, 1};

        System.out.println("--- Find All Duplicates in Array ---");
        System.out.println("HashSet approach:  " + findDuplicatesHashSet(nums));
        System.out.println("In-place approach: " + findDuplicatesInPlace(nums));
    }
}

/*
 * Time Complexity: O(N) linear scan for both methods.
 * Space Complexity: HashSet: O(N), In-place: O(1) auxiliary space.
 */
