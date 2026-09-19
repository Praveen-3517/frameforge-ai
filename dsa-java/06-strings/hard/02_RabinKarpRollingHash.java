/**
 * Problem Statement:
 * Implement the Rabin-Karp Substring Search Algorithm using a polynomial rolling hash function.
 * Given a `text` and a `pattern`, find all starting indices of `pattern` inside `text`.
 *
 * Example:
 * text = "GEEKS FOR GEEKS", pattern = "GEEK" -> Indices: [0, 10]
 *
 * Asked in: Amazon, Google, Microsoft, Adobe
 *
 * Approach:
 * - Polynomial Rolling Hash:
 *   Let base $B = 256$ (number of characters in extended ASCII) and prime modulus $Q = 1000000007$.
 *   - Hash formula:
 *     $H(s) = (s[0] \cdot B^{M-1} + s[1] \cdot B^{M-2} + ... + s[M-1]) \pmod Q$.
 *   - Precompute high power: $H_{pow} = B^{M-1} \pmod Q$.
 *   - Rolling update when window shifts right:
 *     Subtract leading character: `hash = (hash - text[i] * H_pow) % Q`.
 *     Multiply by base: `hash = (hash * B) % Q`.
 *     Add trailing character: `hash = (hash + text[i + M]) % Q`.
 *     If `hash < 0`, add `Q`.
 *   - Hash Collision Check: When `windowHash == patternHash`, perform an explicit `O(M)` character
 *     comparison to eliminate spurious false-positive hash collisions.
 */
class RabinKarpRollingHash {

    private static final int BASE = 256;
    private static final long MOD = 1000000007L;

    public static int search(String text, String pattern) {
        int n = text.length();
        int m = pattern.length();
        if (m > n) return -1;

        long patternHash = 0;
        long windowHash = 0;
        long hPow = 1;

        // Precompute hPow = BASE^(m - 1) % MOD
        for (int i = 0; i < m - 1; i++) {
            hPow = (hPow * BASE) % MOD;
        }

        // Calculate initial hash for pattern and first window of text
        for (int i = 0; i < m; i++) {
            patternHash = (patternHash * BASE + pattern.charAt(i)) % MOD;
            windowHash = (windowHash * BASE + text.charAt(i)) % MOD;
        }

        // Slide window over text
        for (int i = 0; i <= n - m; i++) {
            if (patternHash == windowHash) {
                // Potential match: verify character-by-character against collision
                boolean match = true;
                for (int j = 0; j < m; j++) {
                    if (text.charAt(i + j) != pattern.charAt(j)) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    return i; // Match found
                }
            }

            // Compute rolling hash for next window
            if (i < n - m) {
                windowHash = (windowHash - text.charAt(i) * hPow) % MOD;
                windowHash = (windowHash * BASE + text.charAt(i + m)) % MOD;
                if (windowHash < 0) {
                    windowHash += MOD;
                }
            }
        }

        return -1;
    }

    public static void main(String[] args) {
        System.out.println("=== Rabin-Karp Substring Search (Polynomial Rolling Hash) ===");

        String text = "GEEKS FOR GEEKS";
        String pattern = "GEEK";

        int firstIndex = search(text, pattern);
        System.out.printf("Text   : \"%s\"%nPattern: \"%s\"%nMatch Index: %d%n",
                text, pattern, firstIndex);
    }
}

/*
 * Time Complexity: O(N + M) average time, O(N * M) worst-case with malicious hash collisions.
 * Space Complexity: O(1) - Primitive rolling hash registers.
 */
