import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Problem Statement:
 * Given an array of transactions where `transactions[i] = [from, to, amount]` indicates that
 * person `from` gave `amount` to person `to`.
 * Return the minimum number of transactions required to settle the debt completely.
 * (LeetCode 465: Optimal Account Balancing - Hard).
 *
 * Asked in: Google, Uber, Amazon, Airbnb
 *
 * Approach:
 * - Net Balance Ledger + Backtracking with Pruning:
 *   1. Calculate net balance for each person:
 *      Debtor loses money (`balance[from] -= amount`), creditor gains (`balance[to] += amount`).
 *   2. Filter out individuals whose net balance is already 0 (they need 0 transactions).
 *   3. Collect remaining non-zero balances into a list `debtList`.
 *   4. Backtracking `dfs(start)`:
 *      Skip any indices that are currently 0.
 *      For the current person `debtList[start]`, look ahead for any person `j` with opposite sign:
 *      `debtList[start] * debtList[j] < 0`.
 *      Transact: `debtList[j] += debtList[start]`.
 *      Recurse: `1 + dfs(start + 1)`.
 *      Backtrack: `debtList[j] -= debtList[start]`.
 *      Pruning: If `debtList[start] + debtList[j] == 0`, this is a perfect 2-party settlement;
 *      break immediately without testing other pairs!
 */
class OptimalAccountBalancing {

    public static int minTransfers(int[][] transactions) {
        Map<Integer, Integer> balanceMap = new HashMap<>();

        for (int[] t : transactions) {
            int from = t[0], to = t[1], amount = t[2];
            balanceMap.put(from, balanceMap.getOrDefault(from, 0) - amount);
            balanceMap.put(to, balanceMap.getOrDefault(to, 0) + amount);
        }

        List<Integer> debtList = new ArrayList<>();
        for (int b : balanceMap.values()) {
            if (b != 0) {
                debtList.add(b);
            }
        }

        return dfs(0, debtList);
    }

    private static int dfs(int start, List<Integer> debts) {
        // Skip settled balances
        while (start < debts.size() && debts.get(start) == 0) {
            start++;
        }
        if (start == debts.size()) return 0;

        int minTx = Integer.MAX_VALUE;
        int currentDebt = debts.get(start);

        for (int j = start + 1; j < debts.size(); j++) {
            int nextDebt = debts.get(j);

            // Conditional Guard: Only match debtors with creditors (opposite signs)
            if ((long) currentDebt * nextDebt < 0) {
                debts.set(j, nextDebt + currentDebt);
                minTx = Math.min(minTx, 1 + dfs(start + 1, debts));
                debts.set(j, nextDebt); // Backtrack

                // Powerful Pruning Condition: If exact zero balance achieved, optimal choice made
                if (currentDebt + nextDebt == 0) {
                    break;
                }
            }
        }

        return minTx;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 465: Optimal Account Balancing (Debt Settlement) ===");

        int[][][] testCases = {
            { { 0, 1, 10 }, { 2, 0, 5 } },                     // Needs 2 tx
            { { 0, 1, 10 }, { 1, 0, 1 }, { 1, 2, 5 }, { 2, 0, 5 } }, // Needs 1 tx
            { { 0, 1, 1 }, { 1, 2, 1 }, { 2, 0, 1 } }          // Circular: 0 tx needed!
        };

        for (int[][] txs : testCases) {
            int minTx = minTransfers(txs);
            System.out.printf("Transactions: %d records ==> Minimum Settlement Tx: %d%n",
                    txs.length, minTx);
        }
    }
}

/*
 * Time Complexity: O(N!) where N is the number of unsettled accounts (N <= 12 in practice).
 * Space Complexity: O(N) - Recursion call stack and debts array.
 */
