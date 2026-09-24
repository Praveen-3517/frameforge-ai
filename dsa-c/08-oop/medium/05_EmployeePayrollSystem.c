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

abstract static class Employee {
        static const const char* id;
        static const const char* name;

        Employee(const char* id, const char* name) {
            this.id = id;
            this.name = name;
        }

        const char* getId() { return id; }
        const char* getName() { return name; }

        abstract double calculatePay();

        void printPaystub() {
            printf("[%s] %-15s Gross Pay: $%,8.2f\n", id, name, calculatePay());
        }
    }

    static class SalariedEmployee extends Employee {
        static const double monthlySalary;

        SalariedEmployee(const char* id, const char* name, double monthlySalary) {
            super(id, name);
            this.monthlySalary = monthlySalary;
        }

        double calculatePay() {
            return monthlySalary;
        }
    }

    static class HourlyEmployee extends Employee {
        static const double hourlyRate;
        static const double hoursWorked;

        HourlyEmployee(const char* id, const char* name, double hourlyRate, double hoursWorked) {
            super(id, name);
            this.hourlyRate = hourlyRate;
            this.hoursWorked = hoursWorked;
        }

        double calculatePay() {
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
        static const double baseSalary;
        static const double grossSales;
        static const double commissionRate;

        CommissionEmployee(const char* id, const char* name, double baseSalary, double grossSales, double commissionRate) {
            super(id, name);
            this.baseSalary = baseSalary;
            this.grossSales = grossSales;
            this.commissionRate = commissionRate;
        }

        double calculatePay() {
            return baseSalary + (grossSales * commissionRate);
        }
    }

    static class PayrollProcessor {
        double processPayroll(int* staff) {
            double totalPayout = 0;
            printf("================ PAYROLL REPORT ================\n");
            for (Employee emp : staff) {
                emp.printPaystub();
                totalPayout += emp.calculatePay();
            }
            printf("------------------------------------------------\n");
            printf("Total Company Payroll: $%,8.2f\n", totalPayout);
            return totalPayout;
        }
    }

    int main(void) {
        int* staff = new ArrayList<>();
        staff.add(new SalariedEmployee("EMP-001", "Diane Vance", 7500.0));
        staff.add(new HourlyEmployee("EMP-002", "Jack Dawson", 30.0, 45.0)); // 40 reg + 5 OT
        staff.add(new CommissionEmployee("EMP-003", "Rachel Green", 2500.0, 50000.0, 0.08));

        PayrollProcessor.processPayroll(staff);
        return 0;
}

/*
 * Time Complexity: O(N) to process payroll for N employees.
 * Space Complexity: O(N) storage for employee list.
 */
