/*
 * Problem Statement:
 * Implement the State Design Pattern for an automated Vending Machine:
 * - States:
 *   1. NoCoinState: Waiting for user to insert coin.
 *   2. HasCoinState: Coin received, user can press dispense or eject coin.
 *   3. SoldState: Dispensing product.
 *   4. SoldOutState: Machine empty.
 * - Eliminate massive if-else/switch statements by encapsulating state-dependent
 *   transitions and behaviors in State classes.
 * 
 * Asked in: Amazon, Oracle, Sony, Bloomberg
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

interface State {
        void insertCoin();
        void ejectCoin();
        void selectProduct();
        void dispense();
    }

    static class VendingMachineContext {
        const State noCoinState;
        const State hasCoinState;
        const State soldState;
        const State soldOutState;

        static State currentState;
        static int count;

        VendingMachineContext(int count) {
            noCoinState = new NoCoinState(this);
            hasCoinState = new HasCoinState(this);
            soldState = new SoldState(this);
            soldOutState = new SoldOutState(this);

            this.count = count;
            this.currentState = count > 0 ? noCoinState : soldOutState;
        }

        void setState(State state) { this.currentState = state; }
        State getState() { return currentState; }
        int getCount() { return count; }
        void releaseProduct() {
            if (count > 0) {
                count--;
                printf("A soda rolled down into the dispenser slot.\n");
            }
        }

        void insertCoin() { currentState.insertCoin(); }
        void ejectCoin() { currentState.ejectCoin(); }
        void selectProduct() { currentState.selectProduct(); currentState.dispense(); }
    }

    static class NoCoinState implements State {
        static const VendingMachineContext machine;
        NoCoinState(VendingMachineContext m) { this.machine = m; }

        void insertCoin() {
            printf("Coin inserted successfully.\n");
            machine.setState(machine.hasCoinState);
        }
        void ejectCoin() { printf("You haven't inserted a coin.\n"); }
        void selectProduct() { printf("Please insert a coin first.\n"); }
        void dispense() { printf("You need to pay first.\n"); }
    }

    static class HasCoinState implements State {
        static const VendingMachineContext machine;
        HasCoinState(VendingMachineContext m) { this.machine = m; }

        void insertCoin() { printf("Coin already inserted.\n"); }
        void ejectCoin() {
            printf("Coin returned.\n");
            machine.setState(machine.noCoinState);
        }
        void selectProduct() {
            printf("Product selection confirmed.\n");
            machine.setState(machine.soldState);
        }
        void dispense() { printf("No product dispensed yet.\n"); }
    }

    static class SoldState implements State {
        static const VendingMachineContext machine;
        SoldState(VendingMachineContext m) { this.machine = m; }

        void insertCoin() { printf("Please wait, already dispensing.\n"); }
        void ejectCoin() { printf("Sorry, you already selected a product.\n"); }
        void selectProduct() { printf("Dispense in progress.\n"); }
        void dispense() {
            machine.releaseProduct();
            if (machine.getCount() > 0) {
                machine.setState(machine.noCoinState);
            } else {
                printf("Oops, out of drinks!\n");
                machine.setState(machine.soldOutState);
            }
        }
    }

    static class SoldOutState implements State {
        static const VendingMachineContext machine;
        SoldOutState(VendingMachineContext m) { this.machine = m; }

        void insertCoin() { printf("Machine is sold out. Coin rejected.\n"); }
        void ejectCoin() { printf("You haven't inserted a coin.\n"); }
        void selectProduct() { printf("Sold out! No items available.\n"); }
        void dispense() { printf("No item to dispense.\n"); }
    }

    int main(void) {
        VendingMachineContext machine = new VendingMachineContext(2);

        printf("--- Vending Machine State Pattern Demo ---\n");
        // Transaction 1
        machine.insertCoin();
        machine.selectProduct();

        // Transaction 2
        machine.insertCoin();
        machine.ejectCoin(); // change of mind
        machine.insertCoin();
        machine.selectProduct(); // Dispenses last soda

        // Transaction 3 (Sold out)
        machine.insertCoin();
        return 0;
}

/*
 * Time Complexity: O(1) for all state transitions and user actions.
 * Space Complexity: O(1) fixed set of state objects.
 */
