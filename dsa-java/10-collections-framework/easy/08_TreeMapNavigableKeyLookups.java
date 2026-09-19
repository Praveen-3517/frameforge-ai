/*
 * Problem Statement:
 * Demonstrate NavigableMap operations using `java.util.TreeMap`:
 * - Find nearest matches using:
 *   - `floorKey(k)`: greatest key <= k
 *   - `ceilingKey(k)`: least key >= k
 *   - `lowerKey(k)`: greatest key < k
 *   - `higherKey(k)`: least key > k
 * - Reverse iteration using `descendingMap()`.
 * 
 * Asked in: Goldman Sachs, Morgan Stanley, Google, Citadel
 */

import java.util.TreeMap;

class TreeMapNavigableKeyLookups {

    public static void main(String[] args) {
        // Timestamp (milliseconds) -> Event Name
        TreeMap<Integer, String> eventTimeline = new TreeMap<>();
        eventTimeline.put(100, "User Login");
        eventTimeline.put(250, "Added Item to Cart");
        eventTimeline.put(400, "Initiated Checkout");
        eventTimeline.put(600, "Payment Processed");
        eventTimeline.put(900, "Order Confirmation Sent");

        System.out.println("--- TreeMap Navigable Timeline ---");
        System.out.println("All events: " + eventTimeline);

        int queryTime = 350;
        System.out.println("\nQuerying nearest events around timestamp " + queryTime + "ms:");
        System.out.println("  floorKey (<= 350):   " + eventTimeline.floorKey(queryTime) + " -> " + eventTimeline.get(eventTimeline.floorKey(queryTime)));
        System.out.println("  ceilingKey (>= 350): " + eventTimeline.ceilingKey(queryTime) + " -> " + eventTimeline.get(eventTimeline.ceilingKey(queryTime)));
        System.out.println("  lowerKey (< 250):    " + eventTimeline.lowerKey(250));
        System.out.println("  higherKey (> 600):   " + eventTimeline.higherKey(600));

        System.out.println("\n--- Descending Timeline ---");
        eventTimeline.descendingMap().forEach((k, v) -> System.out.printf("  %3dms : %s%n", k, v));
    }
}

/*
 * Time Complexity: O(log N) for all floorKey, ceilingKey, lowerKey, higherKey searches.
 * Space Complexity: O(N) red-black tree entries.
 */
