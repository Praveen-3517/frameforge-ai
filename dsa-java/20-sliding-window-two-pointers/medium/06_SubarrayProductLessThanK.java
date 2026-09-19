/**
 * Problem: Subarray Product Less Than K (LeetCode 713)
 * Category: Variable Sliding Window | Medium
 * Asked in: Amazon, Google, Facebook, Bloomberg
 * 
 * Given an array of integers nums and an integer k, return the number of contiguous
 * subarrays where the product of all the elements in the subarray is strictly less than k.
 * 
 * Approach - Variable Sliding Window:
 * Maintain window product. Expand right, multiply in nums[right].
 * While product >= k, divide out nums[left] and shrink left.
 * For each valid window of size (right - left + 1), there are exactly
 * (right - left + 1) subarrays ending at right (all right-aligned windows of various sizes).
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class SubarrayProductLessThanK {

    public static int numSubarrayProductLessThanK(int[] nums, int k) {
        if (k <= 1) return 0; // nothing can be < 1 with positive integers

        int left = 0;
        int product = 1;
        int count = 0;

        for (int right = 0; right < nums.length; right++) {
            product *= nums[right];

            while (product >= k) {
                product /= nums[left++];
            }

            // Subarrays ending at right with left..right window all valid
            count += right - left + 1;
        }

        return count;
    }

    public static void main(String[] args) {
        System.out.println(numSubarrayProductLessThanK(new int[]{10, 5, 2, 6}, 100) + " (Expected: 8)");
        // [10],[5],[2],[6],[10,5],[5,2],[2,6],[5,2,6] all < 100
        System.out.println(numSubarrayProductLessThanK(new int[]{1, 2, 3}, 0) + " (Expected: 0)");
    }
}
