import java.util.ArrayList;
import java.util.List;

/**
 * Problem: Repeated DNA Sequences (LeetCode 187)
 * Asked in: LinkedIn, Amazon
 * 
 * The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.
 * Given a string s that represents a DNA sequence, return all the 10-letter-long sequences
 * (substrings) that occur more than once in a DNA molecule.
 * 
 * Approach - Bitmask Rolling Hash:
 * Encode each character as 2 bits: A=00, C=01, G=10, T=11
 * A 10-character window needs 20 bits, fitting in an int.
 * Use a rolling hash: remove leftmost character's bits, add new character's bits.
 * Use two HashSets: `seen` and `repeated` to track duplicates.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
import java.util.HashSet;
import java.util.Set;

class RepeatedDNASequencesBitmask {

    public static List<String> findRepeatedDnaSequences(String s) {
        if (s.length() <= 10) return new ArrayList<>();

        // Encode: A=0, C=1, G=2, T=3
        int[] charToInt = new int[26];
        charToInt['C' - 'A'] = 1;
        charToInt['G' - 'A'] = 2;
        charToInt['T' - 'A'] = 3;

        Set<Integer> seen = new HashSet<>();
        Set<String> repeated = new HashSet<>();

        int hash = 0;
        int mask = (1 << 20) - 1; // 20 bits for 10 characters * 2 bits each

        for (int i = 0; i < s.length(); i++) {
            int encoded = charToInt[s.charAt(i) - 'A'];
            hash = ((hash << 2) | encoded) & mask;

            if (i >= 9) { // Full 10-char window
                if (!seen.add(hash)) {
                    repeated.add(s.substring(i - 9, i + 1));
                }
            }
        }

        return new ArrayList<>(repeated);
    }

    public static void main(String[] args) {
        String dna = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
        List<String> result = findRepeatedDnaSequences(dna);
        System.out.println("Repeated 10-mers: " + result);
        // Expected: ["AAAAACCCCC", "CCCCCAAAAA"] (any order)
    }
}
