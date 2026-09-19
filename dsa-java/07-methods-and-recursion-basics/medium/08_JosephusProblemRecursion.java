/*
 * Problem Statement:
 * There are n people standing in a circle numbered from 1 to n.
 * Starting from person 1, counting begins and every k-th person is eliminated until only
 * one person remains. Return the 1-based position of the survivor.
 * 
 * Also known as LeetCode 1823: Find the Winner of the Circular Game.
 * 
 * Example 1:
 * Input: n = 5, k = 2
 * Output: 3
 * 
 * Example 2:
 * Input: n = 6, k = 5
 * Output: 1
 * 
 * Asked in: Amazon, Goldman Sachs, Cisco, Walmart
 */

class JosephusProblemRecursion {

    /**
     * Approach:
     * Recursive relation for 0-indexed position:
     * J(1, k) = 0
     * J(n, k) = (J(n - 1, k) + k) % n
     * 
     * Once survivor position in 0-indexed is found, convert to 1-based by adding 1.
     */
    public static int findTheWinner(int n, int k) {
        return josephusZeroIndexed(n, k) + 1;
    }

    private static int josephusZeroIndexed(int n, int k) {
        if (n == 1) return 0;
        return (josephusZeroIndexed(n - 1, k) + k) % n;
    }

    // Iterative bottom-up equivalent to avoid stack overflow for huge N
    public static int josephusIterative(int n, int k) {
        int survivor = 0;
        for (int i = 2; i <= n; i++) {
            survivor = (survivor + k) % i;
        }
        return survivor + 1;
    }

    public static void main(String[] args) {
        int[][] tests = {
            {5, 2},
            {6, 5},
            {7, 3},
            {10, 3},
            {41, 2} // Classic historical Josephus problem instance
        };

        System.out.println("--- Josephus Problem Solver ---");
        for (int[] t : tests) {
            int n = t[0];
            int k = t[1];
            int resRec = findTheWinner(n, k);
            int resIter = josephusIterative(n, k);
            System.out.printf("n = %2d, k = %2d -> Survivor: %2d (Iterative: %2d)%n",
                    n, k, resRec, resIter);
        }
    }
}

/*
 * Time Complexity: O(n) - One recursive call per eliminated person.
 * Space Complexity: O(n) - Call stack depth equals n.
 */
