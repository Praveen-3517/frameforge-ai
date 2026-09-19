/*
 * Problem Statement:
 * Design an Object-Oriented Coffee Vending Machine:
 * - Recipe configurations (Espresso, Latte, Cappuccino) with ingredient requirements
 *   (water, milk, coffee beans).
 * - Inventory management with low-stock alerts.
 * - Payment processing with exact change returned.
 * - State machine tracking: READY, DISPENSING, OUT_OF_STOCK.
 * 
 * Asked in: Philips, Samsung, Siemens, Qualcomm
 */

import java.util.HashMap;
import java.util.Map;

class CoffeeVendingMachineOOP {

    enum CoffeeType {
        ESPRESSO(2.50, 50, 0, 18),
        LATTE(3.50, 50, 150, 18),
        CAPPUCCINO(3.00, 50, 100, 18);

        final double price;
        final int waterMl;
        final int milkMl;
        final int beansGram;

        CoffeeType(double price, int waterMl, int milkMl, int beansGram) {
            this.price = price;
            this.waterMl = waterMl;
            this.milkMl = milkMl;
            this.beansGram = beansGram;
        }
    }

    static class Inventory {
        private int waterMl;
        private int milkMl;
        private int beansGram;

        public Inventory(int waterMl, int milkMl, int beansGram) {
            this.waterMl = waterMl;
            this.milkMl = milkMl;
            this.beansGram = beansGram;
        }

        public boolean hasEnough(CoffeeType coffee) {
            return waterMl >= coffee.waterMl &&
                   milkMl >= coffee.milkMl &&
                   beansGram >= coffee.beansGram;
        }

        public void consume(CoffeeType coffee) {
            waterMl -= coffee.waterMl;
            milkMl -= coffee.milkMl;
            beansGram -= coffee.beansGram;
        }

        public void printInventory() {
            System.out.printf("Inventory: Water=%dml, Milk=%dml, Beans=%dg%n", waterMl, milkMl, beansGram);
        }
    }

    static class CoffeeMachine {
        private final Inventory inventory;

        public CoffeeMachine(Inventory inventory) {
            this.inventory = inventory;
        }

        public boolean selectAndPay(CoffeeType coffee, double moneyInserted) {
            System.out.printf("%nRequested %s ($%.2f) with inserted $%.2f%n",
                    coffee.name(), coffee.price, moneyInserted);

            if (moneyInserted < coffee.price) {
                System.out.printf("Insufficient payment! Need $%.2f more.%n", coffee.price - moneyInserted);
                return false;
            }

            if (!inventory.hasEnough(coffee)) {
                System.out.println("Cannot prepare " + coffee.name() + ": Insufficient ingredients in machine.");
                return false;
            }

            inventory.consume(coffee);
            double change = moneyInserted - coffee.price;
            System.out.printf("Dispensing fresh %s! Enjoy your drink. Returned change: $%.2f%n",
                    coffee.name(), change);
            return true;
        }
    }

    public static void main(String[] args) {
        Inventory inv = new Inventory(200, 200, 50);
        CoffeeMachine machine = new CoffeeMachine(inv);

        inv.printInventory();

        // 1. Order Espresso
        machine.selectAndPay(CoffeeType.ESPRESSO, 3.00);
        inv.printInventory();

        // 2. Order Latte (needs 150ml milk; only 200ml left)
        machine.selectAndPay(CoffeeType.LATTE, 5.00);
        inv.printInventory();

        // 3. Try another Latte (milk required 150ml, but only 50ml left)
        machine.selectAndPay(CoffeeType.LATTE, 5.00);
    }
}

/*
 * Time Complexity: O(1) for ordering, inventory checks, and change computation.
 * Space Complexity: O(1) memory for machine and inventory states.
 */
