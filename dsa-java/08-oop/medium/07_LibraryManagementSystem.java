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

import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class LibraryManagementSystem {

    static class Book {
        private final String isbn;
        private final String title;
        private final String author;
        private boolean isAvailable = true;

        public Book(String isbn, String title, String author) {
            this.isbn = isbn;
            this.title = title;
            this.author = author;
        }

        public String getIsbn() { return isbn; }
        public String getTitle() { return title; }
        public String getAuthor() { return author; }
        public boolean isAvailable() { return isAvailable; }
        public void setAvailable(boolean available) { isAvailable = available; }
    }

    static class Member {
        private final String memberId;
        private final String name;
        private final List<LoanRecord> activeLoans = new ArrayList<>();

        public Member(String memberId, String name) {
            this.memberId = memberId;
            this.name = name;
        }

        public String getMemberId() { return memberId; }
        public String getName() { return name; }
        public List<LoanRecord> getActiveLoans() { return activeLoans; }
    }

    static class LoanRecord {
        private final Book book;
        private final Member member;
        private final LocalDate issueDate;
        private final LocalDate dueDate;
        private LocalDate returnDate;

        public LoanRecord(Book book, Member member, LocalDate issueDate) {
            this.book = book;
            this.member = member;
            this.issueDate = issueDate;
            this.dueDate = issueDate.plusDays(14);
        }

        public Book getBook() { return book; }
        public Member getMember() { return member; }
        public LocalDate getDueDate() { return dueDate; }
        public void setReturnDate(LocalDate returnDate) { this.returnDate = returnDate; }

        public double calculateFine() {
            if (returnDate == null || !returnDate.isAfter(dueDate)) return 0.0;
            long daysOverdue = ChronoUnit.DAYS.between(dueDate, returnDate);
            return daysOverdue * 1.50; // $1.50 per day overdue
        }
    }

    static class Library {
        private final Map<String, Book> inventory = new HashMap<>();

        public void addBook(Book book) {
            inventory.put(book.getIsbn(), book);
        }

        public LoanRecord issueBook(String isbn, Member member, LocalDate today) {
            Book book = inventory.get(isbn);
            if (book == null) {
                System.out.println("Book not in library collection.");
                return null;
            }
            if (!book.isAvailable()) {
                System.out.println("Book '" + book.getTitle() + "' is already checked out.");
                return null;
            }
            if (member.getActiveLoans().size() >= 3) {
                System.out.println("Member " + member.getName() + " has reached the 3-book checkout limit.");
                return null;
            }

            book.setAvailable(false);
            LoanRecord loan = new LoanRecord(book, member, today);
            member.getActiveLoans().add(loan);
            System.out.printf("Issued '%s' to %s. Due on %s%n",
                    book.getTitle(), member.getName(), loan.getDueDate());
            return loan;
        }

        public void returnBook(LoanRecord loan, LocalDate returnDate) {
            loan.setReturnDate(returnDate);
            loan.getBook().setAvailable(true);
            loan.getMember().getActiveLoans().remove(loan);

            double fine = loan.calculateFine();
            System.out.printf("Returned '%s'. Overdue fine: $%.2f%n",
                    loan.getBook().getTitle(), fine);
        }
    }

    public static void main(String[] args) {
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
    }
}

/*
 * Time Complexity: O(1) for book checkout, lookup, and return operations.
 * Space Complexity: O(B + M) where B is book count and M is member count.
 */
