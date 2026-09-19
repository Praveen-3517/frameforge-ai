/*
 * Problem Statement:
 * Given a string s, print all of its subsequences (including the empty string).
 * A subsequence is a sequence that can be derived from another sequence by deleting
 * some or no elements without changing the order of the remaining elements.
 * 
 * Example:
 * Input: "abc"
 * Output: ["", "a", "b", "c", "ab", "ac", "bc", "abc"]
 * 
 * Asked in: Amazon, Microsoft, Infosys, Cognizant
 */

import java.util.ArrayList;
import java.util.List;

class PrintAllSubsequencesString {

    public static List<String> generateSubsequences(String s) {
        List<String> result = new ArrayList<>();
        helper(s, 0, new StringBuilder(), result);
        return result;
    }

    private static void helper(String s, int index, StringBuilder current, List<String> result) {
        if (index == s.length()) {
            result.add(current.toString());
            return;
        }

        // Choice 1: Include char at index
        current.append(s.charAt(index));
        helper(s, index + 1, current, result);
        current.deleteCharAt(current.length() - 1); // backtrack

        // Choice 2: Exclude char at index
        helper(s, index + 1, current, result);
    }

    public static void main(String[] args) {
        String s = "abc";
        List<String> subs = generateSubsequences(s);

        System.out.println("Subsequences of \"" + s + "\" (" + subs.size() + "):");
        for (String sub : subs) {
            System.out.println("  \"" + sub + "\"");
        }
    }
}

/*
 * Time Complexity: O(2^N * N) - 2^N subsequences, each takes O(N) to build.
 * Space Complexity: O(N) recursion stack depth.
 */
