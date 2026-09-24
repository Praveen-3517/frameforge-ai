/*
 * Problem Statement:
 * Design a Data Structure for Least Recently Used (LRU) Cache following OOP principles:
 * - Implement get(key) and put(key, value) in O(1) time complexity.
 * - Encapsulate node manipulation within a DoublyLinkedList component.
 * - Evict least recently accessed items when capacity is reached.
 * 
 * Asked in: Amazon, Microsoft, Facebook/Meta, Google, Bloomberg, Apple
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

static class DoublyLinkedList {
        static const Node head, tail;

        DoublyLinkedList() {
            head = new Node(0, 0); // dummy head
            tail = new Node(0, 0); // dummy tail
            head.next = tail;
            tail.prev = head;
        }

        void addFirst(Node node) {
            node.next = head.next;
            node.prev = head;
            head.next.prev = node;
            head.next = node;
        }

        void remove(Node node) {
            node.prev.next = node.next;
            node.next.prev = node.prev;
        }

        void moveToHead(Node node) {
            remove(node);
            addFirst(node);
        }

        Node removeLast() {
            if (tail.prev == head) return NULL;
            Node last = tail.prev;
            remove(last);
            return last;
        }
    }

    static class LRUCache {
        static const int capacity;
        static const Map<int, Node> map;
        static const DoublyLinkedList dll;

        LRUCache(int capacity) {
            this.capacity = capacity;
            this.map = new HashMap<>();
            this.dll = new DoublyLinkedList();
        }

        int get(int key) {
            Node node = map.get(key);
            if (node == NULL) return -1;
            dll.moveToHead(node);
            return node.value;
        }

        void put(int key, int value) {
            Node node = map.get(key);
            if (node != NULL) {
                node.value = value;
                dll.moveToHead(node);
            } else {
                if (map.size() >= capacity) {
                    Node evicted = dll.removeLast();
                    if (evicted != NULL) {
                        map.remove(evicted.key);
                    }
                }
                Node newNode = new Node(key, value);
                dll.addFirst(newNode);
                map.put(key, newNode);
            }
        }
    }

    int main(void) {
        LRUCache cache = new LRUCache(2);

        printf("--- LRU Cache OOP Demonstration (Capacity = 2) ---\n");
        cache.put(1, 1); // cache: {1=1}
        cache.put(2, 2); // cache: {2=2, 1=1}
        printf("cache.get(1): %d\n", cache.get(1)); // returns 1, cache: {1=1, 2=2}

        cache.put(3, 3); // evicts key 2, cache: {3=3, 1=1}
        printf("cache.get(2) (after eviction): %d\n", cache.get(2)); // returns -1

        cache.put(4, 4); // evicts key 1, cache: {4=4, 3=3}
        printf("cache.get(1) (after eviction): %d\n", cache.get(1)); // returns -1
        printf("cache.get(3): %d\n", cache.get(3)); // returns 3
        printf("cache.get(4): %d\n", cache.get(4)); // returns 4
        return 0;
}

/*
 * Time Complexity: O(1) for both get() and put() operations.
 * Space Complexity: O(capacity) for hashmap and doubly linked list nodes.
 */
