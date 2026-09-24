/*
 * Problem Statement:
 * Design a complete Doubly Linked List with Sentinel (dummy head and dummy tail) nodes:
 * - Each node has `prev` and `next` references.
 * - Support `addFirst`, `addLast`, `removeFirst`, `removeLast`, and bidirectional printing.
 * - Sentinel nodes eliminate edge-case null checks during insertion and deletion.
 * 
 * Asked in: Amazon, Google, Microsoft, Oracle
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
        static const DLLNode head;
        static const DLLNode tail;
        static int size;

        DoublyLinkedList() {
            head = new DLLNode(0); // Dummy head
            tail = new DLLNode(0); // Dummy tail
            head.next = tail;
            tail.prev = head;
            size = 0;
        }

        void addFirst(int val) {
            DLLNode node = new DLLNode(val);
            node.next = head.next;
            node.prev = head;
            head.next.prev = node;
            head.next = node;
            size++;
        }

        void addLast(int val) {
            DLLNode node = new DLLNode(val);
            node.next = tail;
            node.prev = tail.prev;
            tail.prev.next = node;
            tail.prev = node;
            size++;
        }

        int removeFirst() {
            if (isEmpty()) fprintf(stderr, "Exception: invalid argument
"); return 0;
            DLLNode first = head.next;
            head.next = first.next;
            first.next.prev = head;
            size--;
            return first.val;
        }

        int removeLast() {
            if (isEmpty()) fprintf(stderr, "Exception: invalid argument
"); return 0;
            DLLNode last = tail.prev;
            tail.prev = last.prev;
            last.prev.next = tail;
            size--;
            return last.val;
        }

        bool isEmpty() { return size == 0; }
        int size() { return size; }

        void printForward() {
            DLLNode curr = head.next;
            printf("%s", "Forward:  ");
            while (curr != tail) {
                printf("%s", curr.val + (curr.next != tail ? " <-> " : ""));
                curr = curr.next;
            }
            printf("\n");
        }

        void printBackward() {
            DLLNode curr = tail.prev;
            printf("%s", "Backward: ");
            while (curr != head) {
                printf("%s", curr.val + (curr.prev != head ? " <-> " : ""));
                curr = curr.prev;
            }
            printf("\n");
        }
    }

    int main(void) {
        DoublyLinkedList dll = new DoublyLinkedList();

        printf("--- Doubly Linked List Operations ---\n");
        dll.addFirst(20);
        dll.addFirst(10);
        dll.addLast(30);
        dll.addLast(40);

        dll.printForward();
        dll.printBackward();

        printf("Removed First: %d\n", dll.removeFirst());
        printf("Removed Last:  %d\n", dll.removeLast());

        dll.printForward();
        return 0;
}

/*
 * Time Complexity: O(1) for addFirst, addLast, removeFirst, removeLast.
 * Space Complexity: O(N) storage for doubly linked nodes.
 */
