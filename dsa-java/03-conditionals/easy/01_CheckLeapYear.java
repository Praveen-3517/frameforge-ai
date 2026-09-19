/**
 * Problem Statement:
 * Determine whether a given Gregorian calendar year is a Leap Year.
 * Rules:
 * 1. A year is a leap year if it is divisible by 4.
 * 2. Exception: Years divisible by 100 are NOT leap years...
 * 3. Exception to the exception: ...UNLESS they are also divisible by 400.
 *
 * Example:
 * 2000 -> Leap Year (divisible by 400)
 * 1900 -> NOT Leap Year (divisible by 100 but not 400)
 * 2024 -> Leap Year (divisible by 4, not 100)
 * 2023 -> NOT Leap Year
 *
 * Asked in: TCS, Infosys, Cognizant, Wipro, Accenture
 *
 * Approach:
 * - Direct Boolean Conditional:
 *   `boolean isLeap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);`
 * - Evaluation order matters: Checking `% 400 == 0` first short-circuits centuries like 2000 and 2400.
 *   Then `year % 4 == 0 && year % 100 != 0` handles all standard leap years.
 */
class CheckLeapYear {

    public static boolean isLeapYear(int year) {
        if (year <= 0) {
            throw new IllegalArgumentException("Year must be a positive integer.");
        }
        return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    }

    public static void main(String[] args) {
        System.out.println("=== Gregorian Calendar Leap Year Validator ===");

        int[] testYears = { 1600, 1700, 1800, 1900, 2000, 2004, 2019, 2020, 2024, 2100 };

        for (int y : testYears) {
            boolean leap = isLeapYear(y);
            System.out.printf("Year %4d ==> %s%n", y, leap ? "LEAP YEAR (366 Days)" : "COMMON YEAR (365 Days)");
        }
    }
}

/*
 * Time Complexity: O(1) - Constant arithmetic and boolean condition evaluations.
 * Space Complexity: O(1) - Stack variables only.
 */
