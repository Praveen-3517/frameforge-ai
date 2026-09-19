/*
 * Problem Statement:
 * Koko loves to eat bananas. There are n piles of bananas, the i-th pile has piles[i] bananas.
 * The guards have gone and will come back in h hours.
 * Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile
 * of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats
 * all of them instead and will not eat any more bananas during this hour.
 * Return the minimum integer k such that she can eat all the bananas within h hours.
 * (LeetCode 875: Koko Eating Bananas)
 * 
 * Example:
 * Input: piles = [3, 6, 7, 11], h = 8
 * Output: 4
 * 
 * Asked in: Google, Airbnb, Amazon, Bloomberg
 */

class KokoEatingBananasBinarySearchOnAnswer {

    /**
     * Approach:
     * Binary Search on Answer:
     * - Search space for speed k: [1, max(piles)].
     * - Monotonic property: If speed k is sufficient to eat in <= h hours, any speed > k
     *   will also be sufficient.
     * - If canFinish(k, h): try smaller speed (high = mid).
     * - Else: must increase speed (low = mid + 1).
     */
    public static int minEatingSpeed(int[] piles, int h) {
        int low = 1;
        int high = 1;
        for (int p : piles) {
            if (p > high) high = p;
        }

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (canFinish(piles, h, mid)) {
                high = mid; // viable, look for smaller valid speed
            } else {
                low = mid + 1;
            }
        }

        return low;
    }

    private static boolean canFinish(int[] piles, int h, int speed) {
        long totalHours = 0;
        for (int p : piles) {
            // Ceiling division: (p + speed - 1) / speed
            totalHours += (p + speed - 1) / speed;
            if (totalHours > h) return false;
        }
        return totalHours <= h;
    }

    public static void main(String[] args) {
        int[] piles = {3, 6, 7, 11};
        int h = 8;

        System.out.println("Piles: [3, 6, 7, 11], Max Hours: 8");
        System.out.println("Minimum eating speed k: " + minEatingSpeed(piles, h));

        int[] piles2 = {30, 11, 23, 4, 20};
        int h2 = 5;
        System.out.println("\nPiles: [30, 11, 23, 4, 20], Max Hours: 5");
        System.out.println("Minimum eating speed k: " + minEatingSpeed(piles2, h2));
    }
}

/*
 * Time Complexity: O(N * log(max(piles))) where N is piles length.
 * Space Complexity: O(1) auxiliary space.
 */
