import java.util.Arrays;

/**
 * Problem: Maximum Units on a Truck (LeetCode 1710)
 * Asked in: Amazon
 * 
 * You are assigned to put some amount of boxes onto one truck. You are given a 2D array
 * boxTypes, where boxTypes[i] = [numberOfBoxes_i, numberOfUnitsPerBox_i].
 * You are also given an integer truckSize, which is the maximum number of boxes that can be put on the truck.
 * Return the maximum total number of units that can be put on the truck.
 * 
 * Approach:
 * Greedy Fractional Knapsack Strategy:
 * 1. Sort boxTypes by units per box descending (b[1] - a[1]).
 * 2. Greedily pick the maximum boxes from the highest unit types until truck capacity is reached.
 * 
 * Time Complexity: O(N log N) for sorting.
 * Space Complexity: O(1) auxiliary space.
 */
class MaximumUnitsOnTruck {

    public static int maximumUnits(int[][] boxTypes, int truckSize) {
        // Sort by units per box descending
        Arrays.sort(boxTypes, (a, b) -> Integer.compare(b[1], a[1]));

        int totalUnits = 0;

        for (int[] box : boxTypes) {
            int count = box[0];
            int units = box[1];

            int take = Math.min(truckSize, count);
            totalUnits += take * units;
            truckSize -= take;

            if (truckSize == 0) break;
        }

        return totalUnits;
    }

    public static void main(String[] args) {
        int[][] boxTypes1 = {{1, 3}, {2, 2}, {3, 1}};
        System.out.println("Max units (truck=4): " + maximumUnits(boxTypes1, 4) + " (Expected: 8)");

        int[][] boxTypes2 = {{5, 10}, {2, 5}, {4, 7}, {3, 9}};
        System.out.println("Max units (truck=10): " + maximumUnits(boxTypes2, 10) + " (Expected: 91)");
    }
}
