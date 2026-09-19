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

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

class FlattenNestedListIteratorRecursion {

    // Helper interface representing a nested element
    interface NestedInteger {
        boolean isInteger();
        Integer getInteger();
        List<NestedInteger> getList();
    }

    static class SingleInt implements NestedInteger {
        private final int val;
        SingleInt(int val) { this.val = val; }
        public boolean isInteger() { return true; }
        public Integer getInteger() { return val; }
        public List<NestedInteger> getList() { return null; }
    }

    static class IntList implements NestedInteger {
        private final List<NestedInteger> list = new ArrayList<>();
        IntList(NestedInteger... items) {
            for (NestedInteger item : items) list.add(item);
        }
        public boolean isInteger() { return false; }
        public Integer getInteger() { return null; }
        public List<NestedInteger> getList() { return list; }
    }

    // Recursive Flattener
    static class NestedIterator implements Iterator<Integer> {
        private final List<Integer> flattened = new ArrayList<>();
        private int cursor = 0;

        public NestedIterator(List<NestedInteger> nestedList) {
            flattenRecursively(nestedList);
        }

        private void flattenRecursively(List<NestedInteger> list) {
            if (list == null) return;
            for (NestedInteger item : list) {
                if (item.isInteger()) {
                    flattened.add(item.getInteger());
                } else {
                    flattenRecursively(item.getList());
                }
            }
        }

        @Override
        public boolean hasNext() {
            return cursor < flattened.size();
        }

        @Override
        public Integer next() {
            return flattened.get(cursor++);
        }
    }

    public static void main(String[] args) {
        // Build [[1,1], 2, [1,1]]
        List<NestedInteger> input = new ArrayList<>();
        input.add(new IntList(new SingleInt(1), new SingleInt(1)));
        input.add(new SingleInt(2));
        input.add(new IntList(new SingleInt(1), new SingleInt(1)));

        NestedIterator it = new NestedIterator(input);
        List<Integer> result = new ArrayList<>();
        while (it.hasNext()) {
            result.add(it.next());
        }

        System.out.println("--- Flatten Nested List Iterator ---");
        System.out.println("Flattened output: " + result);
    }
}

/*
 * Time Complexity: O(N) to flatten all N integers. Next() and hasNext() are O(1).
 * Space Complexity: O(D + N) where D is maximum nesting depth and N is total integers.
 */
