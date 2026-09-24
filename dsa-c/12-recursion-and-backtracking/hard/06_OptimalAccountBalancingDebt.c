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
        Map<int, long long long long> balances = new HashMap<>();

        // 1. Calculate net balance for every person
        for (int* t : transactions) {
            balances.put(t[0], balances.getOrDefault(t[0], 0L) - t[2]);
            balances.put(t[1], balances.getOrDefault(t[1], 0L) + t[2]);
        }

        // 2. Filter out settled persons (balance == 0)
        int* debtList = new ArrayList<>();
        for (long long val : balances.values()) {
            if (val != 0) debtList.add(val);
        }

        return dfs(0, debtList);
    }

    static int dfs(int start, int* debts) {
        // Skip already balanced entries
        while (start < debts.size() && debts.get(start) == 0) {
            start++;
        }
        if (start == debts.size()) return 0;

        int minTx = INT_MAX;
        long long currDebt = debts.get(start);

        for (int i = start + 1; i < debts.size(); i++) {
            // Opposite signs can settle debt together
            if (currDebt * debts.get(i) < 0) {
                debts.set(i, debts.get(i) + currDebt);
                minTx = MIN(minTx, 1 + dfs(start + 1, debts));
                debts.set(i, debts.get(i) - currDebt); // backtrack

                // Pruning: If exact match settles both to 0, no need to explore alternative splits!
                if (currDebt + debts.get(i) == 0) break;
            }
        }

        return minTx;
    }

    int main(void) {
        int** tx1 = {{0, 1, 10}, {2, 0, 5}};
        printf("Transactions: [[0,1,10], [2,0,5]]\n");
        printf("Min transactions to settle: " + minTransfers(tx1) + " (Expected: 2)\n");

        int** tx2 = {{0, 1, 10}, {1, 0, 1}, {1, 2, 5}, {2, 0, 5}};
        printf("\nTransactions: [[0,1,10], [1,0,1], [1,2,5], [2,0,5]]\n");
        printf("Min transactions to settle: " + minTransfers(tx2) + " (Expected: 1)\n");
        return 0;
}

/*
 * Time Complexity: O(N!) in worst case where N is number of unsettled people (typically N <= 12).
 * Space Complexity: O(N) recursion stack and balance list.
 */
