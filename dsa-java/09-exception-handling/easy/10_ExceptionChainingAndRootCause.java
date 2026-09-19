/*
 * Problem Statement:
 * Implement Exception Chaining (wrapping low-level exceptions in high-level domain exceptions):
 * - Wrap a low-level SQLException/IOException inside a high-level ServiceException.
 * - Retain the original root cause using the `cause` constructor argument and `getCause()`.
 * - Print full causal chain to trace where the error originated.
 * 
 * Asked in: Goldman Sachs, Amazon, Morgan Stanley, Netflix
 */

class ExceptionChainingAndRootCause {

    // High-level service exception
    static class OrderProcessingException extends Exception {
        public OrderProcessingException(String message, Throwable cause) {
            super(message, cause);
        }
    }

    // Mid-level payment gateway exception
    static class PaymentGatewayException extends Exception {
        public PaymentGatewayException(String message, Throwable cause) {
            super(message, cause);
        }
    }

    // Low-level network exception
    static class NetworkTimeoutException extends Exception {
        public NetworkTimeoutException(String message) {
            super(message);
        }
    }

    // Low-level network call
    public static void connectToStripe() throws NetworkTimeoutException {
        throw new NetworkTimeoutException("Connection to stripe.api.com:443 timed out after 5000ms");
    }

    // Mid-level payment handler
    public static void chargeCard(double amount) throws PaymentGatewayException {
        try {
            connectToStripe();
        } catch (NetworkTimeoutException e) {
            throw new PaymentGatewayException("Failed to charge credit card for amount $" + amount, e);
        }
    }

    // High-level order service
    public static void processOrder(String orderId, double amount) throws OrderProcessingException {
        try {
            chargeCard(amount);
        } catch (PaymentGatewayException e) {
            throw new OrderProcessingException("Could not fulfill order #" + orderId, e);
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Exception Chaining & Root Cause Analysis ---");
        try {
            processOrder("ORD-7741", 149.99);
        } catch (OrderProcessingException e) {
            System.err.println("Top-level Exception: " + e.getMessage());

            // Trace causal chain
            Throwable current = e.getCause();
            int level = 1;
            while (current != null) {
                System.err.printf("  Caused by (Level %d - %s): %s%n",
                        level++, current.getClass().getSimpleName(), current.getMessage());
                current = current.getCause();
            }
        }
    }
}

/*
 * Time Complexity: O(D) where D is depth of causal exception chain.
 * Space Complexity: O(D) references linking causal exception chain.
 */
