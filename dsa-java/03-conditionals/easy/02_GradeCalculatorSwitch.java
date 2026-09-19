/**
 * Problem Statement:
 * Given a student's percentage score (0 to 100), assign a letter grade based on the following scale:
 *   90 - 100 : A (Outstanding)
 *   80 - 89  : B (Very Good)
 *   70 - 79  : C (Good)
 *   60 - 69  : D (Satisfactory)
 *   0  - 59  : F (Fail)
 * Implement using:
 * 1. Traditional `if-else` ladder.
 * 2. Modern Java switch expression using `score / 10` integer division bucketing.
 *
 * Asked in: TCS, Infosys, Capgemini, Wipro
 *
 * Approach:
 * - Integer division bucketing:
 *   Dividing score by 10 maps ranges:
 *   100/10 = 10, 90..99/10 = 9 -> Grade A
 *   80..89/10 = 8 -> Grade B
 *   70..79/10 = 7 -> Grade C
 *   60..69/10 = 6 -> Grade D
 *   0..59/10  = 0..5 -> Grade F
 * - Use modern arrow switch syntax (`case 10, 9 -> "A"`).
 */
class GradeCalculatorSwitch {

    // Method 1: if-else ladder
    public static String getGradeIfElse(int score) {
        if (score < 0 || score > 100) return "Invalid Score";
        if (score >= 90) return "A";
        if (score >= 80) return "B";
        if (score >= 70) return "C";
        if (score >= 60) return "D";
        return "F";
    }

    // Method 2: Modern Java switch expression with range bucketing
    public static String getGradeSwitch(int score) {
        if (score < 0 || score > 100) return "Invalid Score";

        return switch (score / 10) {
            case 10, 9 -> "A";
            case 8     -> "B";
            case 7     -> "C";
            case 6     -> "D";
            default    -> "F";
        };
    }

    public static void main(String[] args) {
        System.out.println("=== Grade Calculator: if-else Ladder vs Modern Switch ===");

        int[] scores = { 100, 95, 88, 73, 62, 59, 0, 105, -5 };

        for (int s : scores) {
            String g1 = getGradeIfElse(s);
            String g2 = getGradeSwitch(s);
            System.out.printf("Score: %4d ==> if-else: %-13s | switch: %-13s%n", s, g1, g2);
        }
    }
}

/*
 * Time Complexity: O(1) - Constant time range lookup.
 * Space Complexity: O(1) - Uses no dynamic heap storage.
 */
