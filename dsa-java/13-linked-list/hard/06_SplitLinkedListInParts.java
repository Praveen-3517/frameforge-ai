/*
 * Problem Statement:
 * Given the head of a singly linked list and an integer k, split the linked list into
 * k consecutive linked list parts. The length of each part should be as equal as possible:
 * no two parts should have a size differing by more than one. This may lead to some parts
 * being null. The parts should be in the order of occurrence in the input list, and parts
 * occurring earlier should always have a size greater than or equal to parts occurring later.
 * (LeetCode 725: Split Linked List in Parts)
 * 
 * Example:
 * Input: head = [1,2,3,4,5,6,7,8,9,10], k = 3
 * Output: [[1,2,3,4],[5,6,7],[8,9,10]]
 * 
 * Asked in: Amazon, Google, Microsoft
 */

class SplitLinkedListInParts {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    public static ListNode[] splitListToParts(ListNode head, int k) {
        ListNode[] parts = new ListNode[k];

        // 1. Calculate total length
        int totalLen = 0;
        ListNode curr = head;
        while (curr != null) {
            totalLen++;
            curr = curr.next;
        }

        // 2. Base size per part and remaining extra elements to distribute to earliest parts
        int baseSize = totalLen / k;
        int extra = totalLen % k;

        curr = head;
        for (int i = 0; i < k; i++) {
            if (curr == null) {
                parts[i] = null;
                continue;
            }

            parts[i] = curr;
            int currentPartSize = baseSize + (i < extra ? 1 : 0);

            // Traverse to the end of this part
            for (int j = 1; j < currentPartSize; j++) {
                curr = curr.next;
            }

            // Sever the link to start next part
            ListNode nextPartHead = curr.next;
            curr.next = null;
            curr = nextPartHead;
        }

        return parts;
    }

    private static ListNode buildList(int... vals) {
        ListNode dummy = new ListNode(0);
        ListNode curr = dummy;
        for (int v : vals) {
            curr.next = new ListNode(v);
            curr = curr.next;
        }
        return dummy.next;
    }

    private static void printList(ListNode head) {
        if (head == null) {
            System.out.println("[]");
            return;
        }
        ListNode curr = head;
        System.out.print("[");
        while (curr != null) {
            System.out.print(curr.val + (curr.next != null ? ", " : ""));
            curr = curr.next;
        }
        System.out.println("]");
    }

    public static void main(String[] args) {
        ListNode list = buildList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        int k = 3;

        System.out.println("--- Splitting List into " + k + " Balanced Parts ---");
        ListNode[] parts = splitListToParts(list, k);
        for (int i = 0; i < parts.length; i++) {
            System.out.print("Part #" + (i + 1) + ": ");
            printList(parts[i]);
        }
    }
}

/*
 * Time Complexity: O(N + k) where N is total nodes in list.
 * Space Complexity: O(k) for output array of heads.
 */
