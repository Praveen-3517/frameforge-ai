/**
 * Problem Statement:
 * Convert a non-negative integer `num` to its English words representation.
 * (0 <= num <= 2^31 - 1 = 2,147,483,647).
 * (LeetCode 273: Integer to English Words - Hard).
 *
 * Example:
 * 1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
 *
 * Asked in: Amazon, Facebook / Meta, Microsoft, Apple, Google
 *
 * Approach:
 * - 3-Digit Chunking Strategy:
 *   Every 3 digits (1000-fold) follows the exact same verbal rules, followed by a scale suffix:
 *   - Chunk 0: "" (Units)
 *   - Chunk 1: "Thousand"
 *   - Chunk 2: "Million"
 *   - Chunk 3: "Billion"
 * - Inside each 3-digit chunk (0 to 999):
 *   - If n >= 100: append `LESS_THAN_20[n / 100] + " Hundred"` and reduce `n %= 100`.
 *   - If n >= 20 : append `TENS[n / 10]` and reduce `n %= 10`.
 *   - If n > 0  : append `LESS_THAN_20[n]`.
 * - Edge case: `num == 0` returns `"Zero"`.
 */
class IntegerToEnglishWords {

    private static final String[] LESS_THAN_20 = {
        "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
        "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen",
        "Eighteen", "Nineteen"
    };

    private static final String[] TENS = {
        "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
    };

    private static final String[] THOUSANDS = { "", "Thousand", "Million", "Billion" };

    public static String numberToWords(int num) {
        if (num == 0) return "Zero";

        StringBuilder result = new StringBuilder();
        int chunkIdx = 0;

        while (num > 0) {
            int chunk = num % 1000;
            if (chunk != 0) {
                String chunkWords = helper(chunk);
                if (THOUSANDS[chunkIdx].length() > 0) {
                    chunkWords += " " + THOUSANDS[chunkIdx];
                }
                if (result.length() > 0) {
                    result.insert(0, chunkWords + " ");
                } else {
                    result.insert(0, chunkWords);
                }
            }
            num /= 1000;
            chunkIdx++;
        }

        return result.toString().trim();
    }

    private static String helper(int n) {
        StringBuilder sb = new StringBuilder();

        if (n >= 100) {
            sb.append(LESS_THAN_20[n / 100]).append(" Hundred");
            n %= 100;
            if (n > 0) sb.append(" ");
        }

        if (n >= 20) {
            sb.append(TENS[n / 10]);
            n %= 10;
            if (n > 0) sb.append(" ");
        }

        if (n > 0) {
            sb.append(LESS_THAN_20[n]);
        }

        return sb.toString();
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 273: Integer to English Words ===");

        int[] testNumbers = {
            0,
            5,
            19,
            99,
            123,
            12345,
            1000010,
            1234567,
            2147483647 // Max 32-bit int
        };

        for (int n : testNumbers) {
            System.out.printf("%10d ==> \"%s\"%n", n, numberToWords(n));
        }
    }
}

/*
 * Time Complexity: O(1) - Number of chunks is bounded by 4 for 32-bit signed integers.
 * Space Complexity: O(1) - Stack variables only.
 */
