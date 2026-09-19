/**
 * Problem: Minimum Number of K Consecutive Bit Flips (LeetCode 995)
 * Category: Sliding Window | Hard
 * Asked in: Google
 * 
 * You are given a binary array nums and an integer k.
 * A k-bit flip is choosing a subarray of length k from nums and simultaneously
 * changing every 0 in the subarray to 1, and every 1 in the subarray to 0.
 * Return the minimum number of k-bit flips required so that there is no 0 in the array.
 * Return -1 if it is not possible.
 * 
 * Approach - Sliding Window Flip Count (XOR Trick):
 * Instead of actually flipping, maintain a variable `flipped` tracking how many times
 * the current index has been flipped (mod 2).
 * Use a difference array (or deque): `flipChange[i] = 1` means a flip started at i expires at i+k.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N) for the flipChange array.
 */
class MinimumKConsecutiveBitFlips {

    public static int minKBitFlips(int[] nums, int k) {
        int n = nums.length;
        int[] flipChange = new int[n + 1]; // flipChange[i] = 1 means a flip started at i-k ends here
        int totalFlips = 0;
        int currentFlips = 0; // number of active flips at position i (mod 2)

        for (int i = 0; i < n; i++) {
            currentFlips ^= flipChange[i]; // expire flips that no longer cover index i

            // Effective value at index i = nums[i] XOR (currentFlips % 2)
            if (nums[i] == currentFlips % 2) {
                // need to flip: nums[i] ^ 1 flipped state should be 1
                // effective bit after current flips: nums[i] XOR currentFlips
                // We need it to be 1, so if nums[i] ^ (currentFlips & 1) == 0, flip
            }

            int effectiveBit = nums[i] ^ (currentFlips & 1);
            if (effectiveBit == 0) {
                // We need to flip starting at i
                if (i + k > n) return -1; // can't flip, goes out of bounds
                totalFlips++;
                currentFlips ^= 1;
                if (i + k <= n) flipChange[i + k] ^= 1; // flip expires after index i+k-1
            }
        }

        return totalFlips;
    }

    public static void main(String[] args) {
        System.out.println(minKBitFlips(new int[]{0, 1, 0}, 1) + " (Expected: 2)");
        // Flip index 0 and index 2
        System.out.println(minKBitFlips(new int[]{1, 1, 0}, 2) + " (Expected: -1)");
        // Cannot make all 1s
        System.out.println(minKBitFlips(new int[]{0, 0, 0, 1, 0, 1, 1, 0}, 3) + " (Expected: 3)");
    }
}
