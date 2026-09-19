/**
 * Problem Statement:
 * Implement a bidirectional temperature conversion utility:
 * 1. Celsius to Fahrenheit: F = (C * 9/5) + 32
 * 2. Fahrenheit to Celsius: C = (F - 32) * 5/9
 * Avoid the common beginner integer division bug `9 / 5 == 1`.
 *
 * Asked in: Wipro, Infosys, IBM
 *
 * Approach:
 * - If written as `9 / 5`, integer division truncates to `1`, causing incorrect calculations.
 * - Always use floating-point literals `9.0 / 5.0` or explicit double multiplication first.
 */
class TemperatureConverter {

    public static double celsiusToFahrenheit(double celsius) {
        // Correct: 9.0 / 5.0 ensures double precision
        return (celsius * 9.0 / 5.0) + 32.0;
    }

    public static double fahrenheitToCelsius(double fahrenheit) {
        return (fahrenheit - 32.0) * 5.0 / 9.0;
    }

    public static void main(String[] args) {
        double[] testCelsius = { 0.0, 25.0, 37.0, 100.0, -40.0 };

        System.out.println("=== Celsius to Fahrenheit Conversions ===");
        for (double c : testCelsius) {
            double f = celsiusToFahrenheit(c);
            System.out.printf("%6.1f °C  ==>  %6.1f °F%n", c, f);
        }

        System.out.println("\n=== Fahrenheit to Celsius Conversions ===");
        double[] testFahrenheit = { 32.0, 77.0, 98.6, 212.0, -40.0 };
        for (double f : testFahrenheit) {
            double c = fahrenheitToCelsius(f);
            System.out.printf("%6.1f °F  ==>  %6.1f °C%n", f, c);
        }

        System.out.println("\nNote: At -40.0 degrees, both Celsius and Fahrenheit scales intersect (-40°C == -40°F).");
    }
}

/*
 * Time Complexity: O(1) - Constant floating-point arithmetic.
 * Space Complexity: O(1) - Constant memory.
 */
