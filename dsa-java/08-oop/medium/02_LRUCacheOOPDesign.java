/*
 * Problem Statement:
 * Design a Data Structure for Least Recently Used (LRU) Cache following OOP principles:
 * - Implement get(key) and put(key, value) in O(1) time complexity.
 * - Encapsulate node manipulation within a DoublyLinkedList component.
 * - Evict least recently accessed items when capacity is reached.
 * 
 * Asked in: Amazon, Microsoft, Facebook/Meta, Google, Bloomberg, Apple
 */

import java.util.HashMap;
import java.util.Map;

class LRUCacheOOPDesign {

    static class Node {
        int key, value;
        Node prev, next;

        Node(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }

    static class DoublyLinkedList {
        private final Node head, tail;

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
            if (tail.prev == head) return null;
            Node last = tail.prev;
            remove(last);
            return last;
        }
    }

    static class LRUCache {
        private final int capacity;
        private final Map<Integer, Node> map;
        private final DoublyLinkedList dll;

        public LRUCache(int capacity) {
            this.capacity = capacity;
            this.map = new HashMap<>();
            this.dll = new DoublyLinkedList();
        }

        public int get(int key) {
            Node node = map.get(key);
            if (node == null) return -1;
            dll.moveToHead(node);
            return node.value;
        }

        public void put(int key, int value) {
            Node node = map.get(key);
            if (node != null) {
                node.value = value;
                dll.moveToHead(node);
            } else {
                if (map.size() >= capacity) {
                    Node evicted = dll.removeLast();
                    if (evicted != null) {
                        map.remove(evicted.key);
                    }
                }
                Node newNode = new Node(key, value);
                dll.addFirst(newNode);
                map.put(key, newNode);
            }
        }
    }

    public static void main(String[] args) {
        LRUCache cache = new LRUCache(2);

        System.out.println("--- LRU Cache OOP Demonstration (Capacity = 2) ---");
        cache.put(1, 1); // cache: {1=1}
        cache.put(2, 2); // cache: {2=2, 1=1}
        System.out.println("cache.get(1): " + cache.get(1)); // returns 1, cache: {1=1, 2=2}

        cache.put(3, 3); // evicts key 2, cache: {3=3, 1=1}
        System.out.println("cache.get(2) (after eviction): " + cache.get(2)); // returns -1

        cache.put(4, 4); // evicts key 1, cache: {4=4, 3=3}
        System.out.println("cache.get(1) (after eviction): " + cache.get(1)); // returns -1
        System.out.println("cache.get(3): " + cache.get(3)); // returns 3
        System.out.println("cache.get(4): " + cache.get(4)); // returns 4
    }
}

/*
 * Time Complexity: O(1) for both get() and put() operations.
 * Space Complexity: O(capacity) for hashmap and doubly linked list nodes.
 */
