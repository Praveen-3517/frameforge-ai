import java.util.Arrays;

/**
 * Problem Statement:
 * Given an integer array `nums`, move all 0's to the end of it while maintaining the relative
 * order of the non-zero elements.
 * You must do this in-place without making a copy of the array.
 * (LeetCode 283: Move Zeroes).
 *
 * Example:
 * nums = [0, 1, 0, 3, 12] -> Output: [1, 3, 12, 0, 0]
 *
 * Asked in: Facebook / Meta, Bloomberg, Amazon, Apple, Microsoft
 *
 * Approach:
 * - Snowball / Two-Pointer Swap In-Place:
 *   - Pointer `insertPos` tracks the destination for the next non-zero element.
 *   - For each element `nums[i]`:
 *     If `nums[i] != 0`:
 *       If `i != insertPos`:
 *         Swap `nums[insertPos]` and `nums[i]`.
 *       `insertPos++;`
 *   - This simultaneously shifts non-zeros forward and rolls zeroes backward in a single pass!
 */
class MoveZeroesToEnd {

    public static void moveZeroes(int[] nums) {
        if (nums == null || nums.length <= 1) return;

        int insertPos = 0;

        for (int i = 0; i < nums.length; i++) {
            if (nums[i] != 0) {
                if (i != insertPos) {
                    int temp = nums[insertPos];
                    nums[insertPos] = nums[i];
                    nums[i] = temp;
                }
                insertPos++;
            }
        }
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 283: Move Zeroes to End In-Place ===");

        int[][] testCases = {
            { 0, 1, 0, 3, 12 },
            { 0, 0, 1 },
            { 1, 2, 3 },
            { 0, 0, 0 }
        };

        for (int[] arr : testCases) {
            int[] original = arr.clone();
            moveZeroes(arr);
            System.out.printf("Original: %-18s ==> Result: %s%n",
                    Arrays.toString(original), Arrays.toString(arr));
        }
    }
}

/*
 * Time Complexity: O(N) - Single pass through the array.
 * Space Complexity: O(1) - Constant auxiliary space.
 */
