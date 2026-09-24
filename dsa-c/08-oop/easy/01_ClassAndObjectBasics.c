/*
 * Problem Statement:
 * Design a Car class that demonstrates foundational OOP concepts:
 * - State (attributes): make, model, year, speed
 * - Behaviors (methods): accelerate, brake, displayStatus
 * - Instantiation of multiple objects with independent states.
 * 
 * Asked in: Infosys, Wipro, TCS, Cognizant
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

static class Car {
        // Attributes (Instance Variables)
        static const char* make;
        static const char* model;
        static int year;
        static double speed;

        // Constructor
        Car(const char* make, const char* model, int year) {
            this.make = make;
            this.model = model;
            this.year = year;
            this.speed = 0.0;
        }

        // Behaviors
        void accelerate(double increment) {
            if (increment > 0) {
                this.speed += increment;
            }
        }

        void brake(double decrement) {
            if (decrement > 0) {
                this.speed = MAX(0.0, this.speed - decrement);
            }
        }

        void displayStatus() {
            printf("[%d %s %s] Current speed: %.1f km/h\n", year, make, model, speed);
        }

        double getSpeed() {
            return speed;
        }
    }

    int main(void) {
        // Object Instantiation
        Car car1 = new Car("Toyota", "Corolla", 2022);
        Car car2 = new Car("Tesla", "Model 3", 2024);

        printf("--- Initial State ---\n");
        car1.displayStatus();
        car2.displayStatus();

        printf("\n--- Performing Actions ---\n");
        car1.accelerate(50);
        car2.accelerate(85);
        car1.displayStatus();
        car2.displayStatus();

        car1.brake(20);
        car2.brake(100);
        printf("\n--- After Braking ---\n");
        car1.displayStatus();
        car2.displayStatus();
        return 0;
}

/*
 * Time Complexity: O(1) for all car state transitions and queries.
 * Space Complexity: O(1) per instantiated car object on heap.
 */
