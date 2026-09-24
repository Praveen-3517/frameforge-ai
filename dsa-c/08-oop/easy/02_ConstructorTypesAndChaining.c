/*
 * Problem Statement:
 * Demonstrate all types of Constructors in Java:
 * 1. Default (no-arg) constructor
 * 2. Parameterized constructor
 * 3. Copy constructor (manual deep/shallow copy)
 * 4. Constructor chaining using `this(...)` within the same class.
 * 
 * Asked in: Amazon, Oracle, HCL, Mindtree
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

static class Book {
        static const char* title;
        static const char* author;
        static double price;
        static int pages;

        // 1. Default Constructor (calls parameterized constructor via chaining)
        Book() {
            this("Untitled", "Unknown Author", 0.0, 0);
            printf("Default Book constructor invoked.\n");
        }

        // Overloaded constructor with 2 arguments
        Book(const char* title, const char* author) {
            this(title, author, 9.99, 100);
        }

        // 2. Full Parameterized Constructor
        Book(const char* title, const char* author, double price, int pages) {
            this.title = title;
            this.author = author;
            this.price = price;
            this.pages = pages;
        }

        // 3. Copy Constructor
        Book(Book other) {
            if (other == NULL) fprintf(stderr, "Exception: invalid argument
"); return 0;
            this.title = other.title;
            this.author = other.author;
            this.price = other.price;
            this.pages = other.pages;
        }

        void printInfo() {
            printf("'%s' by %s | Price: $%.2f | Pages: %d\n", title, author, price, pages);
        }

        void setPrice(double price) {
            this.price = price;
        }
    }

    int main(void) {
        printf("--- Constructor Demonstration ---\n");

        Book b1 = new Book();
        b1.printInfo();

        Book b2 = new Book("Effective Java", "Joshua Bloch");
        b2.printInfo();

        Book b3 = new Book("Clean Code", "Robert C. Martin", 34.50, 464);
        b3.printInfo();

        // Copy constructor
        Book b4 = new Book(b3);
        printf("\n--- Copied Book (b4 copied from b3) ---\n");
        b4.printInfo();

        b4.setPrice(19.99);
        printf("After changing b4 price to 19.99:\n");
        printf("%s", "b3 (original): "); b3.printInfo();
        printf("%s", "b4 (copy):     "); b4.printInfo();
        return 0;
}

/*
 * Time Complexity: O(1) for all constructor invocations.
 * Space Complexity: O(1) auxiliary space per instantiated book.
 */
