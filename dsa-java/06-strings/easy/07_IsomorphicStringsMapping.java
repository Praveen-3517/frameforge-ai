/**
 * Problem Statement:
 * Given two strings `s` and `t`, determine if they are isomorphic.
 * Two strings are isomorphic if the characters in `s` can be replaced to get `t`.
 * All occurrences of a character must be replaced with another character while preserving order.
 * No two characters may map to the same character, but a character may map to itself.
 * (LeetCode 205: Isomorphic Strings).
 *
 * Example:
 * s = "egg", t = "add"     -> true
 * s = "foo", t = "bar"     -> false
 * s = "paper", t = "title" -> true
 *
 * Asked in: Google, Amazon, LinkedIn, Bloomberg
 *
 * Approach:
 * - Last-Seen Position Mapping (O(N) Time, O(1) Space):
 *   Instead of two maps mapping characters to each other, map each character in `s` and `t`
 *   to the LAST INDEX where it was seen!
 *   Maintain `int[] mapS = new int[256]` and `int[] mapT = new int[256]`:
 *   - For each index `i`:
 *     If `mapS[s.charAt(i)] != mapT[t.charAt(i)]`:
 *       The two characters appeared at different previous positions, violating bijection! Return false.
 *     Update `mapS[s.charAt(i)] = i + 1` and `mapT[t.charAt(i)] = i + 1` (using 1-based index).
 *   - If loop finishes without mismatch, strings are isomorphic.
 */
class IsomorphicStringsMapping {

    public static boolean isIsomorphic(String s, String t) {
        if (s.length() != t.length()) return false;

        int[] mapS = new int[256];
        int[] mapT = new int[256];

        for (int i = 0; i < s.length(); i++) {
            char cs = s.charAt(i);
            char ct = t.charAt(i);

            if (mapS[cs] != mapT[ct]) {
                return false;
            }

            // Record 1-based last seen index (so 0 remains default unset)
            mapS[cs] = i + 1;
            mapT[ct] = i + 1;
        }

        return true;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 205: Isomorphic Strings (Last-Seen Index Map) ===");

        String[][] testPairs = {
            { "egg", "add" },
            { "foo", "bar" },
            { "paper", "title" },
            { "badc", "baba" }
        };

        for (String[] pair : testPairs) {
            boolean iso = isIsomorphic(pair[0], pair[1]);
            System.out.printf("'%s' vs '%s' ==> Isomorphic: %s%n", pair[0], pair[1], iso);
        }
    }
}

/*
 * Time Complexity: O(N) - Single pass through both strings.
 * Space Complexity: O(1) - Two fixed 256-integer ASCII arrays.
 */
