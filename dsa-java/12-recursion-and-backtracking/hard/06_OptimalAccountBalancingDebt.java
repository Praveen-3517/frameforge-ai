/*
 * Problem Statement:
 * You are given an array of transactions transactions where transactions[i] = [from_i, to_i, amount_i]
 * indicates that the person with ID from_i gave amount_i to the person with ID to_i.
 * Return the minimum number of transactions required to settle the debt.
 * (LeetCode 465: Optimal Account Balancing)
 * 
 * Example:
 * Input: transactions = [[0,1,10],[2,0,5]]
 * Output: 2
 * 
 * Asked in: Google, Uber, Affirm, Splitwise
 */

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class OptimalAccountBalancingDebt {

    public static int minTransfers(int[][] transactions) {
        Map<Integer, Long> balances = new HashMap<>();

        // 1. Calculate net balance for every person
        for (int[] t : transactions) {
            balances.put(t[0], balances.getOrDefault(t[0], 0L) - t[2]);
            balances.put(t[1], balances.getOrDefault(t[1], 0L) + t[2]);
        }

        // 2. Filter out settled persons (balance == 0)
        List<Long> debtList = new ArrayList<>();
        for (long val : balances.values()) {
            if (val != 0) debtList.add(val);
        }

        return dfs(0, debtList);
    }

    private static int dfs(int start, List<Long> debts) {
        // Skip already balanced entries
        while (start < debts.size() && debts.get(start) == 0) {
            start++;
        }
        if (start == debts.size()) return 0;

        int minTx = Integer.MAX_VALUE;
        long currDebt = debts.get(start);

        for (int i = start + 1; i < debts.size(); i++) {
            // Opposite signs can settle debt together
            if (currDebt * debts.get(i) < 0) {
                debts.set(i, debts.get(i) + currDebt);
                minTx = Math.min(minTx, 1 + dfs(start + 1, debts));
                debts.set(i, debts.get(i) - currDebt); // backtrack

                // Pruning: If exact match settles both to 0, no need to explore alternative splits!
                if (currDebt + debts.get(i) == 0) break;
            }
        }

        return minTx;
    }

    public static void main(String[] args) {
        int[][] tx1 = {{0, 1, 10}, {2, 0, 5}};
        System.out.println("Transactions: [[0,1,10], [2,0,5]]");
        System.out.println("Min transactions to settle: " + minTransfers(tx1) + " (Expected: 2)");

        int[][] tx2 = {{0, 1, 10}, {1, 0, 1}, {1, 2, 5}, {2, 0, 5}};
        System.out.println("\nTransactions: [[0,1,10], [1,0,1], [1,2,5], [2,0,5]]");
        System.out.println("Min transactions to settle: " + minTransfers(tx2) + " (Expected: 1)");
    }
}

/*
 * Time Complexity: O(N!) in worst case where N is number of unsettled people (typically N <= 12).
 * Space Complexity: O(N) recursion stack and balance list.
 */
