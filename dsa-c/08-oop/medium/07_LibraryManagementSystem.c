/*
 * Problem Statement:
 * Design a complete Object-Oriented Library Management System:
 * - Entities: Book, Member, Librarian, LoanRecord.
 * - Capabilities:
 *   - Search books by title or author.
 *   - Issue book (tracks borrowing date, maximum 14 days allowed, max 3 active loans per member).
 *   - Return book (calculates late fee fine if returned after due date).
 * 
 * Asked in: Amazon, Oracle, Cisco, Infosys
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
        static const const char* isbn;
        static const const char* title;
        static const const char* author;
        static bool isAvailable = true;

        Book(const char* isbn, const char* title, const char* author) {
            this.isbn = isbn;
            this.title = title;
            this.author = author;
        }

        const char* getIsbn() { return isbn; }
        const char* getTitle() { return title; }
        const char* getAuthor() { return author; }
        bool isAvailable() { return isAvailable; }
        void setAvailable(bool available) { isAvailable = available; }
    }

    static class Member {
        static const const char* memberId;
        static const const char* name;
        static const int* activeLoans = new ArrayList<>();

        Member(const char* memberId, const char* name) {
            this.memberId = memberId;
            this.name = name;
        }

        const char* getMemberId() { return memberId; }
        const char* getName() { return name; }
        int* getActiveLoans() { return activeLoans; }
    }

    static class LoanRecord {
        static const Book book;
        static const Member member;
        static const LocalDate issueDate;
        static const LocalDate dueDate;
        static LocalDate returnDate;

        LoanRecord(Book book, Member member, LocalDate issueDate) {
            this.book = book;
            this.member = member;
            this.issueDate = issueDate;
            this.dueDate = issueDate.plusDays(14);
        }

        Book getBook() { return book; }
        Member getMember() { return member; }
        LocalDate getDueDate() { return dueDate; }
        void setReturnDate(LocalDate returnDate) { this.returnDate = returnDate; }

        double calculateFine() {
            if (returnDate == NULL || !returnDate.isAfter(dueDate)) return 0.0;
            long long daysOverdue = ChronoUnit.DAYS.between(dueDate, returnDate);
            return daysOverdue * 1.50; // $1.50 per day overdue
        }
    }

    static class Library {
        static const Map<const char*, Book> inventory = new HashMap<>();

        void addBook(Book book) {
            inventory.put(book.getIsbn(), book);
        }

        LoanRecord issueBook(const char* isbn, Member member, LocalDate today) {
            Book book = inventory.get(isbn);
            if (book == NULL) {
                printf("Book not in library collection.\n");
                return NULL;
            }
            if (!book.isAvailable()) {
                printf("Book '" + book.getTitle() + "' is already checked out.\n");
                return NULL;
            }
            if (member.getActiveLoans().size() >= 3) {
                printf("Member " + member.getName() + " has reached the 3-book checkout limit.\n");
                return NULL;
            }

            book.setAvailable(false);
            LoanRecord loan = new LoanRecord(book, member, today);
            member.getActiveLoans().add(loan);
            printf("Issued '%s' to %s. Due on %s\n",
                    book.getTitle(), member.getName(), loan.getDueDate());
            return loan;
        }

        void returnBook(LoanRecord loan, LocalDate returnDate) {
            loan.setReturnDate(returnDate);
            loan.getBook().setAvailable(true);
            loan.getMember().getActiveLoans().remove(loan);

            double fine = loan.calculateFine();
            printf("Returned '%s'. Overdue fine: $%.2f\n",
                    loan.getBook().getTitle(), fine);
        }
    }

    int main(void) {
        Library lib = new Library();
        Book b1 = new Book("978-0134685991", "Effective Java", "Joshua Bloch");
        Book b2 = new Book("978-0132350884", "Clean Code", "Robert Martin");
        lib.addBook(b1);
        lib.addBook(b2);

        Member member = new Member("M101", "Sara Connor");

        LocalDate today = LocalDate.of(2026, 9, 1);
        LoanRecord loan1 = lib.issueBook(b1.getIsbn(), member, today);

        // Attempt duplicate checkout
        lib.issueBook(b1.getIsbn(), member, today);

        // Return book 20 days later (6 days late)
        LocalDate returnDate = today.plusDays(20);
        lib.returnBook(loan1, returnDate);
        return 0;
}

/*
 * Time Complexity: O(1) for book checkout, lookup, and return operations.
 * Space Complexity: O(B + M) where B is book count and M is member count.
 */
