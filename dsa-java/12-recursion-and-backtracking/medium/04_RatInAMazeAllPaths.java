/*
 * Problem Statement:
 * Consider a rat placed at (0, 0) in a square grid of size N x N. It has to reach
 * the destination at (N - 1, N - 1). The maze is represented by a binary matrix where
 * 0 indicates a blocked cell and 1 indicates an open path.
 * The rat can move in directions: Down ('D'), Left ('L'), Right ('R'), Up ('U').
 * Return all complete paths sorted in alphabetical order.
 * 
 * Example:
 * maze = [
 *   [1, 0, 0, 0],
 *   [1, 1, 0, 1],
 *   [1, 1, 0, 0],
 *   [0, 1, 1, 1]
 * ]
 * Output: ["DDRDRR", "DRDDRR"]
 * 
 * Asked in: Amazon, Microsoft, Samsung, Paytm
 */

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class RatInAMazeAllPaths {

    private static final int[] DR = {1, 0, 0, -1}; // D, L, R, U
    private static final int[] DC = {0, -1, 1, 0};
    private static final char[] DIR_CHARS = {'D', 'L', 'R', 'U'};

    public static List<String> findPath(int[][] maze, int n) {
        List<String> result = new ArrayList<>();
        if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0) return result;

        boolean[][] visited = new boolean[n][n];
        StringBuilder path = new StringBuilder();
        dfs(0, 0, maze, n, visited, path, result);
        Collections.sort(result);
        return result;
    }

    private static void dfs(int r, int c, int[][] maze, int n, boolean[][] visited, StringBuilder path, List<String> result) {
        if (r == n - 1 && c == n - 1) {
            result.add(path.toString());
            return;
        }

        visited[r][c] = true;

        for (int i = 0; i < 4; i++) {
            int nr = r + DR[i];
            int nc = c + DC[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < n && maze[nr][nc] == 1 && !visited[nr][nc]) {
                path.append(DIR_CHARS[i]);
                dfs(nr, nc, maze, n, visited, path, result);
                path.deleteCharAt(path.length() - 1); // backtrack
            }
        }

        visited[r][c] = false; // backtrack
    }

    public static void main(String[] args) {
        int[][] maze = {
            {1, 0, 0, 0},
            {1, 1, 0, 1},
            {1, 1, 0, 0},
            {0, 1, 1, 1}
        };

        List<String> paths = findPath(maze, maze.length);
        System.out.println("--- Rat in a Maze Paths ---");
        System.out.println("Paths found: " + paths);
    }
}

/*
 * Time Complexity: O(4^(N^2)) worst case exploration bounded by grid cells.
 * Space Complexity: O(N^2) visited matrix and recursion stack.
 */
