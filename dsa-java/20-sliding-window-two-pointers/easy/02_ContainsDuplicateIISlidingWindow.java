import java.util.HashMap;
import java.util.Map;

/**
 * Problem: Contains Duplicate II (LeetCode 219)
 * Category: Fixed-Size Sliding Window | Easy
 * Asked in: Amazon, Bloomberg, Google
 * 
 * Given an integer array nums and an integer k, return true if there are two distinct
 * indices i and j in the array such that nums[i] == nums[j] and |i - j| <= k.
 * 
 * Approach - Sliding Window with HashMap:
 * Maintain a window of the last k elements using a HashMap (value -> index).
 * For each element, check if it already exists in the window.
 * If yes, indices differ by at most k: return true.
 * Update the map entry (index) for the current element.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(min(N, K)) for the map.
 */
class ContainsDuplicateIISlidingWindow {

    public static boolean containsNearbyDuplicate(int[] nums, int k) {
        Map<Integer, Integer> lastSeen = new HashMap<>();

        for (int i = 0; i < nums.length; i++) {
            if (lastSeen.containsKey(nums[i]) && i - lastSeen.get(nums[i]) <= k) {
                return true;
            }
            lastSeen.put(nums[i], i);
        }

        return false;
    }

    public static void main(String[] args) {
        System.out.println(containsNearbyDuplicate(new int[]{1, 2, 3, 1}, 3) + " (Expected: true)");
        System.out.println(containsNearbyDuplicate(new int[]{1, 0, 1, 1}, 1) + " (Expected: true)");
        System.out.println(containsNearbyDuplicate(new int[]{1, 2, 3, 1, 2, 3}, 2) + " (Expected: false)");
    }
}
