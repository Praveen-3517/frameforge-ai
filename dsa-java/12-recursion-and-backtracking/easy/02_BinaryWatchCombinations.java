/*
 * Problem Statement:
 * A binary watch has 4 LEDs on the top (representing hours 0-11) and 6 LEDs on the
 * bottom (representing minutes 0-59).
 * Given an integer turnedOn which represents the number of LEDs that are currently on,
 * return all possible times the watch could represent.
 * (LeetCode 401: Binary Watch)
 * 
 * Example:
 * Input: turnedOn = 1
 * Output: ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
 * 
 * Asked in: Google, Amazon, Microsoft
 */

import java.util.ArrayList;
import java.util.List;

class BinaryWatchCombinations {

    public static List<String> readBinaryWatch(int turnedOn) {
        List<String> times = new ArrayList<>();
        if (turnedOn < 0 || turnedOn > 8) return times;

        for (int h = 0; h < 12; h++) {
            for (int m = 0; m < 60; m++) {
                if (Integer.bitCount(h) + Integer.bitCount(m) == turnedOn) {
                    times.add(String.format("%d:%02d", h, m));
                }
            }
        }

        return times;
    }

    public static void main(String[] args) {
        int turnedOn = 1;
        List<String> result = readBinaryWatch(turnedOn);

        System.out.println("Binary Watch times for turnedOn = " + turnedOn + " (Count: " + result.size() + "):");
        System.out.println(result);
    }
}

/*
 * Time Complexity: O(1) - Constant search space: exactly 12 * 60 = 720 combinations checked.
 * Space Complexity: O(1) auxiliary space (excluding result list).
 */
