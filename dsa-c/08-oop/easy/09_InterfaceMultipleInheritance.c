/*
 * Problem Statement:
 * Demonstrate multiple interface implementation and Java 8+ interface features:
 * - Define interfaces Flyable and Swimmable.
 * - Show how a class Duck can implement both (Multiple Inheritance of Type).
 * - Demonstrate `default` methods, `static` methods, and resolving default method collisions.
 * 
 * Asked in: Amazon, Oracle, Walmart, Mindtree
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

interface Flyable {
        void fly();

        // Java 8 default method
        default void logActivity() {
            printf("Log: Operating in Aerial mode.\n");
        }

        // Java 8 static utility method
        static double knotsToKmh(double knots) {
            return knots * 1.852;
        }
    }

    interface Swimmable {
        void swim();

        // Java 8 default method with colliding name
        default void logActivity() {
            printf("Log: Operating in Aquatic mode.\n");
        }
    }

    // Implementing multiple interfaces
    static class Duck implements Flyable, Swimmable {
        static const char* name;

        Duck(const char* name) {
            this.name = name;
        }

        void fly() {
            printf("%d takes flight across the lake.\n", name);
        }

        void swim() {
            printf("%d paddles gracefully through the water.\n", name);
        }

        // Disambiguate colliding default methods from both interfaces
        void logActivity() {
            printf("%d unified status log:\n", name);
            Flyable.super.logActivity();
            Swimmable.super.logActivity();
        }
    }

    int main(void) {
        Duck mallard = new Duck("Mallard");

        printf("--- Multiple Interfaces & Default Methods ---\n");
        mallard.fly();
        mallard.swim();
        mallard.logActivity();

        // Invoking interface static method
        double speedKnots = 25.0;
        printf("\nFlight speed %.1f knots = %.2f km/h (via Flyable static method)\n",
                speedKnots, Flyable.knotsToKmh(speedKnots));
        return 0;
}

/*
 * Time Complexity: O(1) for interface method calls and conflict resolution.
 * Space Complexity: O(1) heap allocation per Duck object.
 */
