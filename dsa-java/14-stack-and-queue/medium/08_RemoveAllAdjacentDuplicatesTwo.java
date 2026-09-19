/*
 * Problem Statement:
 * You are given a string s and an integer k, a k duplicate removal consists of choosing
 * k adjacent and equal letters from s and removing them, causing the left and the right side
 * of the deleted substring to concatenate together.
 * We repeatedly make k duplicate removals on s until we no longer can.
 * Return the final string after all such duplicate removals have been made.
 * (LeetCode 1209: Remove All Adjacent Duplicates in String II)
 * 
 * Example:
 * Input: s = "deeedbbcccbdaa", k = 3
 * Output: "aa"
 * 
 * Asked in: Bloomberg, Amazon, Goldman Sachs
 */

import java.util.ArrayDeque;
import java.util.Deque;

class RemoveAllAdjacentDuplicatesTwo {

    static class CharFreq {
        char ch;
        int count;
        CharFreq(char ch, int count) { this.ch = ch; this.count = count; }
    }

    public static String removeDuplicates(String s, int k) {
        Deque<CharFreq> stack = new ArrayDeque<>();

        for (char c : s.toCharArray()) {
            if (!stack.isEmpty() && stack.peek().ch == c) {
                stack.peek().count++;
                if (stack.peek().count == k) {
                    stack.pop(); // Remove all k duplicates
                }
            } else {
                stack.push(new CharFreq(c, 1));
            }
        }

        StringBuilder sb = new StringBuilder();
        while (!stack.isEmpty()) {
            CharFreq entry = stack.pollLast(); // From bottom up
            for (int i = 0; i < entry.count; i++) {
                sb.append(entry.ch);
            }
        }

        return sb.toString();
    }

    public static void main(String[] args) {
        String s1 = "abcd", k1 = "2";
        System.out.println("s = \"abcd\", k = 2 -> Result: \"" + removeDuplicates(s1, 2) + "\"");

        String s2 = "deeedbbcccbdaa";
        System.out.println("s = \"deeedbbcccbdaa\", k = 3 -> Result: \"" + removeDuplicates(s2, 3) + "\" (Expected: \"aa\")");

        String s3 = "pbbcggttciiippooaais";
        System.out.println("s = \"pbbcggttciiippooaais\", k = 2 -> Result: \"" + removeDuplicates(s3, 2) + "\" (Expected: \"ps\")");
    }
}

/*
 * Time Complexity: O(N) single pass through the string.
 * Space Complexity: O(N) stack to store characters and running counts.
 */
