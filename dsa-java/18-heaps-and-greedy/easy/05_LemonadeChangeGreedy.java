/**
 * Problem: Lemonade Change (LeetCode 860)
 * Asked in: Amazon, Google
 * 
 * At a lemonade stand, each lemonade costs $5. Customers are standing in a queue to buy
 * from you and order one at a time. Each customer will only buy one lemonade and pay with
 * either a $5, $10, or $20 bill. You must provide the correct change to each customer.
 * Return true if you can provide every customer with the correct change.
 * 
 * Approach:
 * Greedy Change Strategy:
 * Keep track of counts of $5 bills and $10 bills ($20 bills cannot be given as change).
 * - Customer pays $5: fiveCount++
 * - Customer pays $10: needs $5 change -> if fiveCount > 0, fiveCount--, tenCount++ else return false.
 * - Customer pays $20: needs $15 change.
 *   Greedy Choice: Always prefer giving (one $10 + one $5) over (three $5) bills,
 *   because $5 bills are strictly more versatile!
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class LemonadeChangeGreedy {

    public static boolean lemonadeChange(int[] bills) {
        int five = 0;
        int ten = 0;

        for (int bill : bills) {
            if (bill == 5) {
                five++;
            } else if (bill == 10) {
                if (five == 0) return false;
                five--;
                ten++;
            } else { // bill == 20
                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                } else if (five >= 3) {
                    five -= 3;
                } else {
                    return false;
                }
            }
        }

        return true;
    }

    public static void main(String[] args) {
        int[] bills1 = {5, 5, 5, 10, 20};
        System.out.println("Can provide change 1: " + lemonadeChange(bills1) + " (Expected: true)");

        int[] bills2 = {5, 5, 10, 10, 20};
        System.out.println("Can provide change 2: " + lemonadeChange(bills2) + " (Expected: false)");
    }
}
