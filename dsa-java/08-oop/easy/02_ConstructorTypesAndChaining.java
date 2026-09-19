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

class ConstructorTypesAndChaining {

    static class Book {
        private String title;
        private String author;
        private double price;
        private int pages;

        // 1. Default Constructor (calls parameterized constructor via chaining)
        public Book() {
            this("Untitled", "Unknown Author", 0.0, 0);
            System.out.println("Default Book constructor invoked.");
        }

        // Overloaded constructor with 2 arguments
        public Book(String title, String author) {
            this(title, author, 9.99, 100);
        }

        // 2. Full Parameterized Constructor
        public Book(String title, String author, double price, int pages) {
            this.title = title;
            this.author = author;
            this.price = price;
            this.pages = pages;
        }

        // 3. Copy Constructor
        public Book(Book other) {
            if (other == null) throw new IllegalArgumentException("Source book cannot be null");
            this.title = other.title;
            this.author = other.author;
            this.price = other.price;
            this.pages = other.pages;
        }

        public void printInfo() {
            System.out.printf("'%s' by %s | Price: $%.2f | Pages: %d%n", title, author, price, pages);
        }

        public void setPrice(double price) {
            this.price = price;
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Constructor Demonstration ---");

        Book b1 = new Book();
        b1.printInfo();

        Book b2 = new Book("Effective Java", "Joshua Bloch");
        b2.printInfo();

        Book b3 = new Book("Clean Code", "Robert C. Martin", 34.50, 464);
        b3.printInfo();

        // Copy constructor
        Book b4 = new Book(b3);
        System.out.println("\n--- Copied Book (b4 copied from b3) ---");
        b4.printInfo();

        b4.setPrice(19.99);
        System.out.println("After changing b4 price to 19.99:");
        System.out.print("b3 (original): "); b3.printInfo();
        System.out.print("b4 (copy):     "); b4.printInfo();
    }
}

/*
 * Time Complexity: O(1) for all constructor invocations.
 * Space Complexity: O(1) auxiliary space per instantiated book.
 */
