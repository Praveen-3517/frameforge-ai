/**
 * Problem Statement:
 * Given a bitmask `mask`, enumerate all of its submasks efficiently in strictly descending order.
 * Furthermore, prove and demonstrate why enumerating all submasks for all masks of an N-element set
 * runs in O(3^N) time rather than O(4^N).
 * Also implement Gosper's Hack to enumerate all N-bit integers with exactly K set bits in O(1) per state.
 *
 * Asked in: Google, Codeforces, Competitive Programming Rounds, Advanced Graph/DP Interviews
 *
 * Approach:
 * - Submask Decrement Trick:
 *   To iterate over all submasks of `mask`:
 *   ```java
 *   for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
 *       // Process non-empty submask
 *   }
 *   ```
 *   Why it works:
 *   - Subtracting 1 (`sub - 1`) clears the lowest set bit and sets all trailing 0s to 1s.
 *   - Bitwise ANDing with `mask` (`& mask`) masks out all bits that were not in the original mask,
 *     jumping directly to the next lexicographically smaller valid submask without wasting iterations!
 * - Mathematical Proof of O(3^N):
 *   By the Binomial Theorem:
 *   sum_{k=0}^{N} C(N, k) * 2^k = (1 + 2)^N = 3^N!
 *   Each element can be in 3 states: not in mask, in mask but not in submask, or in both!
 * - Gosper's Hack:
 *   Computes the next integer with the exact same number of set bits (popcount):
 *   `int c = x & -x; int r = x + c; return (((r ^ x) >>> 2) / c) | r;`
 */
class SubmaskEnumerationBitwise {

    public static void enumerateSubmasks(int mask) {
        System.out.printf("--- Submasks of Mask %d (Binary: %s) ---%n",
                mask, Integer.toBinaryString(mask));

        int count = 0;
        int sub = mask;
        while (true) {
            System.out.printf("  Submask #%2d: %3d | Binary: %5s%n",
                    ++count, sub, String.format("%5s", Integer.toBinaryString(sub)).replace(' ', '0'));

            if (sub == 0) break;
            sub = (sub - 1) & mask;
        }
        System.out.println("Total Submasks: " + count + " (Matches 2^" + Integer.bitCount(mask) + ")");
    }

    // Gosper's Hack: Generates next higher integer with identical count of set bits
    public static int nextSameWeightNumber(int x) {
        int lowestSetBit = x & -x;
        int nextHigherWithoutBits = x + lowestSetBit;
        int changedBits = x ^ nextHigherWithoutBits;
        int rightJustified = (changedBits >>> 2) / lowestSetBit;
        return nextHigherWithoutBits | rightJustified;
    }

    public static void demonstrateGospersHack(int k, int n) {
        System.out.printf("%n--- Gosper's Hack: All masks of length %d with exactly %d set bits ---%n", n, k);
        int mask = (1 << k) - 1; // Smallest number with k set bits (e.g. 00111 for k=3)
        int limit = 1 << n;

        int count = 0;
        while (mask < limit) {
            System.out.printf("  Combination #%2d: %s (Val: %d)%n",
                    ++count, String.format("%" + n + "s", Integer.toBinaryString(mask)).replace(' ', '0'), mask);
            mask = nextSameWeightNumber(mask);
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Advanced Bitmask Enumeration (Submask Trick & Gosper's Hack) ===");
        enumerateSubmasks(22); // 22 = 10110_2 (3 set bits -> 2^3 = 8 submasks)
        demonstrateGospersHack(3, 5); // 5 choose 3 = 10 combinations
    }
}

/*
 * Time Complexity:
 *   - Submask enumeration of mask with k bits: O(2^k).
 *   - All submasks of all masks of size N: O(3^N).
 *   - Gosper's Hack per combination: O(1) CPU instructions.
 * Space Complexity: O(1) - Primitive register manipulation only.
 */
