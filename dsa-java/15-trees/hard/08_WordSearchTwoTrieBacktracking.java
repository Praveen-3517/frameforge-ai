import java.util.ArrayList;
import java.util.List;

/**
 * Problem: Word Search II (LeetCode 212)
 * Asked in: Amazon, Google, Microsoft, Uber, Apple
 * 
 * Given an m x n board of characters and a list of strings words, return all words on the board.
 * Each word must be constructed from letters of sequentially adjacent cells (horizontally or vertically).
 * The same letter cell may not be used more than once in a word.
 * 
 * Approach:
 * Trie + 2D DFS Backtracking:
 * 1. Build a Trie containing all words from the dictionary.
 *    Store the completed word string at the leaf TrieNode (`word` field) to avoid rebuilding strings during DFS.
 * 2. For each cell in the board, initiate DFS starting from the Trie root.
 * 3. In DFS:
 *    - If character matches trie child, step into it.
 *    - If node has `word != null`, add to result and set `node.word = null` (to prevent duplicates).
 *    - Mark cell visited by swapping with '#' or '#' char.
 *    - Explore all 4 adjacent directions.
 *    - Backtrack (restore original character).
 * 
 * Time Complexity: O(M * N * 4^L) where L is max word length.
 * Space Complexity: O(Total letters in words) for Trie.
 */
class WordSearchTwoTrieBacktracking {

    static class TrieNode {
        TrieNode[] children = new TrieNode[26];
        String word = null;
    }

    public static List<String> findWords(char[][] board, String[] words) {
        List<String> result = new ArrayList<>();
        TrieNode root = buildTrie(words);

        int rows = board.length;
        int cols = board[0].length;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                dfs(board, r, c, root, result);
            }
        }

        return result;
    }

    private static void dfs(char[][] board, int r, int c, TrieNode node, List<String> result) {
        char ch = board[r][c];
        if (ch == '#' || node.children[ch - 'a'] == null) return;

        node = node.children[ch - 'a'];
        if (node.word != null) {
            result.add(node.word);
            node.word = null; // Avoid duplicate additions
        }

        board[r][c] = '#'; // Mark visited

        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < board.length && nc >= 0 && nc < board[0].length && board[nr][nc] != '#') {
                dfs(board, nr, nc, node, result);
            }
        }

        board[r][c] = ch; // Backtrack
    }

    private static TrieNode buildTrie(String[] words) {
        TrieNode root = new TrieNode();
        for (String w : words) {
            TrieNode curr = root;
            for (char ch : w.toCharArray()) {
                int idx = ch - 'a';
                if (curr.children[idx] == null) {
                    curr.children[idx] = new TrieNode();
                }
                curr = curr.children[idx];
            }
            curr.word = w;
        }
        return root;
    }

    public static void main(String[] args) {
        char[][] board = {
            {'o', 'a', 'a', 'n'},
            {'e', 't', 'a', 'e'},
            {'i', 'h', 'k', 'r'},
            {'i', 'f', 'l', 'v'}
        };
        String[] words = {"oath", "pea", "eat", "rain"};

        List<String> found = findWords(board, words);
        System.out.println("Found words: " + found);
        // Expected: ["oath", "eat"]
    }
}
