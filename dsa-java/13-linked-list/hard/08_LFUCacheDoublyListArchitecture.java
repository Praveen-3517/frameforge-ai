/*
 * Problem Statement:
 * Design an LFU (Least Frequently Used) Cache using a Doubly Linked List Architecture:
 * - Each frequency level has its own doubly-linked list of cache nodes.
 * - Frequencies themselves form a doubly-linked list of frequency blocks.
 * - This allows O(1) eviction of the least frequent, least recently used element,
 *   and O(1) elevation of an element to the next frequency block upon access.
 * 
 * Asked in: Amazon, Google, Citadel, Two Sigma
 */

import java.util.HashMap;
import java.util.Map;

class LFUCacheDoublyListArchitecture {

    static class CacheNode {
        int key, val, freq;
        CacheNode prev, next;
        FreqNode parentFreq;

        CacheNode(int key, int val) {
            this.key = key;
            this.val = val;
            this.freq = 1;
        }
    }

    static class FreqNode {
        int freq;
        FreqNode prev, next;
        CacheNode head, tail; // Sentinel nodes for this frequency

        FreqNode(int freq) {
            this.freq = freq;
            head = new CacheNode(0, 0);
            tail = new CacheNode(0, 0);
            head.next = tail;
            tail.prev = head;
        }

        void addNode(CacheNode node) {
            node.next = head.next;
            node.prev = head;
            head.next.prev = node;
            head.next = node;
            node.parentFreq = this;
        }

        void removeNode(CacheNode node) {
            node.prev.next = node.next;
            node.next.prev = node.prev;
            node.parentFreq = null;
        }

        boolean isEmpty() {
            return head.next == tail;
        }

        CacheNode removeLRU() {
            if (isEmpty()) return null;
            CacheNode lru = tail.prev;
            removeNode(lru);
            return lru;
        }
    }

    static class LFUCache {
        private final int capacity;
        private final Map<Integer, CacheNode> keyMap = new HashMap<>();
        private final FreqNode freqHead;
        private final FreqNode freqTail;

        public LFUCache(int capacity) {
            this.capacity = capacity;
            freqHead = new FreqNode(0);
            freqTail = new FreqNode(0);
            freqHead.next = freqTail;
            freqTail.prev = freqHead;
        }

        public int get(int key) {
            CacheNode node = keyMap.get(key);
            if (node == null) return -1;
            incrementFreq(node);
            return node.val;
        }

        public void put(int key, int value) {
            if (capacity <= 0) return;

            CacheNode node = keyMap.get(key);
            if (node != null) {
                node.val = value;
                incrementFreq(node);
            } else {
                if (keyMap.size() >= capacity) {
                    // Evict from first non-empty freq block
                    FreqNode minFreqNode = freqHead.next;
                    CacheNode evicted = minFreqNode.removeLRU();
                    if (evicted != null) {
                        keyMap.remove(evicted.key);
                    }
                    if (minFreqNode.isEmpty()) {
                        removeFreqBlock(minFreqNode);
                    }
                }

                CacheNode newNode = new CacheNode(key, value);
                // Attach to freq = 1 block
                FreqNode f1 = freqHead.next;
                if (f1.freq != 1) {
                    f1 = new FreqNode(1);
                    insertFreqBlockAfter(freqHead, f1);
                }
                f1.addNode(newNode);
                keyMap.put(key, newNode);
            }
        }

        private void incrementFreq(CacheNode node) {
            FreqNode currFreqBlock = node.parentFreq;
            int nextFreqVal = currFreqBlock.freq + 1;
            FreqNode nextFreqBlock = currFreqBlock.next;

            if (nextFreqBlock.freq != nextFreqVal) {
                nextFreqBlock = new FreqNode(nextFreqVal);
                insertFreqBlockAfter(currFreqBlock, nextFreqBlock);
            }

            currFreqBlock.removeNode(node);
            node.freq = nextFreqVal;
            nextFreqBlock.addNode(node);

            if (currFreqBlock.isEmpty()) {
                removeFreqBlock(currFreqBlock);
            }
        }

        private void insertFreqBlockAfter(FreqNode prev, FreqNode newBlock) {
            newBlock.next = prev.next;
            newBlock.prev = prev;
            prev.next.prev = newBlock;
            prev.next = newBlock;
        }

        private void removeFreqBlock(FreqNode block) {
            block.prev.next = block.next;
            block.next.prev = block.prev;
        }
    }

    public static void main(String[] args) {
        LFUCache lfu = new LFUCache(2);

        System.out.println("--- LFU Cache Nested Doubly-Linked Architecture ---");
        lfu.put(1, 10);
        lfu.put(2, 20);
        System.out.println("get(1): " + lfu.get(1)); // freq(1)=2, freq(2)=1

        lfu.put(3, 30); // Evicts key 2 (freq = 1)
        System.out.println("get(2) (evicted): " + lfu.get(2)); // returns -1
        System.out.println("get(3): " + lfu.get(3)); // returns 30
        System.out.println("get(1): " + lfu.get(1)); // returns 10
    }
}

/*
 * Time Complexity: O(1) strictly for get and put without hash collisions.
 * Space Complexity: O(capacity) for node allocations.
 */
