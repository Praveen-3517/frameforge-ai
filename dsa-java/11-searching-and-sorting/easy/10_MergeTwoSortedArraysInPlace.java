/*
 * Problem Statement:
 * You are given two integer arrays nums1 and nums2, sorted in non-decreasing order,
 * and two integers m and n, representing the number of elements in nums1 and nums2 respectively.
 * Merge nums1 and nums2 into a single array sorted in non-decreasing order.
 * The final sorted array should not be returned by the function, but instead be stored inside
 * the array nums1. To accommodate this, nums1 has a length of m + n.
 * (LeetCode 88: Merge Sorted Array)
 * 
 * Example:
 * Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
 * Output: [1,2,2,3,5,6]
 * 
 * Asked in: Facebook/Meta, Microsoft, Amazon, Google, Bloomberg
 */

import java.util.Arrays;

class MergeTwoSortedArraysInPlace {

    /**
     * Approach:
     * Three-Pointer Merging from Backward:
     * Start from the tail of nums1 (index m + n - 1):
     * Place the larger of nums1[p1] and nums2[p2] at nums1[p].
     * Avoids overwriting existing elements in nums1 without requiring an auxiliary array!
     */
    public static void merge(int[] nums1, int m, int[] nums2, int n) {
        int p1 = m - 1;
        int p2 = n - 1;
        int p = m + n - 1;

        while (p1 >= 0 && p2 >= 0) {
            if (nums1[p1] > nums2[p2]) {
                nums1[p] = nums1[p1];
                p1--;
            } else {
                nums1[p] = nums2[p2];
                p2--;
            }
            p--;
        }

        // Fill remaining elements of nums2 if any
        while (p2 >= 0) {
            nums1[p] = nums2[p2];
            p2--;
            p--;
        }
    }

    public static void main(String[] args) {
        int[] nums1 = {1, 2, 3, 0, 0, 0};
        int m = 3;
        int[] nums2 = {2, 5, 6};
        int n = 3;

        System.out.println("nums1: " + Arrays.toString(nums1) + ", m = " + m);
        System.out.println("nums2: " + Arrays.toString(nums2) + ", n = " + n);

        merge(nums1, m, nums2, n);
        System.out.println("Merged nums1: " + Arrays.toString(nums1));
    }
}

/*
 * Time Complexity: O(m + n) - Single pass filling buffer from back.
 * Space Complexity: O(1) in-place merging.
 */
