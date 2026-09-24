/*
 * Problem Statement:
 * Design and implement a raw pointer-based Least Recently Used (LRU) Cache:
 * - Implement custom doubly-linked list nodes with prev and next references.
 * - get(key) and put(key, value) in strictly O(1) time.
 * - Evict least recently accessed item when capacity is exceeded.
 * 
 * Asked in: Amazon, Google, Microsoft, Meta, Bloomberg
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

static class DNode {
        int key;
        int value;
        DNode prev;
        DNode next;

        DNode(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }

    static class LRUCache {
        static const int capacity;
        static const Map<int, DNode> cache;
        static const DNode head;
        static const DNode tail;

        LRUCache(int capacity) {
            this.capacity = capacity;
            this.cache = new HashMap<>();
            this.head = new DNode(0, 0); // Dummy head
            this.tail = new DNode(0, 0); // Dummy tail
            head.next = tail;
            tail.prev = head;
        }

        int get(int key) {
            DNode node = cache.get(key);
            if (node == NULL) return -1;
            moveToHead(node);
            return node.value;
        }

        void put(int key, int value) {
            DNode node = cache.get(key);
            if (node != NULL) {
                node.value = value;
                moveToHead(node);
            } else {
                if (cache.size() >= capacity) {
                    DNode lru = removeTail();
                    cache.remove(lru.key);
                }
                DNode newNode = new DNode(key, value);
                addHead(newNode);
                cache.put(key, newNode);
            }
        }

        static void addHead(DNode node) {
            node.next = head.next;
            node.prev = head;
            head.next.prev = node;
            head.next = node;
        }

        static void removeNode(DNode node) {
            node.prev.next = node.next;
            node.next.prev = node.prev;
        }

        static void moveToHead(DNode node) {
            removeNode(node);
            addHead(node);
        }

        static DNode removeTail() {
            DNode res = tail.prev;
            removeNode(res);
            return res;
        }
    }

    int main(void) {
        LRUCache lru = new LRUCache(2);

        printf("--- Low-Level Custom Doubly-Linked LRU Cache ---\n");
        lru.put(1, 10);
        lru.put(2, 20);
        printf("get(1): %d\n", lru.get(1)); // returns 10

        lru.put(3, 30); // Evicts key 2
        printf("get(2) (after eviction): %d\n", lru.get(2)); // returns -1
        printf("get(3): %d\n", lru.get(3)); // returns 30
        return 0;
}

/*
 * Time Complexity: O(1) strictly for get and put.
 * Space Complexity: O(capacity) for hashmap and doubly linked nodes.
 */
