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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

static const int* DR = {1, 0, 0, -1}; // D, L, R, U
    static const int* DC = {0, -1, 1, 0};
    static const char* DIR_CHARS = {'D', 'L', 'R', 'U'};

    int* findPath(int** maze, int n) {
        int* result = new ArrayList<>();
        if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0) return result;

        bool[][] visited = (bool*)malloc((n) * sizeof(bool))[n];
        StringBuilder path = new StringBuilder();
        dfs(0, 0, maze, n, visited, path, result);
        Collections.sort(result);
        return result;
    }

    static void dfs(int r, int c, int** maze, int n, bool[][] visited, StringBuilder path, int* result) {
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
                path.deleteCharAt(((int)strlen(path)) - 1); // backtrack
            }
        }

        visited[r][c] = false; // backtrack
    }

    int main(void) {
        int** maze = {
            {1, 0, 0, 0},
            {1, 1, 0, 1},
            {1, 1, 0, 0},
            {0, 1, 1, 1}
        };

        int* paths = findPath(maze, n);
        printf("--- Rat in a Maze Paths ---\n");
        printf("Paths found: %d\n", paths);
        return 0;
}

/*
 * Time Complexity: O(4^(N^2)) worst case exploration bounded by grid cells.
 * Space Complexity: O(N^2) visited matrix and recursion stack.
 */
