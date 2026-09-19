/**
 * Problem: Decode Ways (LeetCode 91)
 * Asked in: Facebook, Amazon, Google, Microsoft, Uber
 * 
 * A message containing letters from A-Z can be encoded into numbers using the mapping:
 * 'A' -> "1", 'B' -> "2", ..., 'Z' -> "26".
 * Given a string s containing only digits, return the number of ways to decode it.
 * 
 * Approach:
 * 1D DP with O(1) Space Optimization:
 * At index i:
 * - Single digit: s[i-1] != '0' contributes dp[i - 1].
 * - Two digits: s[i-2..i-1] between "10" and "26" contributes dp[i - 2].
 * dp[i] = ways1 + ways2.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class DecodeWaysDP {

    public static int numDecodings(String s) {
        if (s == null || s.length() == 0 || s.charAt(0) == '0') return 0;

        int n = s.length();
        int prev2 = 1; // dp[0]
        int prev1 = 1; // dp[1]

        for (int i = 2; i <= n; i++) {
            int curr = 0;
            int oneDigit = s.charAt(i - 1) - '0';
            int twoDigits = Integer.parseInt(s.substring(i - 2, i));

            if (oneDigit >= 1 && oneDigit <= 9) {
                curr += prev1;
            }
            if (twoDigits >= 10 && twoDigits <= 26) {
                curr += prev2;
            }

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    public static void main(String[] args) {
        System.out.println("Ways for '12': " + numDecodings("12") + " (Expected: 2)"); // "AB" or "L"
        System.out.println("Ways for '226': " + numDecodings("226") + " (Expected: 3)"); // "BZ", "VF", "BBF"
        System.out.println("Ways for '06': " + numDecodings("06") + " (Expected: 0)");
    }
}
