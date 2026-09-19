/*
 * Problem Statement:
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * Return all possible palindrome partitioning of s.
 * (LeetCode 131: Palindrome Partitioning)
 * 
 * Example:
 * Input: s = "aab"
 * Output: [["a","a","b"],["aa","b"]]
 * 
 * Asked in: Bloomberg, Amazon, Google, Facebook/Meta
 */

import java.util.ArrayList;
import java.util.List;

class PalindromePartitioningAllCuts {

    public static List<List<String>> partition(String s) {
        List<List<String>> result = new ArrayList<>();
        backtrack(s, 0, new ArrayList<>(), result);
        return result;
    }

    private static void backtrack(String s, int start, List<String> current, List<List<String>> result) {
        if (start == s.length()) {
            result.add(new ArrayList<>(current));
            return;
        }

        for (int end = start; end < s.length(); end++) {
            if (isPalindrome(s, start, end)) {
                current.add(s.substring(start, end + 1));
                backtrack(s, end + 1, current, result);
                current.remove(current.size() - 1); // backtrack
            }
        }
    }

    private static boolean isPalindrome(String s, int l, int r) {
        while (l < r) {
            if (s.charAt(l++) != s.charAt(r--)) return false;
        }
        return true;
    }

    public static void main(String[] args) {
        String s = "aab";
        List<List<String>> partitions = partition(s);

        System.out.println("String: \"" + s + "\"");
        System.out.println("Palindrome Partitions (" + partitions.size() + "): " + partitions);
    }
}

/*
 * Time Complexity: O(N * 2^N) - In worst case (e.g. "aaaa"), 2^(N-1) partitions, each validated in O(N).
 * Space Complexity: O(N) recursion stack.
 */
