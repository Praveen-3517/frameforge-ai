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

import java.util.ArrayList;
import java.util.List;

class ShapeHierarchyPolymorphism {

    interface Shape {
        String getName();
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
        private final double radius;
        public Circle(double radius) { this.radius = radius; }
        public String getName() { return "Circle(r=" + radius + ")"; }
        public double getArea() { return Math.PI * radius * radius; }
        public double getPerimeter() { return 2 * Math.PI * radius; }
    }

    static class Rectangle implements TwoDimensionalShape {
        private final double width, height;
        public Rectangle(double width, double height) { this.width = width; this.height = height; }
        public String getName() { return "Rectangle(" + width + "x" + height + ")"; }
        public double getArea() { return width * height; }
        public double getPerimeter() { return 2 * (width + height); }
    }

    static class Sphere implements ThreeDimensionalShape {
        private final double radius;
        public Sphere(double radius) { this.radius = radius; }
        public String getName() { return "Sphere(r=" + radius + ")"; }
        public double getVolume() { return (4.0 / 3.0) * Math.PI * Math.pow(radius, 3); }
        public double getSurfaceArea() { return 4 * Math.PI * radius * radius; }
    }

    static class Cube implements ThreeDimensionalShape {
        private final double side;
        public Cube(double side) { this.side = side; }
        public String getName() { return "Cube(s=" + side + ")"; }
        public double getVolume() { return Math.pow(side, 3); }
        public double getSurfaceArea() { return 6 * side * side; }
    }

    public static void main(String[] args) {
        List<Shape> shapes = new ArrayList<>();
        shapes.add(new Circle(3.0));
        shapes.add(new Rectangle(4.0, 5.0));
        shapes.add(new Sphere(3.0));
        shapes.add(new Cube(4.0));

        System.out.println("--- 2D and 3D Shape Polymorphism ---");
        for (Shape s : shapes) {
            System.out.println("Shape: " + s.getName());
            if (s instanceof TwoDimensionalShape) {
                TwoDimensionalShape d2 = (TwoDimensionalShape) s;
                System.out.printf("  [2D] Area: %.2f | Perimeter: %.2f%n", d2.getArea(), d2.getPerimeter());
            } else if (s instanceof ThreeDimensionalShape) {
                ThreeDimensionalShape d3 = (ThreeDimensionalShape) s;
                System.out.printf("  [3D] Volume: %.2f | Surface Area: %.2f%n", d3.getVolume(), d3.getSurfaceArea());
            }
        }
    }
}

/*
 * Time Complexity: O(1) for all geometric property computations.
 * Space Complexity: O(N) where N is number of shapes.
 */
