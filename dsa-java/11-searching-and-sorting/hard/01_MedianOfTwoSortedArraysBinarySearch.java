/*
 * Problem Statement:
 * Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median
 * of the two sorted arrays.
 * The overall run time complexity should be O(log (m+n)) or O(log(min(m, n))).
 * (LeetCode 4: Median of Two Sorted Arrays)
 * 
 * Example 1:
 * Input: nums1 = [1,3], nums2 = [2]
 * Output: 2.00000
 * 
 * Example 2:
 * Input: nums1 = [1,2], nums2 = [3,4]
 * Output: 2.50000
 * 
 * Asked in: Google, Amazon, Microsoft, Apple, Goldman Sachs
 */

class MedianOfTwoSortedArraysBinarySearch {

    /**
     * Approach:
     * Binary Search on Partitions:
     * - Ensure nums1 is the shorter array (m <= n) to guarantee O(log(min(m, n))).
     * - Partition nums1 at cut1 and nums2 at cut2 such that:
     *   cut1 + cut2 = (m + n + 1) / 2
     * - Let:
     *   L1 = nums1[cut1 - 1], R1 = nums1[cut1]
     *   L2 = nums2[cut2 - 1], R2 = nums2[cut2]
     * - If L1 <= R2 and L2 <= R1, valid partition found!
     *   - If (m + n) is odd: median = max(L1, L2)
     *   - If (m + n) is even: median = (max(L1, L2) + min(R1, R2)) / 2.0
     * - If L1 > R2: cut1 too far right, search left.
     * - Else: cut1 too far left, search right.
     */
    public static double findMedianSortedArrays(int[] nums1, int[] nums2) {
        if (nums1.length > nums2.length) {
            return findMedianSortedArrays(nums2, nums1); // Ensure nums1 is smaller
        }

        int m = nums1.length;
        int n = nums2.length;
        int low = 0;
        int high = m;

        while (low <= high) {
            int cut1 = low + (high - low) / 2;
            int cut2 = (m + n + 1) / 2 - cut1;

            int l1 = (cut1 == 0) ? Integer.MIN_VALUE : nums1[cut1 - 1];
            int r1 = (cut1 == m) ? Integer.MAX_VALUE : nums1[cut1];

            int l2 = (cut2 == 0) ? Integer.MIN_VALUE : nums2[cut2 - 1];
            int r2 = (cut2 == n) ? Integer.MAX_VALUE : nums2[cut2];

            if (l1 <= r2 && l2 <= r1) {
                // Correct partition
                if ((m + n) % 2 == 0) {
                    return (Math.max(l1, l2) + Math.min(r1, r2)) / 2.0;
                } else {
                    return Math.max(l1, l2);
                }
            } else if (l1 > r2) {
                high = cut1 - 1;
            } else {
                low = cut1 + 1;
            }
        }

        return 0.0;
    }

    public static void main(String[] args) {
        int[] a1 = {1, 3};
        int[] b1 = {2};
        System.out.printf("nums1: [1, 3], nums2: [2] -> Median: %.2f%n", findMedianSortedArrays(a1, b1));

        int[] a2 = {1, 2};
        int[] b2 = {3, 4};
        System.out.printf("nums1: [1, 2], nums2: [3, 4] -> Median: %.2f%n", findMedianSortedArrays(a2, b2));
    }
}

/*
 * Time Complexity: O(log(min(m, n))) - Binary search on smaller array.
 * Space Complexity: O(1) auxiliary space.
 */
