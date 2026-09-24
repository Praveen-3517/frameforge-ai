/**
 * Problem: Huffman Coding (Lossless Data Compression)
 * Asked in: Google, Microsoft, Adobe, Cisco
 * 
 * Implement complete Huffman Coding algorithm using a PriorityQueue:
 * 1. Count character frequencies.
 * 2. Build Huffman Tree greedily by repeatedly merging the two lowest-frequency subtrees.
 * 3. Generate variable-length prefix codes.
 * 4. Encode text into binary bitstring.
 * 5. Decode bitstring back to original text.
 * 
 * Time Complexity: O(N log K) where N is text length and K is unique characters count.
 * Space Complexity: O(K) for Huffman Tree and prefix code map.
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

static class HuffmanNode {
        char ch;
        int freq;
        HuffmanNode left, right;

        HuffmanNode(char ch, int freq) {
            this.ch = ch;
            this.freq = freq;
        }

        HuffmanNode(int freq, HuffmanNode left, HuffmanNode right) {
            this.ch = '\0';
            this.freq = freq;
            this.left = left;
            this.right = right;
        }

        bool isLeaf() {
            return left == NULL && right == NULL;
        }
    }

    static const Map<char, const char*> charToCode = new HashMap<>();
    static HuffmanNode root;

    void buildTree(const char* text) {
        Map<char, int> freqMap = new HashMap<>();
        for (size_t _idx = 0; _idx < sizeof(text)/sizeof(text[0]); _idx++) {
        char c = text[_idx];
            freqMap.put(c, freqMap.getOrDefault(c, 0) + 1);
        }

        PriorityQueue<HuffmanNode> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a.freq));
        for (Map.Entry<char, int> entry : freqMap.entrySet()) {
            pq.offer(new HuffmanNode(entry.getKey(), entry.getValue()));
        }

        while (pq.size() > 1) {
            HuffmanNode left = pq.poll();
            HuffmanNode right = pq.poll();
            HuffmanNode parent = new HuffmanNode(left.freq + right.freq, left, right);
            pq.offer(parent);
        }

        root = pq.poll();
        generateCodes(root, "");
    }

    static void generateCodes(HuffmanNode node, const char* code) {
        if (node == NULL) return;
        if (node.isLeaf()) {
            charToCode.put(node.ch, code.isEmpty() ? "0" : code);
            return;
        }
        generateCodes(node.left, code + "0");
        generateCodes(node.right, code + "1");
    }

    const char* encode(const char* text) {
        StringBuilder sb = new StringBuilder();
        for (size_t _idx = 0; _idx < sizeof(text)/sizeof(text[0]); _idx++) {
        char c = text[_idx];
            sb.append(charToCode.get(c));
        }
        return sb.toString();
    }

    const char* decode(const char* encodedBits) {
        StringBuilder sb = new StringBuilder();
        HuffmanNode curr = root;

        for (size_t _idx = 0; _idx < sizeof(encodedBits)/sizeof(encodedBits[0]); _idx++) {
        char bit = encodedBits[_idx];
            curr = (bit == '0') ? curr.left : curr.right;

            if (curr.isLeaf()) {
                sb.append(curr.ch);
                curr = root;
            }
        }

        return sb.toString();
    }

    int main(void) {
        HuffmanCodingLosslessCompression huffman = new HuffmanCodingLosslessCompression();
        const char* text = "abracadabra";

        huffman.buildTree(text);
        const char* encoded = huffman.encode(text);
        const char* decoded = huffman.decode(encoded);

        printf("Original Text: %d\n", text);
        printf("Encoded Bits: %d\n", encoded);
        printf("Decoded Text: %d\n", decoded);
        printf("Match: %d\n", (strcmp(text, decoded) == 0));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
