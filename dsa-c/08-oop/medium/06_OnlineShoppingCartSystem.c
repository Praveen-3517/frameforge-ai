/*
 * Problem Statement:
 * Design an E-Commerce Shopping Cart System employing the Strategy Design Pattern:
 * - Product: id, name, price.
 * - CartItem: product, quantity.
 * - DiscountStrategy interface: applyDiscount(total)
 *   - PercentageDiscountStrategy (e.g. 15% off)
 *   - FlatDiscountStrategy (e.g. $20 off orders over $100)
 *   - NoDiscountStrategy
 * - ShoppingCart: add, remove, updateQuantity, calculateTotal, checkout.
 * 
 * Asked in: Amazon, Flipkart, Walmart, eBay
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

static class Product {
        static const const char* id;
        static const const char* name;
        static const double price;

        Product(const char* id, const char* name, double price) {
            this.id = id;
            this.name = name;
            this.price = price;
        }

        const char* getId() { return id; }
        const char* getName() { return name; }
        double getPrice() { return price; }
    }

    static class CartItem {
        static const Product product;
        static int quantity;

        CartItem(Product product, int quantity) {
            this.product = product;
            this.quantity = quantity;
        }

        Product getProduct() { return product; }
        int getQuantity() { return quantity; }
        void setQuantity(int quantity) { this.quantity = quantity; }
        double getSubtotal() { return product.getPrice() * quantity; }
    }

    interface DiscountStrategy {
        double applyDiscount(double originalTotal);
    }

    static class NoDiscountStrategy implements DiscountStrategy {
        double applyDiscount(double total) { return total; }
    }

    static class PercentageDiscountStrategy implements DiscountStrategy {
        static const double percentage; // e.g., 0.15 for 15%
        PercentageDiscountStrategy(double percentage) { this.percentage = percentage; }
        double applyDiscount(double total) { return total * (1.0 - percentage); }
    }

    static class FlatDiscountStrategy implements DiscountStrategy {
        static const double threshold;
        static const double discountAmount;

        FlatDiscountStrategy(double threshold, double discountAmount) {
            this.threshold = threshold;
            this.discountAmount = discountAmount;
        }

        double applyDiscount(double total) {
            return total >= threshold ? MAX(0.0, total - discountAmount) : total;
        }
    }

    static class ShoppingCart {
        static const int* items = new ArrayList<>();
        static DiscountStrategy discountStrategy = new NoDiscountStrategy();

        void addItem(Product product, int quantity) {
            for (CartItem item : items) {
                if (item.getProduct().getId().equals(product.getId())) {
                    item.setQuantity(item.getQuantity() + quantity);
                    return;
                }
            }
            items.add(new CartItem(product, quantity));
        }

        void setDiscountStrategy(DiscountStrategy strategy) {
            this.discountStrategy = strategy;
        }

        double calculateSubtotal() {
            double subtotal = 0;
            for (CartItem item : items) subtotal += item.getSubtotal();
            return subtotal;
        }

        double calculateFinalTotal() {
            return discountStrategy.applyDiscount(calculateSubtotal());
        }

        void printReceipt() {
            printf("========== ORDER SUMMARY ==========\n");
            for (CartItem item : items) {
                printf("%-15s x %d @ $%.2f = $%.2f\n",
                        item.getProduct().getName(), item.getQuantity(),
                        item.getProduct().getPrice(), item.getSubtotal());
            }
            printf("-----------------------------------\n");
            printf("Subtotal:   $%.2f\n", calculateSubtotal());
            printf("Final Total: $%.2f\n", calculateFinalTotal());
        }
    }

    int main(void) {
        Product laptop = new Product("P101", "MacBook Air", 999.0);
        Product mouse = new Product("P102", "Magic Mouse", 79.0);
        Product usbCable = new Product("P103", "USB-C Cable", 19.0);

        ShoppingCart cart = new ShoppingCart();
        cart.addItem(laptop, 1);
        cart.addItem(mouse, 2);
        cart.addItem(usbCable, 3);

        printf("--- Cart without Discount ---\n");
        cart.printReceipt();

        printf("\n--- Cart with 10% Festive Discount ---\n");
        cart.setDiscountStrategy(new PercentageDiscountStrategy(0.10));
        cart.printReceipt();

        printf("\n--- Cart with Flat $100 Discount on orders above $500 ---\n");
        cart.setDiscountStrategy(new FlatDiscountStrategy(500.0, 100.0));
        cart.printReceipt();
        return 0;
}

/*
 * Time Complexity: O(M) where M is items in cart for totals computation.
 * Space Complexity: O(M) to store line items.
 */
