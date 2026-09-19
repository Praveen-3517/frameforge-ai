/*
 * Problem Statement:
 * Given an m x n grid of characters board and a string word, return true if word
 * exists in the grid.
 * The word can be constructed from letters of sequentially adjacent cells, where
 * adjacent cells are horizontally or vertically neighboring. The same letter cell
 * may not be used more than once in a word.
 * 
 * Example:
 * board = [
 *   ['A','B','C','E'],
 *   ['S','F','C','S'],
 *   ['A','D','E','E']
 * ]
 * word = "ABCCED" -> true
 * word = "SEE"    -> true
 * word = "ABCB"   -> false
 * 
 * Asked in: Amazon, Microsoft, Bloomberg, Apple, Uber
 */

class WordSearchGridRecursion {

    private static final int[][] DIRS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    /**
     * Approach:
     * 2D Grid DFS Backtracking:
     * 1. Search for first character of word in any cell (r, c).
     * 2. When found, call dfs(r, c, 0):
     *    - If index == word.length(), return true.
     *    - Check bounds and board[r][c] == word.charAt(index).
     *    - Temporarily mark cell visited (e.g., '#' or board[r][c] ^= 256).
     *    - Recurse in all 4 cardinal directions.
     *    - Backtrack (restore original character).
     */
    public static boolean exist(char[][] board, String word) {
        int rows = board.length;
        int cols = board[0].length;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (board[r][c] == word.charAt(0)) {
                    if (dfs(board, word, r, c, 0)) return true;
                }
            }
        }
        return false;
    }

    private static boolean dfs(char[][] board, String word, int r, int c, int idx) {
        if (idx == word.length()) return true;
        if (r < 0 || r >= board.length || c < 0 || c >= board[0].length) return false;
        if (board[r][c] != word.charAt(idx)) return false;

        char original = board[r][c];
        board[r][c] = '#'; // Mark visited

        for (int[] d : DIRS) {
            int nr = r + d[0];
            int nc = c + d[1];
            if (dfs(board, word, nr, nc, idx + 1)) {
                board[r][c] = original; // Backtrack before return
                return true;
            }
        }

        board[r][c] = original; // Backtrack
        return false;
    }

    public static void main(String[] args) {
        char[][] board = {
            {'A', 'B', 'C', 'E'},
            {'S', 'F', 'C', 'S'},
            {'A', 'D', 'E', 'E'}
        };

        String[] words = {"ABCCED", "SEE", "ABCB"};
        System.out.println("--- Word Search in 2D Board ---");
        for (String w : words) {
            System.out.println("Search for \"" + w + "\": " + exist(board, w));
        }
    }
}

/*
 * Time Complexity: O(M * N * 3^L) where M*N is grid size, L is word length.
 * Space Complexity: O(L) for recursion stack.
 */
