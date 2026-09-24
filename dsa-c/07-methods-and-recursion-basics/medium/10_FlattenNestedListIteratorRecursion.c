/*
 * Problem Statement:
 * You are given a nested list of integers nestedList. Each element is either an integer,
 * or a list whose elements may also be integers or other lists.
 * Implement an iterator to flatten it.
 * 
 * Example:
 * Input: [[1,1], 2, [1,1]]
 * Output: [1, 1, 2, 1, 1]
 * 
 * Asked in: Twitter/X, Netflix, Google, Facebook/Meta, LinkedIn
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

// Helper interface representing a nested element
    interface NestedInteger {
        bool isInteger();
        int getInteger();
        int* getList();
    }

    static class SingleInt implements NestedInteger {
        static const int val;
        SingleInt(int val) { this.val = val; }
        bool isInteger() { return true; }
        int getInteger() { return val; }
        int* getList() { return NULL; }
    }

    static class IntList implements NestedInteger {
        static const int* list = new ArrayList<>();
        IntList(NestedInteger... items) {
            for (NestedInteger item : items) list.add(item);
        }
        bool isInteger() { return false; }
        int getInteger() { return NULL; }
        int* getList() { return list; }
    }

    // Recursive Flattener
    static class NestedIterator implements Iterator<int> {
        static const int* flattened = new ArrayList<>();
        static int cursor = 0;

        NestedIterator(int* nestedList) {
            flattenRecursively(nestedList);
        }

        static void flattenRecursively(int* list) {
            if (list == NULL) return;
            for (NestedInteger item : list) {
                if (item.isInteger()) {
                    flattened.add(item.getInteger());
                } else {
                    flattenRecursively(item.getList());
                }
            }
        }

        bool hasNext() {
            return cursor < flattened.size();
        }

        int next() {
            return flattened.get(cursor++);
        }
    }

    int main(void) {
        // Build [[1,1], 2, [1,1]]
        int* input = new ArrayList<>();
        input.add(new IntList(new SingleInt(1), new SingleInt(1)));
        input.add(new SingleInt(2));
        input.add(new IntList(new SingleInt(1), new SingleInt(1)));

        NestedIterator it = new NestedIterator(input);
        int* result = new ArrayList<>();
        while (it.hasNext()) {
            result.add(it.next());
        }

        printf("--- Flatten Nested List Iterator ---\n");
        printf("Flattened output: %d\n", result);
        return 0;
}

/*
 * Time Complexity: O(N) to flatten all N integers. Next() and hasNext() are O(1).
 * Space Complexity: O(D + N) where D is maximum nesting depth and N is total integers.
 */
