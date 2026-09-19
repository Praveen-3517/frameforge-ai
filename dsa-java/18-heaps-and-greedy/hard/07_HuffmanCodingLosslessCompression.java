import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;

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
class HuffmanCodingLosslessCompression {

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

        boolean isLeaf() {
            return left == null && right == null;
        }
    }

    private final Map<Character, String> charToCode = new HashMap<>();
    private HuffmanNode root;

    public void buildTree(String text) {
        Map<Character, Integer> freqMap = new HashMap<>();
        for (char c : text.toCharArray()) {
            freqMap.put(c, freqMap.getOrDefault(c, 0) + 1);
        }

        PriorityQueue<HuffmanNode> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a.freq));
        for (Map.Entry<Character, Integer> entry : freqMap.entrySet()) {
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

    private void generateCodes(HuffmanNode node, String code) {
        if (node == null) return;
        if (node.isLeaf()) {
            charToCode.put(node.ch, code.isEmpty() ? "0" : code);
            return;
        }
        generateCodes(node.left, code + "0");
        generateCodes(node.right, code + "1");
    }

    public String encode(String text) {
        StringBuilder sb = new StringBuilder();
        for (char c : text.toCharArray()) {
            sb.append(charToCode.get(c));
        }
        return sb.toString();
    }

    public String decode(String encodedBits) {
        StringBuilder sb = new StringBuilder();
        HuffmanNode curr = root;

        for (char bit : encodedBits.toCharArray()) {
            curr = (bit == '0') ? curr.left : curr.right;

            if (curr.isLeaf()) {
                sb.append(curr.ch);
                curr = root;
            }
        }

        return sb.toString();
    }

    public static void main(String[] args) {
        HuffmanCodingLosslessCompression huffman = new HuffmanCodingLosslessCompression();
        String text = "abracadabra";

        huffman.buildTree(text);
        String encoded = huffman.encode(text);
        String decoded = huffman.decode(encoded);

        System.out.println("Original Text: " + text);
        System.out.println("Encoded Bits: " + encoded);
        System.out.println("Decoded Text: " + decoded);
        System.out.println("Match: " + text.equals(decoded));
    }
}
