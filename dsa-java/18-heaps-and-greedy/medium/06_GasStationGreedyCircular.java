/**
 * Problem: Gas Station (LeetCode 134)
 * Asked in: Amazon, Google, Microsoft, Bloomberg
 * 
 * There are n gas stations along a circular route, where the amount of gas at the ith
 * station is gas[i]. Traveling from station i to i + 1 costs cost[i] gas.
 * Return the starting gas station's index if you can travel around the circuit once in the clockwise
 * direction, otherwise return -1.
 * 
 * Approach:
 * Greedy Single Pass:
 * 1. If sum(gas) < sum(cost), impossible to complete circuit -> return -1.
 * 2. Keep track of currentTank.
 *    If currentTank < 0 at station i, NO station from `start` to `i` can be the starting station!
 *    Reset currentTank = 0, and try starting at station i + 1.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class GasStationGreedyCircular {

    public static int canCompleteCircuit(int[] gas, int[] cost) {
        int totalTank = 0;
        int currentTank = 0;
        int startStation = 0;

        for (int i = 0; i < gas.length; i++) {
            int net = gas[i] - cost[i];
            totalTank += net;
            currentTank += net;

            if (currentTank < 0) {
                startStation = i + 1;
                currentTank = 0;
            }
        }

        return totalTank >= 0 ? startStation : -1;
    }

    public static void main(String[] args) {
        int[] gas1 = {1, 2, 3, 4, 5};
        int[] cost1 = {3, 4, 5, 1, 2};
        System.out.println("Start station 1: " + canCompleteCircuit(gas1, cost1) + " (Expected: 3)");

        int[] gas2 = {2, 3, 4};
        int[] cost2 = {3, 4, 3};
        System.out.println("Start station 2: " + canCompleteCircuit(gas2, cost2) + " (Expected: -1)");
    }
}
