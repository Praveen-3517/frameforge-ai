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
class ImplementTriePrefixTree {

    static class TrieNode {
        TrieNode[] children = new TrieNode[26];
        boolean isEndOfWord = false;
    }

    private final TrieNode root;

    public ImplementTriePrefixTree() {
        root = new TrieNode();
    }

    public void insert(String word) {
        TrieNode curr = root;
        for (int i = 0; i < word.length(); i++) {
            int idx = word.charAt(i) - 'a';
            if (curr.children[idx] == null) {
                curr.children[idx] = new TrieNode();
            }
            curr = curr.children[idx];
        }
        curr.isEndOfWord = true;
    }

    public boolean search(String word) {
        TrieNode node = findNode(word);
        return node != null && node.isEndOfWord;
    }

    public boolean startsWith(String prefix) {
        return findNode(prefix) != null;
    }

    private TrieNode findNode(String str) {
        TrieNode curr = root;
        for (int i = 0; i < str.length(); i++) {
            int idx = str.charAt(i) - 'a';
            if (curr.children[idx] == null) {
                return null;
            }
            curr = curr.children[idx];
        }
        return curr;
    }

    public static void main(String[] args) {
        ImplementTriePrefixTree trie = new ImplementTriePrefixTree();
        trie.insert("apple");
        System.out.println("search('apple'): " + trie.search("apple") + " (Expected: true)");
        System.out.println("search('app'): " + trie.search("app") + " (Expected: false)");
        System.out.println("startsWith('app'): " + trie.startsWith("app") + " (Expected: true)");
        trie.insert("app");
        System.out.println("search('app'): " + trie.search("app") + " (Expected: true)");
    }
}
