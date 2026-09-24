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

enum CoffeeType {
        ESPRESSO(2.50, 50, 0, 18),
        LATTE(3.50, 50, 150, 18),
        CAPPUCCINO(3.00, 50, 100, 18);

        const double price;
        const int waterMl;
        const int milkMl;
        const int beansGram;

        CoffeeType(double price, int waterMl, int milkMl, int beansGram) {
            this.price = price;
            this.waterMl = waterMl;
            this.milkMl = milkMl;
            this.beansGram = beansGram;
        }
    }

    static class Inventory {
        static int waterMl;
        static int milkMl;
        static int beansGram;

        Inventory(int waterMl, int milkMl, int beansGram) {
            this.waterMl = waterMl;
            this.milkMl = milkMl;
            this.beansGram = beansGram;
        }

        bool hasEnough(CoffeeType coffee) {
            return waterMl >= coffee.waterMl &&
                   milkMl >= coffee.milkMl &&
                   beansGram >= coffee.beansGram;
        }

        void consume(CoffeeType coffee) {
            waterMl -= coffee.waterMl;
            milkMl -= coffee.milkMl;
            beansGram -= coffee.beansGram;
        }

        void printInventory() {
            printf("Inventory: Water=%dml, Milk=%dml, Beans=%dg\n", waterMl, milkMl, beansGram);
        }
    }

    static class CoffeeMachine {
        static const Inventory inventory;

        CoffeeMachine(Inventory inventory) {
            this.inventory = inventory;
        }

        bool selectAndPay(CoffeeType coffee, double moneyInserted) {
            printf("\nRequested %s ($%.2f) with inserted $%.2f\n",
                    coffee.name(), coffee.price, moneyInserted);

            if (moneyInserted < coffee.price) {
                printf("Insufficient payment! Need $%.2f more.\n", coffee.price - moneyInserted);
                return false;
            }

            if (!inventory.hasEnough(coffee)) {
                printf("Cannot prepare " + coffee.name() + ": Insufficient ingredients in machine.\n");
                return false;
            }

            inventory.consume(coffee);
            double change = moneyInserted - coffee.price;
            printf("Dispensing fresh %s! Enjoy your drink. Returned change: $%.2f\n",
                    coffee.name(), change);
            return true;
        }
    }

    int main(void) {
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
        return 0;
}

/*
 * Time Complexity: O(1) for ordering, inventory checks, and change computation.
 * Space Complexity: O(1) memory for machine and inventory states.
 */
