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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

int minTransfers(int** transactions) {
        Map<int, int> balanceMap = new HashMap<>();

        for (int* t : transactions) {
            int from = t[0], to = t[1], amount = t[2];
            balanceMap.put(from, balanceMap.getOrDefault(from, 0) - amount);
            balanceMap.put(to, balanceMap.getOrDefault(to, 0) + amount);
        }

        int* debtList = new ArrayList<>();
        for (int b : balanceMap.values()) {
            if (b != 0) {
                debtList.add(b);
            }
        }

        return dfs(0, debtList);
    }

    static int dfs(int start, int* debts) {
        // Skip settled balances
        while (start < debts.size() && debts.get(start) == 0) {
            start++;
        }
        if (start == debts.size()) return 0;

        int minTx = INT_MAX;
        int currentDebt = debts.get(start);

        for (int j = start + 1; j < debts.size(); j++) {
            int nextDebt = debts.get(j);

            // Conditional Guard: Only match debtors with creditors (opposite signs)
            if ((long long) currentDebt * nextDebt < 0) {
                debts.set(j, nextDebt + currentDebt);
                minTx = MIN(minTx, 1 + dfs(start + 1, debts));
                debts.set(j, nextDebt); // Backtrack

                // Powerful Pruning Condition: If exact zero balance achieved, optimal choice made
                if (currentDebt + nextDebt == 0) {
                    break;
                }
            }
        }

        return minTx;
    }

    int main(void) {
        printf("=== LeetCode 465: Optimal Account Balancing (Debt Settlement) ===\n");

        int[][][] testCases = {
            { { 0, 1, 10 }, { 2, 0, 5 } },                     // Needs 2 tx
            { { 0, 1, 10 }, { 1, 0, 1 }, { 1, 2, 5 }, { 2, 0, 5 } }, // Needs 1 tx
            { { 0, 1, 1 }, { 1, 2, 1 }, { 2, 0, 1 } }          // Circular: 0 tx needed!
        };

        for (int** txs : testCases) {
            int minTx = minTransfers(txs);
            printf("Transactions: %d records ==> Minimum Settlement Tx: %d\n",
                    n, minTx);
        }
        return 0;
}

/*
 * Time Complexity: O(N!) where N is the number of unsettled accounts (N <= 12 in practice).
 * Space Complexity: O(N) - Recursion call stack and debts array.
 */
