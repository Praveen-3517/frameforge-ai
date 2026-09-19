import java.util.ArrayList;
import java.util.List;

/**
 * Problem: Pascal's Triangle (LeetCode 118)
 * Asked in: Amazon, Apple, Goldman Sachs
 * 
 * Given an integer numRows, return the first numRows of Pascal's triangle.
 * In Pascal's triangle, each number is the sum of the two numbers directly above it.
 * 
 * Approach:
 * 2D DP construction:
 * Each row starts and ends with 1.
 * For 1 <= j < i: row[j] = prevRow[j - 1] + prevRow[j].
 * 
 * Time Complexity: O(numRows^2)
 * Space Complexity: O(numRows^2) for the output triangle.
 */
class PascalsTriangleGenerate {

    public static List<List<Integer>> generate(int numRows) {
        List<List<Integer>> triangle = new ArrayList<>(numRows);

        for (int i = 0; i < numRows; i++) {
            List<Integer> row = new ArrayList<>(i + 1);
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i) {
                    row.add(1);
                } else {
                    List<Integer> prevRow = triangle.get(i - 1);
                    row.add(prevRow.get(j - 1) + prevRow.get(j));
                }
            }
            triangle.add(row);
        }

        return triangle;
    }

    public static void main(String[] args) {
        List<List<Integer>> result = generate(5);
        System.out.println("Pascal's Triangle (5 rows): " + result);
        // Expected: [[1], [1, 1], [1, 2, 1], [1, 3, 3, 1], [1, 4, 6, 4, 1]]
    }
}
