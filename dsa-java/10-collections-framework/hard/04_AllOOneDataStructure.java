/*
 * Problem Statement:
 * Design a data structure to store the strings' count with the ability to return
 * the strings with minimum and maximum counts in O(1) time complexity.
 * Implement the AllOne class:
 * - inc(String key): Increments the count of the string key by 1.
 * - dec(String key): Decrements the count of the string key by 1. If 0, remove.
 * - getMaxKey(): Returns one of the keys with maximal count. If empty, return "".
 * - getMinKey(): Returns one of the keys with minimal count. If empty, return "".
 * (LeetCode 432: All O`one Data Structure)
 * 
 * Asked in: Uber, LinkedIn, Google, Amazon
 */

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

class AllOOneDataStructure {

    static class Bucket {
        int count;
        Set<String> keys = new HashSet<>();
        Bucket prev, next;

        Bucket(int count) {
            this.count = count;
        }
    }

    static class AllOne {
        private final Bucket head, tail; // Dummy head and tail
        private final Map<String, Bucket> keyToBucket = new HashMap<>();

        public AllOne() {
            head = new Bucket(0);
            tail = new Bucket(0);
            head.next = tail;
            tail.prev = head;
        }

        public void inc(String key) {
            Bucket currBucket = keyToBucket.get(key);
            if (currBucket == null) {
                // Key does not exist yet. Needs to be placed in bucket with count = 1
                if (head.next.count == 1) {
                    head.next.keys.add(key);
                    keyToBucket.put(key, head.next);
                } else {
                    Bucket newBucket = new Bucket(1);
                    newBucket.keys.add(key);
                    insertAfter(head, newBucket);
                    keyToBucket.put(key, newBucket);
                }
            } else {
                int nextCount = currBucket.count + 1;
                Bucket nextBucket = currBucket.next;
                if (nextBucket.count != nextCount) {
                    nextBucket = new Bucket(nextCount);
                    insertAfter(currBucket, nextBucket);
                }
                nextBucket.keys.add(key);
                keyToBucket.put(key, nextBucket);
                currBucket.keys.remove(key);
                if (currBucket.keys.isEmpty()) {
                    removeBucket(currBucket);
                }
            }
        }

        public void dec(String key) {
            Bucket currBucket = keyToBucket.get(key);
            if (currBucket == null) return;

            currBucket.keys.remove(key);
            if (currBucket.count == 1) {
                keyToBucket.remove(key);
            } else {
                int prevCount = currBucket.count - 1;
                Bucket prevBucket = currBucket.prev;
                if (prevBucket.count != prevCount) {
                    prevBucket = new Bucket(prevCount);
                    insertAfter(currBucket.prev, prevBucket);
                }
                prevBucket.keys.add(key);
                keyToBucket.put(key, prevBucket);
            }

            if (currBucket.keys.isEmpty()) {
                removeBucket(currBucket);
            }
        }

        public String getMaxKey() {
            return tail.prev == head ? "" : tail.prev.keys.iterator().next();
        }

        public String getMinKey() {
            return head.next == tail ? "" : head.next.keys.iterator().next();
        }

        private void insertAfter(Bucket prev, Bucket newBucket) {
            newBucket.next = prev.next;
            newBucket.prev = prev;
            prev.next.prev = newBucket;
            prev.next = newBucket;
        }

        private void removeBucket(Bucket bucket) {
            bucket.prev.next = bucket.next;
            bucket.next.prev = bucket.prev;
        }
    }

    public static void main(String[] args) {
        AllOne allOne = new AllOne();

        System.out.println("--- All O(1) Data Structure ---");
        allOne.inc("hello");
        allOne.inc("hello");
        System.out.println("Max Key: " + allOne.getMaxKey()); // "hello"
        System.out.println("Min Key: " + allOne.getMinKey()); // "hello"

        allOne.inc("leet");
        System.out.println("Max Key: " + allOne.getMaxKey()); // "hello" (count 2)
        System.out.println("Min Key: " + allOne.getMinKey()); // "leet" (count 1)

        allOne.dec("hello");
        allOne.dec("hello");
        System.out.println("After removing 'hello' entirely:");
        System.out.println("Max Key: " + allOne.getMaxKey()); // "leet"
        System.out.println("Min Key: " + allOne.getMinKey()); // "leet"
    }
}

/*
 * Time Complexity: O(1) strictly for inc, dec, getMaxKey, and getMinKey.
 * Space Complexity: O(K) where K is number of unique keys stored.
 */
