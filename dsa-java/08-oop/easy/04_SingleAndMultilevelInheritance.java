/*
 * Problem Statement:
 * Implement single and multilevel inheritance hierarchies representing an Organization:
 * - Base class: Person (name, age)
 * - Derived class (Single inheritance): Employee (adds employeeId, baseSalary)
 * - Multi-level derived class: Manager (adds teamSize, department, bonus)
 * Demonstrate constructor calling sequence using `super(...)` and method reuse.
 * 
 * Asked in: Oracle, Infosys, Wipro, Accenture
 */

class SingleAndMultilevelInheritance {

    // Base Class
    static class Person {
        protected String name;
        protected int age;

        public Person(String name, int age) {
            this.name = name;
            this.age = age;
            System.out.println("Person constructor called for " + name);
        }

        public void displayPersonalDetails() {
            System.out.printf("Person: %s, Age: %d%n", name, age);
        }
    }

    // Single Inheritance: Employee extends Person
    static class Employee extends Person {
        protected String employeeId;
        protected double baseSalary;

        public Employee(String name, int age, String employeeId, double baseSalary) {
            super(name, age); // Call parent Person constructor
            this.employeeId = employeeId;
            this.baseSalary = baseSalary;
            System.out.println("Employee constructor called for ID: " + employeeId);
        }

        public double calculateAnnualPay() {
            return baseSalary * 12;
        }

        public void displayEmployeeDetails() {
            displayPersonalDetails();
            System.out.printf("Employee ID: %s, Monthly Salary: $%.2f%n", employeeId, baseSalary);
        }
    }

    // Multilevel Inheritance: Manager extends Employee (which extends Person)
    static class Manager extends Employee {
        private String department;
        private int teamSize;
        private double bonus;

        public Manager(String name, int age, String employeeId, double baseSalary,
                       String department, int teamSize, double bonus) {
            super(name, age, employeeId, baseSalary); // Call Employee constructor
            this.department = department;
            this.teamSize = teamSize;
            this.bonus = bonus;
            System.out.println("Manager constructor called for Dept: " + department);
        }

        @Override
        public double calculateAnnualPay() {
            return (baseSalary * 12) + bonus;
        }

        public void displayManagerSummary() {
            displayEmployeeDetails();
            System.out.printf("Dept: %s | Team Size: %d | Annual Bonus: $%.2f | Total Annual Pay: $%.2f%n",
                    department, teamSize, bonus, calculateAnnualPay());
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Instantiating Manager (Multilevel Chain) ---");
        Manager mgr = new Manager("Alice Chen", 38, "EMP1001", 8500.0, "Engineering", 12, 15000.0);

        System.out.println("\n--- Manager Details ---");
        mgr.displayManagerSummary();
    }
}

/*
 * Time Complexity: O(1) for object construction and field initialization.
 * Space Complexity: O(1) auxiliary space per instantiated instance.
 */
