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

static class Bucket {
        int count;
        Set<const char*> keys = new HashSet<>();
        Bucket prev, next;

        Bucket(int count) {
            this.count = count;
        }
    }

    static class AllOne {
        static const Bucket head, tail; // Dummy head and tail
        static const Map<const char*, Bucket> keyToBucket = new HashMap<>();

        AllOne() {
            head = new Bucket(0);
            tail = new Bucket(0);
            head.next = tail;
            tail.prev = head;
        }

        void inc(const char* key) {
            Bucket currBucket = keyToBucket.get(key);
            if (currBucket == NULL) {
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

        void dec(const char* key) {
            Bucket currBucket = keyToBucket.get(key);
            if (currBucket == NULL) return;

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

        const char* getMaxKey() {
            return tail.prev == head ? "" : tail.prev.keys.iterator().next();
        }

        const char* getMinKey() {
            return head.next == tail ? "" : head.next.keys.iterator().next();
        }

        static void insertAfter(Bucket prev, Bucket newBucket) {
            newBucket.next = prev.next;
            newBucket.prev = prev;
            prev.next.prev = newBucket;
            prev.next = newBucket;
        }

        static void removeBucket(Bucket bucket) {
            bucket.prev.next = bucket.next;
            bucket.next.prev = bucket.prev;
        }
    }

    int main(void) {
        AllOne allOne = new AllOne();

        printf("--- All O(1) Data Structure ---\n");
        allOne.inc("hello");
        allOne.inc("hello");
        printf("Max Key: %d\n", allOne.getMaxKey()); // "hello"
        printf("Min Key: %d\n", allOne.getMinKey()); // "hello"

        allOne.inc("leet");
        printf("Max Key: %d\n", allOne.getMaxKey()); // "hello" (count 2)
        printf("Min Key: %d\n", allOne.getMinKey()); // "leet" (count 1)

        allOne.dec("hello");
        allOne.dec("hello");
        printf("After removing 'hello' entirely:\n");
        printf("Max Key: %d\n", allOne.getMaxKey()); // "leet"
        printf("Min Key: %d\n", allOne.getMinKey()); // "leet"
        return 0;
}

/*
 * Time Complexity: O(1) strictly for inc, dec, getMaxKey, and getMinKey.
 * Space Complexity: O(K) where K is number of unique keys stored.
 */
