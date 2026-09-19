/**
 * Problem Statement:
 * Given two sorted arrays `nums1` and `nums2` of size `m` and `n` respectively,
 * return the median of the two sorted arrays.
 * The overall run time complexity must be O(log(min(m, n))).
 * (LeetCode 4: Median of Two Sorted Arrays - Hard).
 *
 * Example:
 * nums1 = [1, 3], nums2 = [2] -> Median: 2.0
 * nums1 = [1, 2], nums2 = [3, 4] -> Median: (2 + 3) / 2 = 2.5
 *
 * Asked in: Google, Amazon, Microsoft, Apple, Goldman Sachs
 *
 * Approach:
 * - Binary Search Partitioning on the Shorter Array (O(log(min(m, n)))):
 *   1. Always perform binary search on the shorter array (if `m > n`, swap arrays).
 *   2. We want to partition both arrays into two halves (Left Half and Right Half) such that:
 *      - Total elements on left = `(m + n + 1) / 2`.
 *      - Every element in Left Half <= Every element in Right Half.
 *   3. Partition `partX` in `nums1` and `partY = (m + n + 1) / 2 - partX` in `nums2`:
 *      - `maxLeftX  = (partX == 0) ? -INF : nums1[partX - 1]`
 *      - `minRightX = (partX == m) ? +INF : nums1[partX]`
 *      - `maxLeftY  = (partY == 0) ? -INF : nums2[partY - 1]`
 *      - `minRightY = (partY == n) ? +INF : nums2[partY]`
 *   4. Valid Partition Condition:
 *      `maxLeftX <= minRightY && maxLeftY <= minRightX`
 *      - If total length is odd: `median = Math.max(maxLeftX, maxLeftY)`
 *      - If total length is even: `median = (Math.max(maxLeftX, maxLeftY) + Math.min(minRightX, minRightY)) / 2.0`
 *   5. Adjust Binary Search:
 *      - If `maxLeftX > minRightY`: `high = partX - 1` (too far right in nums1)
 *      - Else: `low = partX + 1` (too far left in nums1)
 */
class MedianOfTwoSortedArrays {

    public static double findMedianSortedArrays(int[] nums1, int[] nums2) {
        // Guarantee nums1 is the shorter array
        if (nums1.length > nums2.length) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = nums1.length;
        int n = nums2.length;
        int low = 0;
        int high = m;

        while (low <= high) {
            int partX = (low + high) / 2;
            int partY = (m + n + 1) / 2 - partX;

            int maxLeftX = (partX == 0) ? Integer.MIN_VALUE : nums1[partX - 1];
            int minRightX = (partX == m) ? Integer.MAX_VALUE : nums1[partX];

            int maxLeftY = (partY == 0) ? Integer.MIN_VALUE : nums2[partY - 1];
            int minRightY = (partY == n) ? Integer.MAX_VALUE : nums2[partY];

            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                // Correct partition reached
                if (((m + n) & 1) == 1) { // Odd total length
                    return Math.max(maxLeftX, maxLeftY);
                } else { // Even total length
                    return (Math.max(maxLeftX, maxLeftY) + Math.min(minRightX, minRightY)) / 2.0;
                }
            } else if (maxLeftX > minRightY) {
                high = partX - 1; // Move left in nums1
            } else {
                low = partX + 1;  // Move right in nums1
            }
        }

        throw new IllegalArgumentException("Input arrays are not sorted.");
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 4: Median of Two Sorted Arrays (Binary Partition) ===");

        int[] a1 = { 1, 3 };
        int[] b1 = { 2 };
        System.out.printf("Arrays: %s and %s ==> Median: %.1f%n",
                java.util.Arrays.toString(a1), java.util.Arrays.toString(b1), findMedianSortedArrays(a1, b1));

        int[] a2 = { 1, 2 };
        int[] b2 = { 3, 4 };
        System.out.printf("Arrays: %s and %s ==> Median: %.1f%n",
                java.util.Arrays.toString(a2), java.util.Arrays.toString(b2), findMedianSortedArrays(a2, b2));

        int[] a3 = { 0, 0 };
        int[] b3 = { 0, 0 };
        System.out.printf("Arrays: %s and %s ==> Median: %.1f%n",
                java.util.Arrays.toString(a3), java.util.Arrays.toString(b3), findMedianSortedArrays(a3, b3));
    }
}

/*
 * Time Complexity: O(log(min(M, N))) - Binary search on the shorter array.
 * Space Complexity: O(1) - Constant stack registers.
 */
