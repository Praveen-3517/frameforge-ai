import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Problem: Number of Valid Words for Each Puzzle (LeetCode 1178)
 * Asked in: Google
 * 
 * With respect to a given puzzle string, a word is valid if both the following conditions are satisfied:
 * - word contains the first letter of puzzle.
 * - For each letter in word, that letter is in puzzle.
 * 
 * Return an array answer, where answer[i] is the number of words in the given word list
 * that are valid with respect to the puzzle puzzles[i].
 * 
 * Approach - Bitmask Frequency Map:
 * 1. Encode each word as a 26-bit bitmask (ignore duplicates, only care which letters appear).
 *    Build a frequency map: wordMask -> count.
 * 2. For each puzzle (length 6):
 *    - Get puzzleMask (26-bit).
 *    - Enumerate all subsets of puzzleMask that include puzzle[0].
 *    - For each such subset, look up its count in wordMask frequency map.
 * 
 * Time Complexity: O(W * L + P * 2^6) where W = words count, L = avg word length, P = puzzles count
 * Space Complexity: O(W) for word frequency map
 */
class NumberOfValidWordsForEveryPuzzle {

    public static List<Integer> findNumOfValidWords(String[] words, String[] puzzles) {
        Map<Integer, Integer> wordFreq = new HashMap<>();
        for (String word : words) {
            int mask = 0;
            for (char c : word.toCharArray()) {
                mask |= (1 << (c - 'a'));
            }
            wordFreq.put(mask, wordFreq.getOrDefault(mask, 0) + 1);
        }

        List<Integer> result = new ArrayList<>();

        for (String puzzle : puzzles) {
            int puzzleMask = 0;
            for (char c : puzzle.toCharArray()) {
                puzzleMask |= (1 << (c - 'a'));
            }

            int firstBit = 1 << (puzzle.charAt(0) - 'a');
            int count = 0;

            // Enumerate all subsets of puzzleMask that include firstBit
            for (int sub = puzzleMask; sub > 0; sub = (sub - 1) & puzzleMask) {
                if ((sub & firstBit) != 0) {
                    count += wordFreq.getOrDefault(sub, 0);
                }
            }

            result.add(count);
        }

        return result;
    }

    public static void main(String[] args) {
        String[] words = {"aaaa", "asas", "able", "ability", "actt", "actor", "access"};
        String[] puzzles = {"aboveyz", "abrodyz", "abslute", "became", "bedozy", "bedroj"};

        System.out.println("Valid word counts: " + findNumOfValidWords(words, puzzles));
        // Expected: [1, 1, 3, 0, 0, 0]
    }
}
