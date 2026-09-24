/*
 * Problem Statement:
 * Implement Exception Chaining (wrapping low-level exceptions in high-level domain exceptions):
 * - Wrap a low-level SQLException/IOException inside a high-level ServiceException.
 * - Retain the original root cause using the `cause` constructor argument and `getCause()`.
 * - Print full causal chain to trace where the error originated.
 * 
 * Asked in: Goldman Sachs, Amazon, Morgan Stanley, Netflix
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

// High-level service exception
    static class OrderProcessingException extends Exception {
        OrderProcessingException(const char* message, Throwable cause) {
            super(message, cause);
        }
    }

    // Mid-level payment gateway exception
    static class PaymentGatewayException extends Exception {
        PaymentGatewayException(const char* message, Throwable cause) {
            super(message, cause);
        }
    }

    // Low-level network exception
    static class NetworkTimeoutException extends Exception {
        NetworkTimeoutException(const char* message) {
            super(message);
        }
    }

    // Low-level network call
    void connectToStripe() throws NetworkTimeoutException {
        fprintf(stderr, "Exception: invalid argument
"); return 0;
    }

    // Mid-level payment handler
    void chargeCard(double amount) throws PaymentGatewayException {
        try {
            connectToStripe();
        } catch (NetworkTimeoutException e) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }
    }

    // High-level order service
    void processOrder(const char* orderId, double amount) throws OrderProcessingException {
        try {
            chargeCard(amount);
        } catch (PaymentGatewayException e) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }
    }

    int main(void) {
        printf("--- Exception Chaining & Root Cause Analysis ---\n");
        try {
            processOrder("ORD-7741", 149.99);
        } catch (OrderProcessingException e) {
            System.err.println("Top-level Exception: " + e.getMessage());

            // Trace causal chain
            Throwable current = e.getCause();
            int level = 1;
            while (current != NULL) {
                System.err.printf("  Caused by (Level %d - %s): %s%n",
                        level++, current.getClass().getSimpleName(), current.getMessage());
                current = current.getCause();
            }
        }
        return 0;
}

/*
 * Time Complexity: O(D) where D is depth of causal exception chain.
 * Space Complexity: O(D) references linking causal exception chain.
 */
