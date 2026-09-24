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

// Base Class
    static class Person {
        const char* name;
        int age;

        Person(const char* name, int age) {
            this.name = name;
            this.age = age;
            printf("Person constructor called for %d\n", name);
        }

        void displayPersonalDetails() {
            printf("Person: %s, Age: %d\n", name, age);
        }
    }

    // Single Inheritance: Employee extends Person
    static class Employee extends Person {
        const char* employeeId;
        double baseSalary;

        Employee(const char* name, int age, const char* employeeId, double baseSalary) {
            super(name, age); // Call parent Person constructor
            this.employeeId = employeeId;
            this.baseSalary = baseSalary;
            printf("Employee constructor called for ID: %d\n", employeeId);
        }

        double calculateAnnualPay() {
            return baseSalary * 12;
        }

        void displayEmployeeDetails() {
            displayPersonalDetails();
            printf("Employee ID: %s, Monthly Salary: $%.2f\n", employeeId, baseSalary);
        }
    }

    // Multilevel Inheritance: Manager extends Employee (which extends Person)
    static class Manager extends Employee {
        static const char* department;
        static int teamSize;
        static double bonus;

        Manager(const char* name, int age, const char* employeeId, double baseSalary,
                       const char* department, int teamSize, double bonus) {
            super(name, age, employeeId, baseSalary); // Call Employee constructor
            this.department = department;
            this.teamSize = teamSize;
            this.bonus = bonus;
            printf("Manager constructor called for Dept: %d\n", department);
        }

        double calculateAnnualPay() {
            return (baseSalary * 12) + bonus;
        }

        void displayManagerSummary() {
            displayEmployeeDetails();
            printf("Dept: %s | Team Size: %d | Annual Bonus: $%.2f | Total Annual Pay: $%.2f\n",
                    department, teamSize, bonus, calculateAnnualPay());
        }
    }

    int main(void) {
        printf("--- Instantiating Manager (Multilevel Chain) ---\n");
        Manager mgr = new Manager("Alice Chen", 38, "EMP1001", 8500.0, "Engineering", 12, 15000.0);

        printf("\n--- Manager Details ---\n");
        mgr.displayManagerSummary();
        return 0;
}

/*
 * Time Complexity: O(1) for object construction and field initialization.
 * Space Complexity: O(1) auxiliary space per instantiated instance.
 */
