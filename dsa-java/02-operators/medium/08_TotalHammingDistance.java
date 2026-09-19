/**
 * Problem Statement:
 * Given an integer array `nums`, return the sum of Hamming distances between all
 * the pairs of the integers in `nums`.
 * (LeetCode 477: Total Hamming Distance).
 *
 * Example:
 * nums = [4, 14, 2]
 * 4  = 0100
 * 14 = 1110
 * 2  = 0010
 * Pairs: (4, 14) -> 2, (4, 2) -> 2, (14, 2) -> 2. Total = 6.
 *
 * Asked in: Google, Facebook / Meta, Amazon
 *
 * Approach:
 * - Brute Force Pitfall:
 *   Checking all pairs takes O(N^2 * 32) time. For N = 10,000, N^2 = 100,000,000, causing TLE.
 * - Optimal Bit-Column Contribution (O(32 * N) = O(N)):
 *   Instead of computing distances between pairs of numbers, compute the contribution
 *   of each of the 32 bit columns independently across the entire array!
 *   For bit position `i` (from 0 to 31):
 *     Count how many numbers in `nums` have the i-th bit set to 1 (say `k`).
 *     Then `(n - k)` numbers have the i-th bit set to 0.
 *     Any pair formed by one number with bit=1 and another with bit=0 will differ at bit `i`.
 *     Therefore, bit `i` contributes exactly: `k * (n - k)` to the total Hamming distance!
 *   Summing this contribution across all 32 bits yields the exact answer in O(32 * N) time.
 */
class TotalHammingDistance {

    // Optimal Bit Contribution Approach: O(32 * N)
    public static int totalHammingDistance(int[] nums) {
        int total = 0;
        int n = nums.length;

        for (int bit = 0; bit < 32; bit++) {
            int countOnes = 0;
            for (int num : nums) {
                countOnes += (num >>> bit) & 1;
            }
            int countZeros = n - countOnes;
            total += countOnes * countZeros;
        }

        return total;
    }

    // Brute Force for Verification: O(N^2)
    public static int totalHammingDistanceBrute(int[] nums) {
        int total = 0;
        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                total += Integer.bitCount(nums[i] ^ nums[j]);
            }
        }
        return total;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 477: Total Hamming Distance (O(N) Bit Column) ===");

        int[][] testArrays = {
            { 4, 14, 2 },
            { 4, 14, 4 },
            { 1, 2, 3, 4, 5 },
            { 0, 0, 0, 0 },
            { 1000000, 2000000, 3000000, 4000000 }
        };

        for (int[] arr : testArrays) {
            int optimal = totalHammingDistance(arr);
            int brute = totalHammingDistanceBrute(arr);
            System.out.printf("Array: %s%n ==> Total Distance: %d (Matches Brute: %s)%n%n",
                    java.util.Arrays.toString(arr), optimal, (optimal == brute) ? "YES" : "NO");
        }
    }
}

/*
 * Time Complexity: O(32 * N) = O(N) - Single pass over 32 bit columns.
 * Space Complexity: O(1) - Constant stack registers.
 */
