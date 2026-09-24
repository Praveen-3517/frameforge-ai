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

static class Student {
        // Instance variables (unique to each instance)
        static const int id;
        static const char* name;

        // Static variable (shared across all Student objects)
        static int studentCount = 0;
        static const const char* UNIVERSITY_NAME;

        // Static initialization block
        static {
            UNIVERSITY_NAME = "National Institute of Technology";
            printf("[Static Init Block] University name configured to: %d\n", UNIVERSITY_NAME);
        }

        // Instance initialization block
        {
            studentCount++;
            printf("[Instance Block] New student being registered. Count: %d\n", studentCount);
        }

        Student(const char* name) {
            this.id = studentCount;
            this.name = name;
        }

        // Static utility method
        int getTotalStudents() {
            // Note: Cannot access 'this' or instance fields (id, name) here
            return studentCount;
        }

        const char* getUniversity() {
            return UNIVERSITY_NAME;
        }

        void printCard() {
            printf("Student #%03d: %-15s | %s\n", id, name, UNIVERSITY_NAME);
        }
    }

    int main(void) {
        printf("University from static method before any object: %d\n", Student.getUniversity());
        printf("Current student count: %d\n", Student.getTotalStudents());

        printf("\nCreating students:\n");
        Student s1 = new Student("Aarav Sharma");
        Student s2 = new Student("Bhavna Patel");
        Student s3 = new Student("Chetan Kumar");

        printf("\nStudent ID Cards:\n");
        s1.printCard();
        s2.printCard();
        s3.printCard();

        printf("\nFinal total students count: %d\n", Student.getTotalStudents());
        return 0;
}

/*
 * Time Complexity: O(1) for static block execution and method calls.
 * Space Complexity: O(1) class metadata space in Metaspace.
 */
