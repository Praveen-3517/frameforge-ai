/*
 * Problem Statement:
 * You are keeping score for a baseball game with strange rules:
 * - Integer x: Record a new score of x.
 * - "+": Record a new score that is the sum of previous two scores.
 * - "D": Record a new score that is double the previous score.
 * - "C": Invalidate and remove the previous score.
 * Return the sum of all the scores on the record after applying all operations.
 * (LeetCode 682: Baseball Game)
 * 
 * Example:
 * Input: ops = ["5","2","C","D","+"]
 * Output: 30
 * 
 * Asked in: Amazon, Bloomberg, Morgan Stanley
 */

import java.util.ArrayDeque;
import java.util.Deque;

class BaseballGameRecordStack {

    public static int calPoints(String[] operations) {
        Deque<Integer> stack = new ArrayDeque<>();

        for (String op : operations) {
            switch (op) {
                case "+":
                    int top = stack.pop();
                    int newTop = top + stack.peek();
                    stack.push(top);
                    stack.push(newTop);
                    break;
                case "D":
                    stack.push(2 * stack.peek());
                    break;
                case "C":
                    stack.pop();
                    break;
                default:
                    stack.push(Integer.parseInt(op));
                    break;
            }
        }

        int total = 0;
        for (int score : stack) total += score;
        return total;
    }

    public static void main(String[] args) {
        String[] ops1 = {"5", "2", "C", "D", "+"};
        System.out.println("Operations: [\"5\",\"2\",\"C\",\"D\",\"+\"] -> Total points: " + calPoints(ops1) + " (Expected: 30)");

        String[] ops2 = {"5", "-2", "4", "C", "D", "9", "+", "+"};
        System.out.println("Operations 2 -> Total points: " + calPoints(ops2) + " (Expected: 27)");
    }
}

/*
 * Time Complexity: O(N) where N is operations count.
 * Space Complexity: O(N) score history stack.
 */
