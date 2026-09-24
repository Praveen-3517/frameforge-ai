/**
 * Problem: Implement Trie / Prefix Tree (LeetCode 208)
 * Asked in: Amazon, Google, Microsoft, Apple, Twitter
 * 
 * A trie (pronounced "try") or prefix tree is a tree data structure used to efficiently
 * store and retrieve keys in a dataset of strings.
 * Implement the Trie class with:
 * - void insert(String word)
 * - boolean search(String word)
 * - boolean startsWith(String prefix)
 * 
 * Approach:
 * Each TrieNode contains:
 * - TrieNode[] children of size 26 (for lowercase English letters 'a'-'z').
 * - boolean isEndOfWord indicating whether a complete word terminates here.
 * 
 * Time Complexity:
 * - insert: O(L) where L is string length.
 * - search: O(L).
 * - startsWith: O(L).
 * Space Complexity: O(Total characters inserted * 26).
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

static class TrieNode {
        TrieNode[] children = new TrieNode[26];
        bool isEndOfWord = false;
    }

    static const TrieNode root;

    ImplementTriePrefixTree() {
        root = new TrieNode();
    }

    void insert(const char* word) {
        TrieNode curr = root;
        for (int i = 0; i < ((int)strlen(word)); i++) {
            int idx = word[i] - 'a';
            if (curr.children[idx] == NULL) {
                curr.children[idx] = new TrieNode();
            }
            curr = curr.children[idx];
        }
        curr.isEndOfWord = true;
    }

    bool search(const char* word) {
        TrieNode node = findNode(word);
        return node != NULL && node.isEndOfWord;
    }

    bool startsWith(const char* prefix) {
        return findNode(prefix) != NULL;
    }

    static TrieNode findNode(const char* str) {
        TrieNode curr = root;
        for (int i = 0; i < ((int)strlen(str)); i++) {
            int idx = str[i] - 'a';
            if (curr.children[idx] == NULL) {
                return NULL;
            }
            curr = curr.children[idx];
        }
        return curr;
    }

    int main(void) {
        ImplementTriePrefixTree trie = new ImplementTriePrefixTree();
        trie.insert("apple");
        printf("search('apple'): " + trie.search("apple") + " (Expected: true)\n");
        printf("search('app'): " + trie.search("app") + " (Expected: false)\n");
        printf("startsWith('app'): " + trie.startsWith("app") + " (Expected: true)\n");
        trie.insert("app");
        printf("search('app'): " + trie.search("app") + " (Expected: true)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
