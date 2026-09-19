import java.util.ArrayList;
import java.util.List;

/**
 * Problem Statement:
 * Given an array of strings `words` and a width `maxWidth`, format the text such that each line
 * has exactly `maxWidth` characters and is fully (left and right) justified.
 * Rules:
 *   1. Pack as many words as possible on each line.
 *   2. Fully Justified: Extra spaces between words must be distributed as evenly as possible.
 *      If remaining spaces do not divide evenly, leftmost slots receive more spaces.
 *   3. Left Justified: For the last line of text OR lines containing only a single word,
 *      words are separated by a single space, and remaining spaces are padded to the right.
 * (LeetCode 68: Text Justification - Hard).
 *
 * Asked in: Google, Amazon, LinkedIn, Apple, Uber
 *
 * Approach:
 * - Two-Pointer Line Chunking:
 *   - Start index `i`. Greedily advance `j` while the words fit:
 *     `totalCharLen + wordLen + (j - i) <= maxWidth` (where `j - i` is minimum 1-space gaps).
 * - Conditional Formatting:
 *   - Case 1: Last line (`j == words.length`) OR Single-word line (`j - i == 1`):
 *     Join words with a single space `" "`, then right-pad remaining spaces until line length is `maxWidth`.
 *   - Case 2: Full Justification (`j - i > 1` and not last line):
 *     Calculate total spaces to distribute: `spaces = maxWidth - totalWordLen`.
 *     Number of gaps: `gaps = j - i - 1`.
 *     Base spaces per gap: `spaces / gaps`.
 *     Extra spaces for leftmost gaps: `spaces % gaps`.
 */
class TextJustificationConditionals {

    public static List<String> fullJustify(String[] words, int maxWidth) {
        List<String> result = new ArrayList<>();
        int n = words.length;
        int i = 0;

        while (i < n) {
            int j = i + 1;
            int lineWordLen = words[i].length();

            // Greedily find how many words fit on this line
            while (j < n && lineWordLen + 1 + words[j].length() + (j - i - 1) <= maxWidth) {
                lineWordLen += words[j].length();
                j++;
            }

            int numWords = j - i;
            int numGaps = numWords - 1;
            StringBuilder sb = new StringBuilder();

            // Conditional Branch 1: Last line or single-word line (Left-Justified)
            if (j == n || numWords == 1) {
                for (int k = i; k < j; k++) {
                    sb.append(words[k]);
                    if (k < j - 1) sb.append(" ");
                }
                while (sb.length() < maxWidth) {
                    sb.append(" ");
                }
            } else {
                // Conditional Branch 2: Fully Justified line
                int totalSpaces = maxWidth - lineWordLen;
                int baseSpaces = totalSpaces / numGaps;
                int extraSpaces = totalSpaces % numGaps;

                for (int k = i; k < j; k++) {
                    sb.append(words[k]);
                    if (k < j - 1) {
                        int spacesToApply = baseSpaces + (k - i < extraSpaces ? 1 : 0);
                        sb.append(" ".repeat(spacesToApply));
                    }
                }
            }

            result.add(sb.toString());
            i = j; // Advance to next line
        }

        return result;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 68: Text Justification (Condition-Driven Formatting) ===");

        String[] words = { "This", "is", "an", "example", "of", "text", "justification." };
        int maxWidth = 16;

        List<String> justified = fullJustify(words, maxWidth);

        System.out.println("Formatted Output (width = " + maxWidth + "):");
        for (String line : justified) {
            System.out.println("|" + line + "|");
        }
    }
}

/*
 * Time Complexity: O(N) where N is the total number of characters across all words.
 * Space Complexity: O(N) - Storage for the justified output lines.
 */
