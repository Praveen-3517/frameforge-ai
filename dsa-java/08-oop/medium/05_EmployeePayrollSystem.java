/*
 * Problem Statement:
 * Design an Employee Payroll System that adheres to the Open/Closed Principle:
 * - Abstract base class Employee (id, name).
 * - Concrete subclasses:
 *   1. SalariedEmployee (fixed monthly salary)
 *   2. HourlyEmployee (hourlyRate, hoursWorked, overtime calculation above 40 hrs at 1.5x)
 *   3. CommissionEmployee (baseSalary + salesAmount * commissionRate)
 * - Payroll processor computing total payouts across all diverse worker types.
 * 
 * Asked in: Intuit, ADP, Workday, Salesforce
 */

import java.util.ArrayList;
import java.util.List;

class EmployeePayrollSystem {

    abstract static class Employee {
        private final String id;
        private final String name;

        public Employee(String id, String name) {
            this.id = id;
            this.name = name;
        }

        public String getId() { return id; }
        public String getName() { return name; }

        public abstract double calculatePay();

        public void printPaystub() {
            System.out.printf("[%s] %-15s Gross Pay: $%,8.2f%n", id, name, calculatePay());
        }
    }

    static class SalariedEmployee extends Employee {
        private final double monthlySalary;

        public SalariedEmployee(String id, String name, double monthlySalary) {
            super(id, name);
            this.monthlySalary = monthlySalary;
        }

        @Override
        public double calculatePay() {
            return monthlySalary;
        }
    }

    static class HourlyEmployee extends Employee {
        private final double hourlyRate;
        private final double hoursWorked;

        public HourlyEmployee(String id, String name, double hourlyRate, double hoursWorked) {
            super(id, name);
            this.hourlyRate = hourlyRate;
            this.hoursWorked = hoursWorked;
        }

        @Override
        public double calculatePay() {
            if (hoursWorked <= 40) {
                return hoursWorked * hourlyRate;
            } else {
                double regularPay = 40 * hourlyRate;
                double overtimeHours = hoursWorked - 40;
                double overtimePay = overtimeHours * hourlyRate * 1.5;
                return regularPay + overtimePay;
            }
        }
    }

    static class CommissionEmployee extends Employee {
        private final double baseSalary;
        private final double grossSales;
        private final double commissionRate;

        public CommissionEmployee(String id, String name, double baseSalary, double grossSales, double commissionRate) {
            super(id, name);
            this.baseSalary = baseSalary;
            this.grossSales = grossSales;
            this.commissionRate = commissionRate;
        }

        @Override
        public double calculatePay() {
            return baseSalary + (grossSales * commissionRate);
        }
    }

    static class PayrollProcessor {
        public static double processPayroll(List<Employee> staff) {
            double totalPayout = 0;
            System.out.println("================ PAYROLL REPORT ================");
            for (Employee emp : staff) {
                emp.printPaystub();
                totalPayout += emp.calculatePay();
            }
            System.out.println("------------------------------------------------");
            System.out.printf("Total Company Payroll: $%,8.2f%n", totalPayout);
            return totalPayout;
        }
    }

    public static void main(String[] args) {
        List<Employee> staff = new ArrayList<>();
        staff.add(new SalariedEmployee("EMP-001", "Diane Vance", 7500.0));
        staff.add(new HourlyEmployee("EMP-002", "Jack Dawson", 30.0, 45.0)); // 40 reg + 5 OT
        staff.add(new CommissionEmployee("EMP-003", "Rachel Green", 2500.0, 50000.0, 0.08));

        PayrollProcessor.processPayroll(staff);
    }
}

/*
 * Time Complexity: O(N) to process payroll for N employees.
 * Space Complexity: O(N) storage for employee list.
 */
