import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Problem: 3Sum (LeetCode 15)
 * Category: Two Pointers | Medium
 * Asked in: Amazon, Facebook, Google, Apple, Microsoft, Bloomberg
 * 
 * Given an integer array nums, return all triplets [nums[i], nums[j], nums[k]] such that
 * i != j, i != k, j != k, and nums[i] + nums[j] + nums[k] == 0.
 * The solution set must not contain duplicate triplets.
 * 
 * Approach - Sort + Two Pointer for each pivot:
 * 1. Sort the array.
 * 2. For each index i (pivot), use two pointers left=i+1, right=n-1 to find pairs
 *    summing to -nums[i].
 * 3. Skip duplicate pivots and duplicate pointer values to avoid redundant triplets.
 * 
 * Time Complexity: O(N²)
 * Space Complexity: O(1) auxiliary (excluding output list).
 */
class ThreeSumSortedTwoPointer {

    public static List<List<Integer>> threeSum(int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> result = new ArrayList<>();

        for (int i = 0; i < nums.length - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // skip duplicate pivot

            int left = i + 1;
            int right = nums.length - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    result.add(Arrays.asList(nums[i], nums[left], nums[right]));
                    while (left < right && nums[left] == nums[left + 1]) left++;   // skip dup
                    while (left < right && nums[right] == nums[right - 1]) right--; // skip dup
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        return result;
    }

    public static void main(String[] args) {
        System.out.println(threeSum(new int[]{-1, 0, 1, 2, -1, -4}));
        // Expected: [[-1,-1,2],[-1,0,1]]
        System.out.println(threeSum(new int[]{0, 1, 1}));
        // Expected: []
        System.out.println(threeSum(new int[]{0, 0, 0}));
        // Expected: [[0,0,0]]
    }
}
