/*
 * Problem Statement:
 * A k-booking happens when k events have some non-empty intersection.
 * Implement the MyCalendarThree class:
 * - book(int startTime, int endTime): Returns an integer k representing the largest
 *   integer such that there exists a k-booking in the calendar so far.
 * (LeetCode 732: My Calendar III)
 * 
 * Example:
 * book(10, 20) -> 1
 * book(50, 60) -> 1
 * book(10, 40) -> 2
 * book(5, 15)  -> 3
 * book(5, 10)  -> 3
 * book(25, 55) -> 3
 * 
 * Asked in: Google, Uber, Amazon, Citadel
 */

import java.util.TreeMap;

class MyCalendarThreeKBooking {

    static class MyCalendarThree {
        // TreeMap tracks boundary deltas: +1 at start, -1 at end
        private final TreeMap<Integer, Integer> timeline;

        public MyCalendarThree() {
            timeline = new TreeMap<>();
        }

        public int book(int startTime, int endTime) {
            // Add +1 at interval start
            timeline.put(startTime, timeline.getOrDefault(startTime, 0) + 1);
            // Add -1 at interval end
            timeline.put(endTime, timeline.getOrDefault(endTime, 0) - 1);

            int ongoingEvents = 0;
            int maxKBooking = 0;

            // Sweep line algorithm: iterate chronologically across all timestamps
            for (int delta : timeline.values()) {
                ongoingEvents += delta;
                maxKBooking = Math.max(maxKBooking, ongoingEvents);
            }

            return maxKBooking;
        }
    }

    public static void main(String[] args) {
        MyCalendarThree cal = new MyCalendarThree();

        int[][] bookings = {
            {10, 20},
            {50, 60},
            {10, 40},
            {5, 15},
            {5, 10},
            {25, 55}
        };

        System.out.println("--- My Calendar III (Sweep Line with TreeMap) ---");
        for (int[] b : bookings) {
            int k = cal.book(b[0], b[1]);
            System.out.printf("Booked [%2d, %2d) -> Max simultaneous overlap (k-booking): %d%n",
                    b[0], b[1], k);
        }
    }
}

/*
 * Time Complexity: O(N^2) total across N bookings (each book sweeps the N-entry TreeMap in O(N)).
 * Space Complexity: O(N) to store event endpoints in the TreeMap.
 */
