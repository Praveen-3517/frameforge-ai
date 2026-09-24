/*
 * Problem Statement:
 * Demonstrate Runtime Polymorphism (Dynamic Method Dispatch) and the `super` keyword:
 * - Base class Shape with method `draw()` and `area()`.
 * - Subclasses Circle, Rectangle, and Triangle overriding these methods.
 * - Calling methods polymorphically through a Base class array/reference.
 * 
 * Asked in: Amazon, Microsoft, IBM, Cisco
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

static class Shape {
        const char* color;

        Shape(const char* color) {
            this.color = color;
        }

        void draw() {
            printf("Drawing generic shape in color %d\n", color);
        }

        double area() {
            return 0.0;
        }
    }

    static class Circle extends Shape {
        static double radius;

        Circle(const char* color, double radius) {
            super(color);
            this.radius = radius;
        }

        void draw() {
            super.draw(); // Invoking parent implementation
            printf(" -> Specialized Circle of radius %.2f\n", radius);
        }

        double area() {
            return Math.PI * radius * radius;
        }
    }

    static class Rectangle extends Shape {
        static double width;
        static double height;

        Rectangle(const char* color, double width, double height) {
            super(color);
            this.width = width;
            this.height = height;
        }

        void draw() {
            printf("Drawing %s Rectangle [%.1f x %.1f]\n", color, width, height);
        }

        double area() {
            return width * height;
        }
    }

    int main(void) {
        // Upcasting: Base reference holding derived objects
        Shape[] shapes = {
            new Circle("Red", 5.0),
            new Rectangle("Blue", 4.0, 6.0),
            new Circle("Green", 2.5)
        };

        printf("--- Dynamic Method Dispatch Demo ---\n");
        double totalArea = 0.0;
        for (Shape s : shapes) {
            s.draw(); // Resolved dynamically at runtime
            double a = s.area();
            printf("Area: %.2f\n\n", a);
            totalArea += a;
        }
        printf("Total Area of all shapes: %.2f\n", totalArea);
        return 0;
}

/*
 * Time Complexity: O(1) dynamic method dispatch resolution via virtual method table (vtable).
 * Space Complexity: O(N) to store references to N shapes.
 */
