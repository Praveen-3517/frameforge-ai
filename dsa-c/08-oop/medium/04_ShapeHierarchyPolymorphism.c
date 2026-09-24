/*
 * Problem Statement:
 * Build an advanced Geometry hierarchy showcasing Abstraction & Interfaces:
 * - Base interface: Shape
 * - Interface: TwoDimensionalShape (getArea(), getPerimeter())
 * - Interface: ThreeDimensionalShape (getVolume(), getSurfaceArea())
 * - Classes: Circle, Rectangle, Sphere, Cube
 * - Calculate total surface area and volume polymorphically across a collection.
 * 
 * Asked in: Adobe, Autodesk, Microsoft, Siemens
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

interface Shape {
        const char* getName();
    }

    interface TwoDimensionalShape extends Shape {
        double getArea();
        double getPerimeter();
    }

    interface ThreeDimensionalShape extends Shape {
        double getVolume();
        double getSurfaceArea();
    }

    static class Circle implements TwoDimensionalShape {
        static const double radius;
        Circle(double radius) { this.radius = radius; }
        const char* getName() { return "Circle(r=" + radius + ")"; }
        double getArea() { return Math.PI * radius * radius; }
        double getPerimeter() { return 2 * Math.PI * radius; }
    }

    static class Rectangle implements TwoDimensionalShape {
        static const double width, height;
        Rectangle(double width, double height) { this.width = width; this.height = height; }
        const char* getName() { return "Rectangle(" + width + "x" + height + ")"; }
        double getArea() { return width * height; }
        double getPerimeter() { return 2 * (width + height); }
    }

    static class Sphere implements ThreeDimensionalShape {
        static const double radius;
        Sphere(double radius) { this.radius = radius; }
        const char* getName() { return "Sphere(r=" + radius + ")"; }
        double getVolume() { return (4.0 / 3.0) * Math.PI * pow(radius, 3); }
        double getSurfaceArea() { return 4 * Math.PI * radius * radius; }
    }

    static class Cube implements ThreeDimensionalShape {
        static const double side;
        Cube(double side) { this.side = side; }
        const char* getName() { return "Cube(s=" + side + ")"; }
        double getVolume() { return pow(side, 3); }
        double getSurfaceArea() { return 6 * side * side; }
    }

    int main(void) {
        int* shapes = new ArrayList<>();
        shapes.add(new Circle(3.0));
        shapes.add(new Rectangle(4.0, 5.0));
        shapes.add(new Sphere(3.0));
        shapes.add(new Cube(4.0));

        printf("--- 2D and 3D Shape Polymorphism ---\n");
        for (Shape s : shapes) {
            printf("Shape: %d\n", s.getName());
            if (s instanceof TwoDimensionalShape) {
                TwoDimensionalShape d2 = (TwoDimensionalShape) s;
                printf("  [2D] Area: %.2f | Perimeter: %.2f\n", d2.getArea(), d2.getPerimeter());
            } else if (s instanceof ThreeDimensionalShape) {
                ThreeDimensionalShape d3 = (ThreeDimensionalShape) s;
                printf("  [3D] Volume: %.2f | Surface Area: %.2f\n", d3.getVolume(), d3.getSurfaceArea());
            }
        }
        return 0;
}

/*
 * Time Complexity: O(1) for all geometric property computations.
 * Space Complexity: O(N) where N is number of shapes.
 */
