/**
 * Problem Statement:
 * Write a function to find the longest common prefix string amongst an array of strings.
 * If there is no common prefix, return an empty string "".
 * (LeetCode 14: Longest Common Prefix).
 *
 * Example:
 * strs = ["flower","flow","flight"] -> "fl"
 * strs = ["dog","racecar","car"]    -> ""
 *
 * Asked in: Google, Apple, Amazon, Adobe
 *
 * Approach:
 * - Horizontal Scanning:
 *   Initialize `prefix = strs[0]`.
 *   Iterate through each remaining string `strs[i]`:
 *   - While `strs[i]` does not start with `prefix` (`strs[i].indexOf(prefix) != 0`):
 *     Truncate the last character from `prefix`: `prefix = prefix.substring(0, prefix.length() - 1)`.
 *     If `prefix` becomes empty, return `""` immediately!
 *   - Return `prefix`.
 */
class LongestCommonPrefixHorizontal {

    public static String longestCommonPrefix(String[] strs) {
        if (strs == null || strs.length == 0) return "";

        String prefix = strs[0];

        for (int i = 1; i < strs.length; i++) {
            while (strs[i].indexOf(prefix) != 0) {
                prefix = prefix.substring(0, prefix.length() - 1);
                if (prefix.isEmpty()) {
                    return "";
                }
            }
        }

        return prefix;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 14: Longest Common Prefix (Horizontal Scanning) ===");

        String[][] testArrays = {
            { "flower", "flow", "flight" },
            { "dog", "racecar", "car" },
            { "interspecies", "interstellar", "interstate" },
            { "throne", "throne" }
        };

        for (String[] arr : testArrays) {
            String lcp = longestCommonPrefix(arr);
            System.out.printf("Strings: %-42s ==> Prefix: \"%s\"%n",
                    java.util.Arrays.toString(arr), lcp);
        }
    }
}

/*
 * Time Complexity: O(S) where S is the sum of all characters in all strings.
 * Space Complexity: O(1) - Constant auxiliary space.
 */
