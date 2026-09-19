import java.util.Arrays;

/**
 * Problem: Flood Fill (LeetCode 733)
 * Asked in: Amazon, Google, Microsoft, Uber
 * 
 * An image is represented by an m x n integer grid image where image[i][j] represents
 * the pixel value of the image. Perform flood fill from (sr, sc) with color newColor.
 * 
 * Approach:
 * Recursive DFS:
 * 1. Record original color = image[sr][sc].
 * 2. If original color == newColor, return image immediately (avoid infinite recursion).
 * 3. Change current pixel to newColor.
 * 4. Recurse in 4 cardinal directions (up, down, left, right) if neighboring pixel
 *    matches original color.
 * 
 * Time Complexity: O(M * N) in worst case visiting all pixels.
 * Space Complexity: O(M * N) recursion stack.
 */
class FloodFillAlgorithm {

    public static int[][] floodFill(int[][] image, int sr, int sc, int color) {
        int originalColor = image[sr][sc];
        if (originalColor != color) {
            dfs(image, sr, sc, originalColor, color);
        }
        return image;
    }

    private static void dfs(int[][] image, int r, int c, int origColor, int newColor) {
        if (r < 0 || r >= image.length || c < 0 || c >= image[0].length || image[r][c] != origColor) {
            return;
        }

        image[r][c] = newColor;

        dfs(image, r + 1, c, origColor, newColor);
        dfs(image, r - 1, c, origColor, newColor);
        dfs(image, r, c + 1, origColor, newColor);
        dfs(image, r, c - 1, origColor, newColor);
    }

    public static void main(String[] args) {
        int[][] image = {
            {1, 1, 1},
            {1, 1, 0},
            {1, 0, 1}
        };

        int[][] result = floodFill(image, 1, 1, 2);
        System.out.println("Flood Fill Result:");
        for (int[] row : result) {
            System.out.println(Arrays.toString(row));
        }
        // Expected:
        // [2, 2, 2]
        // [2, 2, 0]
        // [2, 0, 1]
    }
}
