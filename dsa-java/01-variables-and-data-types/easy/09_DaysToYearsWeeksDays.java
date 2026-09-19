/**
 * Problem Statement:
 * Given a total count of days as an integer, convert it into years, weeks,
 * and remaining days (assuming standard non-leap year with 365 days).
 *
 * Asked in: Accenture, Wipro, Capgemini
 *
 * Approach:
 * 1. Years = totalDays / 365
 * 2. Remaining days after extracting years = totalDays % 365
 * 3. Weeks = remainingDays / 7
 * 4. Days = remainingDays % 7
 */
class DaysToYearsWeeksDays {

    public static class DurationBreakdown {
        public final int years;
        public final int weeks;
        public final int days;

        public DurationBreakdown(int years, int weeks, int days) {
            this.years = years;
            this.weeks = weeks;
            this.days = days;
        }

        @Override
        public String toString() {
            return years + " Year(s), " + weeks + " Week(s), " + days + " Day(s)";
        }
    }

    public static DurationBreakdown convertDays(int totalDays) {
        if (totalDays < 0) {
            throw new IllegalArgumentException("Days cannot be negative.");
        }
        int years = totalDays / 365;
        int remainderAfterYears = totalDays % 365;
        int weeks = remainderAfterYears / 7;
        int days = remainderAfterYears % 7;

        return new DurationBreakdown(years, weeks, days);
    }

    public static void main(String[] args) {
        int[] testCases = { 373, 1000, 365, 7, 14, 0 };

        System.out.println("=== Days to Years, Weeks, Days Converter ===");
        for (int totalDays : testCases) {
            System.out.printf("%-6d days = %s%n", totalDays, convertDays(totalDays));
        }
    }
}

/*
 * Time Complexity: O(1) - Constant arithmetic division and modulo operations.
 * Space Complexity: O(1) - Primitive record storage.
 */
