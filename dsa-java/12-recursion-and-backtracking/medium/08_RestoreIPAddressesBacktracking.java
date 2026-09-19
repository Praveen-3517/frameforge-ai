/*
 * Problem Statement:
 * A valid IPv4 address consists of exactly four integers separated by single dots.
 * Each integer is between 0 and 255 (inclusive) and cannot have leading zeros (except '0').
 * Given a string s containing only digits, return all possible valid IPv4 addresses that
 * can be formed by inserting dots in s.
 * (LeetCode 93: Restore IP Addresses)
 * 
 * Example:
 * Input: s = "25525511135"
 * Output: ["255.255.11.135","255.255.111.35"]
 * 
 * Asked in: Amazon, Microsoft, Google, TikTok
 */

import java.util.ArrayList;
import java.util.List;

class RestoreIPAddressesBacktracking {

    public static List<String> restoreIpAddresses(String s) {
        List<String> result = new ArrayList<>();
        if (s.length() < 4 || s.length() > 12) return result;
        backtrack(s, 0, 0, new ArrayList<>(), result);
        return result;
    }

    private static void backtrack(String s, int index, int segmentCount, List<String> currentSegments, List<String> result) {
        if (segmentCount == 4) {
            if (index == s.length()) {
                result.add(String.join(".", currentSegments));
            }
            return;
        }

        // A segment can be 1, 2, or 3 digits long
        for (int len = 1; len <= 3; len++) {
            if (index + len > s.length()) break;

            String part = s.substring(index, index + len);

            // Check leading zero
            if (part.startsWith("0") && part.length() > 1) break;

            // Check value <= 255
            int val = Integer.parseInt(part);
            if (val <= 255) {
                currentSegments.add(part);
                backtrack(s, index + len, segmentCount + 1, currentSegments, result);
                currentSegments.remove(currentSegments.size() - 1); // backtrack
            }
        }
    }

    public static void main(String[] args) {
        String s1 = "25525511135";
        System.out.println("String: \"" + s1 + "\" -> Valid IPs: " + restoreIpAddresses(s1));

        String s2 = "0000";
        System.out.println("String: \"" + s2 + "\" -> Valid IPs: " + restoreIpAddresses(s2));

        String s3 = "101023";
        System.out.println("String: \"" + s3 + "\" -> Valid IPs: " + restoreIpAddresses(s3));
    }
}

/*
 * Time Complexity: O(1) - The search tree has maximum depth 4 and branching factor 3 (3^4 = 81 leaves).
 * Space Complexity: O(1) auxiliary space.
 */
