/**
 * Problem: Can Place Flowers (LeetCode 605)
 * Asked in: Facebook, LinkedIn, Google
 * 
 * You have a long flowerbed in which some plots are planted, and some are not.
 * However, flowers cannot be planted in adjacent plots.
 * Given an integer array flowerbed containing 0's and 1's, and an integer n, return
 * true if n new flowers can be planted in the flowerbed without violating the rule.
 * 
 * Approach:
 * Greedy Linear Scan:
 * At each plot i, if plot is empty (0), check if left neighbor is 0 (or i == 0)
 * and right neighbor is 0 (or i == len - 1).
 * If both adjacent plots are free, plant flower at i (flowerbed[i] = 1) and decrement n.
 * If n <= 0, return true.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class CanPlaceFlowersGreedy {

    public static boolean canPlaceFlowers(int[] flowerbed, int n) {
        int len = flowerbed.length;

        for (int i = 0; i < len; i++) {
            if (flowerbed[i] == 0) {
                boolean emptyLeft = (i == 0 || flowerbed[i - 1] == 0);
                boolean emptyRight = (i == len - 1 || flowerbed[i + 1] == 0);

                if (emptyLeft && emptyRight) {
                    flowerbed[i] = 1;
                    n--;
                    if (n <= 0) return true;
                }
            }
        }

        return n <= 0;
    }

    public static void main(String[] args) {
        int[] fb1 = {1, 0, 0, 0, 1};
        System.out.println("Can place 1: " + canPlaceFlowers(fb1, 1) + " (Expected: true)");

        int[] fb2 = {1, 0, 0, 0, 1};
        System.out.println("Can place 2: " + canPlaceFlowers(fb2, 2) + " (Expected: false)");
    }
}
