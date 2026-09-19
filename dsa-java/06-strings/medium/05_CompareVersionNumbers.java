/**
 * Problem Statement:
 * Given two version strings, `version1` and `version2`, compare them.
 * A version number consists of one or more revisions joined by a dot '.'.
 * Each revision consists of digits and may contain leading zeros.
 * Return:
 *   - -1 if version1 < version2
 *   -  1 if version1 > version2
 *   -  0 if version1 == version2
 * Treat missing revisions as 0 (e.g., "1.0" and "1.0.0" are equal).
 * (LeetCode 165: Compare Version Numbers).
 *
 * Example:
 * version1 = "1.2",   version2 = "1.10"   -> -1
 * version1 = "1.01",  version2 = "1.001"  -> 0
 * version1 = "1.0",   version2 = "1.0.0.0" -> 0
 *
 * Asked in: Apple, Microsoft, Amazon, Google
 *
 * Approach:
 * - Two-Pointer Zero-Allocation Parsing (O(max(N, M)) Time, O(1) Space):
 *   Instead of calling `s.split("\\.")` (which creates array and String allocations),
 *   use two pointers `i` and `j`:
 *   - For each revision chunk:
 *     Parse `num1` by reading digits until '.' or string end.
 *     Parse `num2` by reading digits until '.' or string end.
 *     If `num1 < num2`: return -1.
 *     If `num1 > num2`: return 1.
 *     Skip '.' and continue.
 *   - Missing trailing revisions automatically default to 0.
 */
class CompareVersionNumbers {

    public static int compareVersion(String version1, String version2) {
        int n1 = version1.length();
        int n2 = version2.length();
        int i = 0, j = 0;

        while (i < n1 || j < n2) {
            int num1 = 0;
            while (i < n1 && version1.charAt(i) != '.') {
                num1 = num1 * 10 + (version1.charAt(i) - '0');
                i++;
            }

            int num2 = 0;
            while (j < n2 && version2.charAt(j) != '.') {
                num2 = num2 * 10 + (version2.charAt(j) - '0');
                j++;
            }

            if (num1 < num2) return -1;
            if (num1 > num2) return 1;

            // Skip the '.'
            i++;
            j++;
        }

        return 0;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 165: Compare Version Numbers (Two Pointers) ===");

        String[][] versionPairs = {
            { "1.2", "1.10" },
            { "1.01", "1.001" },
            { "1.0", "1.0.0.0" },
            { "0.1", "1.1" },
            { "7.5.2.4", "7.5.3" }
        };

        for (String[] pair : versionPairs) {
            int result = compareVersion(pair[0], pair[1]);
            String cmp = (result == -1) ? "<" : (result == 1 ? ">" : "==");
            System.out.printf("\"%s\" %s \"%s\" (Code: %d)%n", pair[0], cmp, pair[1], result);
        }
    }
}

/*
 * Time Complexity: O(max(N, M)) - Linear scan of both version strings.
 * Space Complexity: O(1) - Pointer variables only. Zero heap allocations.
 */
