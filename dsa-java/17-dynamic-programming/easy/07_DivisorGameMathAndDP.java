/**
 * Problem: Divisor Game (LeetCode 1025)
 * Asked in: Google, Amazon
 * 
 * Alice and Bob take turns playing a game, with Alice starting first.
 * Initially, there is a number n on the chalkboard. On each player's turn, that player:
 * 1. Chooses any x with 0 < x < n and n % x == 0.
 * 2. Replaces the number n with n - x.
 * Also, if a player cannot make a move, they lose the game.
 * Return true if Alice wins assuming both play optimally.
 * 
 * Approach:
 * 1. Dynamic Programming:
 *    dp[i] = true if player whose turn it is wins with number i.
 *    For each divisor x of i: if !dp[i - x], then dp[i] = true.
 * 2. Mathematical Insight:
 *    If n is even, Alice chooses x = 1, giving Bob an odd number.
 *    Any divisor of an odd number is odd; odd - odd = even.
 *    Bob must always hand Alice back an even number.
 *    Eventually Alice hands Bob 1 (no moves left).
 *    Thus, Alice wins if and only if n is even!
 * 
 * Time Complexity: O(N * sqrt(N)) for DP, O(1) for math.
 * Space Complexity: O(N) for DP, O(1) for math.
 */
class DivisorGameMathAndDP {

    public static boolean divisorGameDP(int n) {
        boolean[] dp = new boolean[n + 1];
        // dp[1] is false (no move available)

        for (int i = 2; i <= n; i++) {
            for (int x = 1; x * x <= i; x++) {
                if (i % x == 0) {
                    if (!dp[i - x] || !dp[i - (i / x)]) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }

        return dp[n];
    }

    public static boolean divisorGameMath(int n) {
        return n % 2 == 0;
    }

    public static void main(String[] args) {
        System.out.println("n = 2: " + divisorGameDP(2) + " (Expected: true)");
        System.out.println("n = 3: " + divisorGameDP(3) + " (Expected: false)");
        System.out.println("n = 4: " + divisorGameMath(4) + " (Expected: true)");
    }
}
