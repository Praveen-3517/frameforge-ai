/*
 * Problem Statement:
 * Design and implement a raw pointer-based Least Recently Used (LRU) Cache:
 * - Implement custom doubly-linked list nodes with prev and next references.
 * - get(key) and put(key, value) in strictly O(1) time.
 * - Evict least recently accessed item when capacity is exceeded.
 * 
 * Asked in: Amazon, Google, Microsoft, Meta, Bloomberg
 */

import java.util.HashMap;
import java.util.Map;

class LRUCacheCustomDoublyList {

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
        private final int capacity;
        private final Map<Integer, DNode> cache;
        private final DNode head;
        private final DNode tail;

        public LRUCache(int capacity) {
            this.capacity = capacity;
            this.cache = new HashMap<>();
            this.head = new DNode(0, 0); // Dummy head
            this.tail = new DNode(0, 0); // Dummy tail
            head.next = tail;
            tail.prev = head;
        }

        public int get(int key) {
            DNode node = cache.get(key);
            if (node == null) return -1;
            moveToHead(node);
            return node.value;
        }

        public void put(int key, int value) {
            DNode node = cache.get(key);
            if (node != null) {
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

        private void addHead(DNode node) {
            node.next = head.next;
            node.prev = head;
            head.next.prev = node;
            head.next = node;
        }

        private void removeNode(DNode node) {
            node.prev.next = node.next;
            node.next.prev = node.prev;
        }

        private void moveToHead(DNode node) {
            removeNode(node);
            addHead(node);
        }

        private DNode removeTail() {
            DNode res = tail.prev;
            removeNode(res);
            return res;
        }
    }

    public static void main(String[] args) {
        LRUCache lru = new LRUCache(2);

        System.out.println("--- Low-Level Custom Doubly-Linked LRU Cache ---");
        lru.put(1, 10);
        lru.put(2, 20);
        System.out.println("get(1): " + lru.get(1)); // returns 10

        lru.put(3, 30); // Evicts key 2
        System.out.println("get(2) (after eviction): " + lru.get(2)); // returns -1
        System.out.println("get(3): " + lru.get(3)); // returns 30
    }
}

/*
 * Time Complexity: O(1) strictly for get and put.
 * Space Complexity: O(capacity) for hashmap and doubly linked nodes.
 */
