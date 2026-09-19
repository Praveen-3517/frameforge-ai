/*
 * Problem Statement:
 * Given an m x n board of characters and a list of strings words, return all words
 * on the board. Each word must be constructed from letters of sequentially adjacent
 * cells (horizontally or vertically neighboring). The same letter cell may not be used
 * more than once in a word.
 * (LeetCode 212: Word Search II)
 * 
 * Asked in: Amazon, Microsoft, Google, Uber, Apple
 */

import java.util.ArrayList;
import java.util.List;

class WordSearchTwoTrieBacktracking {

    static class TrieNode {
        TrieNode[] children = new TrieNode[26];
        String word = null; // Store complete word at leaf
    }

    private static TrieNode buildTrie(String[] words) {
        TrieNode root = new TrieNode();
        for (String w : words) {
            TrieNode curr = root;
            for (char c : w.toCharArray()) {
                int idx = c - 'a';
                if (curr.children[idx] == null) {
                    curr.children[idx] = new TrieNode();
                }
                curr = curr.children[idx];
            }
            curr.word = w;
        }
        return root;
    }

    public static List<String> findWords(char[][] board, String[] words) {
        List<String> result = new ArrayList<>();
        TrieNode root = buildTrie(words);

        for (int r = 0; r < board.length; r++) {
            for (int c = 0; c < board[0].length; c++) {
                dfs(board, r, c, root, result);
            }
        }

        return result;
    }

    private static void dfs(char[][] board, int r, int c, TrieNode node, List<String> result) {
        if (r < 0 || r >= board.length || c < 0 || c >= board[0].length) return;

        char ch = board[r][c];
        if (ch == '#' || node.children[ch - 'a'] == null) return;

        node = node.children[ch - 'a'];

        if (node.word != null) {
            result.add(node.word);
            node.word = null; // De-duplicate found word
        }

        board[r][c] = '#'; // Mark visited

        dfs(board, r + 1, c, node, result);
        dfs(board, r - 1, c, node, result);
        dfs(board, r, c + 1, node, result);
        dfs(board, r, c - 1, node, result);

        board[r][c] = ch; // Backtrack
    }

    public static void main(String[] args) {
        char[][] board = {
            {'o','a','a','n'},
            {'e','t','a','e'},
            {'i','h','k','r'},
            {'i','f','l','v'}
        };
        String[] words = {"oath","pea","eat","rain"};

        System.out.println("--- Word Search II with Trie Pruning ---");
        List<String> found = findWords(board, words);
        System.out.println("Words found on board: " + found);
    }
}

/*
 * Time Complexity: O(M * N * 4 * 3^(L-1)) where L is maximum word length.
 * Space Complexity: O(Total characters in words dictionary) for Trie.
 */
