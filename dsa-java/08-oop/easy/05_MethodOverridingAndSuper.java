/*
 * Problem Statement:
 * Demonstrate Runtime Polymorphism (Dynamic Method Dispatch) and the `super` keyword:
 * - Base class Shape with method `draw()` and `area()`.
 * - Subclasses Circle, Rectangle, and Triangle overriding these methods.
 * - Calling methods polymorphically through a Base class array/reference.
 * 
 * Asked in: Amazon, Microsoft, IBM, Cisco
 */

class MethodOverridingAndSuper {

    static class Shape {
        protected String color;

        public Shape(String color) {
            this.color = color;
        }

        public void draw() {
            System.out.println("Drawing generic shape in color " + color);
        }

        public double area() {
            return 0.0;
        }
    }

    static class Circle extends Shape {
        private double radius;

        public Circle(String color, double radius) {
            super(color);
            this.radius = radius;
        }

        @Override
        public void draw() {
            super.draw(); // Invoking parent implementation
            System.out.printf(" -> Specialized Circle of radius %.2f%n", radius);
        }

        @Override
        public double area() {
            return Math.PI * radius * radius;
        }
    }

    static class Rectangle extends Shape {
        private double width;
        private double height;

        public Rectangle(String color, double width, double height) {
            super(color);
            this.width = width;
            this.height = height;
        }

        @Override
        public void draw() {
            System.out.printf("Drawing %s Rectangle [%.1f x %.1f]%n", color, width, height);
        }

        @Override
        public double area() {
            return width * height;
        }
    }

    public static void main(String[] args) {
        // Upcasting: Base reference holding derived objects
        Shape[] shapes = {
            new Circle("Red", 5.0),
            new Rectangle("Blue", 4.0, 6.0),
            new Circle("Green", 2.5)
        };

        System.out.println("--- Dynamic Method Dispatch Demo ---");
        double totalArea = 0.0;
        for (Shape s : shapes) {
            s.draw(); // Resolved dynamically at runtime
            double a = s.area();
            System.out.printf("Area: %.2f%n%n", a);
            totalArea += a;
        }
        System.out.printf("Total Area of all shapes: %.2f%n", totalArea);
    }
}

/*
 * Time Complexity: O(1) dynamic method dispatch resolution via virtual method table (vtable).
 * Space Complexity: O(N) to store references to N shapes.
 */
