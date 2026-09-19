/*
 * Problem Statement:
 * Demonstrate all dimensions of the `static` keyword in Java:
 * 1. Static variables (class-level shared state, e.g., instance counter).
 * 2. Static methods (utility functions without object instantiation).
 * 3. Static initialization block (runs once when class is loaded).
 * 4. Static nested class vs. inner class.
 * 
 * Asked in: Oracle, Morgan Stanley, Goldman Sachs, TCS
 */

class StaticKeywordDeepDive {

    static class Student {
        // Instance variables (unique to each instance)
        private final int id;
        private String name;

        // Static variable (shared across all Student objects)
        private static int studentCount = 0;
        private static final String UNIVERSITY_NAME;

        // Static initialization block
        static {
            UNIVERSITY_NAME = "National Institute of Technology";
            System.out.println("[Static Init Block] University name configured to: " + UNIVERSITY_NAME);
        }

        // Instance initialization block
        {
            studentCount++;
            System.out.println("[Instance Block] New student being registered. Count: " + studentCount);
        }

        public Student(String name) {
            this.id = studentCount;
            this.name = name;
        }

        // Static utility method
        public static int getTotalStudents() {
            // Note: Cannot access 'this' or instance fields (id, name) here
            return studentCount;
        }

        public static String getUniversity() {
            return UNIVERSITY_NAME;
        }

        public void printCard() {
            System.out.printf("Student #%03d: %-15s | %s%n", id, name, UNIVERSITY_NAME);
        }
    }

    public static void main(String[] args) {
        System.out.println("University from static method before any object: " + Student.getUniversity());
        System.out.println("Current student count: " + Student.getTotalStudents());

        System.out.println("\nCreating students:");
        Student s1 = new Student("Aarav Sharma");
        Student s2 = new Student("Bhavna Patel");
        Student s3 = new Student("Chetan Kumar");

        System.out.println("\nStudent ID Cards:");
        s1.printCard();
        s2.printCard();
        s3.printCard();

        System.out.println("\nFinal total students count: " + Student.getTotalStudents());
    }
}

/*
 * Time Complexity: O(1) for static block execution and method calls.
 * Space Complexity: O(1) class metadata space in Metaspace.
 */
