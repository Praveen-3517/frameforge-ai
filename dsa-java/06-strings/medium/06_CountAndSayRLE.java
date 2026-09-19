/**
 * Problem Statement:
 * The count-and-say sequence is a sequence of digit strings defined by the recurrence:
 *   countAndSay(1) = "1"
 *   countAndSay(n) is the Run-Length Encoding (RLE) of countAndSay(n - 1).
 * Given a positive integer `n`, return the nth term of the count-and-say sequence.
 * (LeetCode 38: Count and Say).
 *
 * Example:
 * n = 1: "1"
 * n = 2: "11"     (one 1)
 * n = 3: "21"     (two 1s)
 * n = 4: "1211"   (one 2, one 1)
 * n = 5: "111221" (one 1, one 2, two 1s)
 *
 * Asked in: Facebook / Meta, Google, Amazon, Microsoft
 *
 * Approach:
 * - Iterative Run-Length Encoding Loop:
 *   Start with `curr = "1"`.
 *   Repeat n - 1 times:
 *   - Use `StringBuilder next = new StringBuilder()`.
 *   - Traverse `curr`:
 *     Group identical consecutive characters `curr.charAt(i)`:
 *     Count how many times it repeats consecutively (`count`).
 *     Append `count` followed by the character.
 *   - Update `curr = next.toString()`.
 */
class CountAndSayRLE {

    public static String countAndSay(int n) {
        if (n <= 0) return "";
        String curr = "1";

        for (int step = 2; step <= n; step++) {
            StringBuilder next = new StringBuilder();
            int i = 0;

            while (i < curr.length()) {
                char ch = curr.charAt(i);
                int count = 0;

                // Count consecutive occurrences of ch
                while (i < curr.length() && curr.charAt(i) == ch) {
                    count++;
                    i++;
                }

                next.append(count).append(ch);
            }

            curr = next.toString();
        }

        return curr;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 38: Count and Say (Run-Length Encoding) ===");

        for (int n = 1; n <= 8; n++) {
            System.out.printf("n = %d ==> \"%s\"%n", n, countAndSay(n));
        }
    }
}

/*
 * Time Complexity: O(N * L) where L is the average length of the string across iterations.
 * Space Complexity: O(L) - StringBuilder holding the generated terms.
 */
