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
            node.parentFreq = NULL;
        }

        bool isEmpty() {
            return head.next == tail;
        }

        CacheNode removeLRU() {
            if (isEmpty()) return NULL;
            CacheNode lru = tail.prev;
            removeNode(lru);
            return lru;
        }
    }

    static class LFUCache {
        static const int capacity;
        static const Map<int, CacheNode> keyMap = new HashMap<>();
        static const FreqNode freqHead;
        static const FreqNode freqTail;

        LFUCache(int capacity) {
            this.capacity = capacity;
            freqHead = new FreqNode(0);
            freqTail = new FreqNode(0);
            freqHead.next = freqTail;
            freqTail.prev = freqHead;
        }

        int get(int key) {
            CacheNode node = keyMap.get(key);
            if (node == NULL) return -1;
            incrementFreq(node);
            return node.val;
        }

        void put(int key, int value) {
            if (capacity <= 0) return;

            CacheNode node = keyMap.get(key);
            if (node != NULL) {
                node.val = value;
                incrementFreq(node);
            } else {
                if (keyMap.size() >= capacity) {
                    // Evict from first non-empty freq block
                    FreqNode minFreqNode = freqHead.next;
                    CacheNode evicted = minFreqNode.removeLRU();
                    if (evicted != NULL) {
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

        static void incrementFreq(CacheNode node) {
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

        static void insertFreqBlockAfter(FreqNode prev, FreqNode newBlock) {
            newBlock.next = prev.next;
            newBlock.prev = prev;
            prev.next.prev = newBlock;
            prev.next = newBlock;
        }

        static void removeFreqBlock(FreqNode block) {
            block.prev.next = block.next;
            block.next.prev = block.prev;
        }
    }

    int main(void) {
        LFUCache lfu = new LFUCache(2);

        printf("--- LFU Cache Nested Doubly-Linked Architecture ---\n");
        lfu.put(1, 10);
        lfu.put(2, 20);
        printf("get(1): %d\n", lfu.get(1)); // freq(1)=2, freq(2)=1

        lfu.put(3, 30); // Evicts key 2 (freq = 1)
        printf("get(2) (evicted): %d\n", lfu.get(2)); // returns -1
        printf("get(3): %d\n", lfu.get(3)); // returns 30
        printf("get(1): %d\n", lfu.get(1)); // returns 10
        return 0;
}

/*
 * Time Complexity: O(1) strictly for get and put without hash collisions.
 * Space Complexity: O(capacity) for node allocations.
 */
