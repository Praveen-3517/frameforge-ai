/**
 * Problem Statement:
 * Given a month number (1 to 12) and a year, determine the total number of days in that month.
 * Handle February's day count dynamically based on whether the year is a leap year (29 vs 28 days).
 *
 * Example:
 * (Month: 2, Year: 2024) -> 29 days
 * (Month: 2, Year: 2023) -> 28 days
 * (Month: 4, Year: 2024) -> 30 days
 *
 * Asked in: Infosys, TCS, Wipro, Cognizant
 *
 * Approach:
 * - Group months with 31 days: January(1), March(3), May(5), July(7), August(8), October(10), December(12).
 * - Group months with 30 days: April(4), June(6), September(9), November(11).
 * - Month 2 (February): Check leap year rule `(year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)`
 *   Return 29 if leap, 28 otherwise.
 */
class DaysInMonthCalculator {

    public static boolean isLeapYear(int year) {
        return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    }

    public static int getDaysInMonth(int month, int year) {
        if (year <= 0) {
            throw new IllegalArgumentException("Year must be positive.");
        }

        return switch (month) {
            case 1, 3, 5, 7, 8, 10, 12 -> 31;
            case 4, 6, 9, 11            -> 30;
            case 2                      -> isLeapYear(year) ? 29 : 28;
            default                     -> throw new IllegalArgumentException("Invalid month: " + month + ". Must be between 1 and 12.");
        };
    }

    public static void main(String[] args) {
        System.out.println("=== Days in Month Calculator (Leap Year Aware) ===");

        int[][] testInputs = {
            { 1, 2024 },  // Jan
            { 2, 2024 },  // Feb Leap (29)
            { 2, 2023 },  // Feb Non-Leap (28)
            { 2, 2000 },  // Feb Leap Century (29)
            { 2, 1900 },  // Feb Non-Leap Century (28)
            { 4, 2024 },  // Apr (30)
            { 7, 2024 },  // Jul (31)
            { 12, 2024 }  // Dec (31)
        };

        for (int[] input : testInputs) {
            int m = input[0];
            int y = input[1];
            System.out.printf("Month %2d in Year %4d ==> %d Days%n", m, y, getDaysInMonth(m, y));
        }
    }
}

/*
 * Time Complexity: O(1) - Modern switch jump table.
 * Space Complexity: O(1) - Constant stack space.
 */
