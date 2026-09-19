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

import java.util.ArrayList;
import java.util.List;

class OnlineShoppingCartSystem {

    static class Product {
        private final String id;
        private final String name;
        private final double price;

        public Product(String id, String name, double price) {
            this.id = id;
            this.name = name;
            this.price = price;
        }

        public String getId() { return id; }
        public String getName() { return name; }
        public double getPrice() { return price; }
    }

    static class CartItem {
        private final Product product;
        private int quantity;

        public CartItem(Product product, int quantity) {
            this.product = product;
            this.quantity = quantity;
        }

        public Product getProduct() { return product; }
        public int getQuantity() { return quantity; }
        public void setQuantity(int quantity) { this.quantity = quantity; }
        public double getSubtotal() { return product.getPrice() * quantity; }
    }

    interface DiscountStrategy {
        double applyDiscount(double originalTotal);
    }

    static class NoDiscountStrategy implements DiscountStrategy {
        public double applyDiscount(double total) { return total; }
    }

    static class PercentageDiscountStrategy implements DiscountStrategy {
        private final double percentage; // e.g., 0.15 for 15%
        public PercentageDiscountStrategy(double percentage) { this.percentage = percentage; }
        public double applyDiscount(double total) { return total * (1.0 - percentage); }
    }

    static class FlatDiscountStrategy implements DiscountStrategy {
        private final double threshold;
        private final double discountAmount;

        public FlatDiscountStrategy(double threshold, double discountAmount) {
            this.threshold = threshold;
            this.discountAmount = discountAmount;
        }

        public double applyDiscount(double total) {
            return total >= threshold ? Math.max(0.0, total - discountAmount) : total;
        }
    }

    static class ShoppingCart {
        private final List<CartItem> items = new ArrayList<>();
        private DiscountStrategy discountStrategy = new NoDiscountStrategy();

        public void addItem(Product product, int quantity) {
            for (CartItem item : items) {
                if (item.getProduct().getId().equals(product.getId())) {
                    item.setQuantity(item.getQuantity() + quantity);
                    return;
                }
            }
            items.add(new CartItem(product, quantity));
        }

        public void setDiscountStrategy(DiscountStrategy strategy) {
            this.discountStrategy = strategy;
        }

        public double calculateSubtotal() {
            double subtotal = 0;
            for (CartItem item : items) subtotal += item.getSubtotal();
            return subtotal;
        }

        public double calculateFinalTotal() {
            return discountStrategy.applyDiscount(calculateSubtotal());
        }

        public void printReceipt() {
            System.out.println("========== ORDER SUMMARY ==========");
            for (CartItem item : items) {
                System.out.printf("%-15s x %d @ $%.2f = $%.2f%n",
                        item.getProduct().getName(), item.getQuantity(),
                        item.getProduct().getPrice(), item.getSubtotal());
            }
            System.out.println("-----------------------------------");
            System.out.printf("Subtotal:   $%.2f%n", calculateSubtotal());
            System.out.printf("Final Total: $%.2f%n", calculateFinalTotal());
        }
    }

    public static void main(String[] args) {
        Product laptop = new Product("P101", "MacBook Air", 999.0);
        Product mouse = new Product("P102", "Magic Mouse", 79.0);
        Product usbCable = new Product("P103", "USB-C Cable", 19.0);

        ShoppingCart cart = new ShoppingCart();
        cart.addItem(laptop, 1);
        cart.addItem(mouse, 2);
        cart.addItem(usbCable, 3);

        System.out.println("--- Cart without Discount ---");
        cart.printReceipt();

        System.out.println("\n--- Cart with 10% Festive Discount ---");
        cart.setDiscountStrategy(new PercentageDiscountStrategy(0.10));
        cart.printReceipt();

        System.out.println("\n--- Cart with Flat $100 Discount on orders above $500 ---");
        cart.setDiscountStrategy(new FlatDiscountStrategy(500.0, 100.0));
        cart.printReceipt();
    }
}

/*
 * Time Complexity: O(M) where M is items in cart for totals computation.
 * Space Complexity: O(M) to store line items.
 */
