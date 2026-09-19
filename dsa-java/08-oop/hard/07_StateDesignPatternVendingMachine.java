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

class StateDesignPatternVendingMachine {

    interface State {
        void insertCoin();
        void ejectCoin();
        void selectProduct();
        void dispense();
    }

    static class VendingMachineContext {
        final State noCoinState;
        final State hasCoinState;
        final State soldState;
        final State soldOutState;

        private State currentState;
        private int count;

        public VendingMachineContext(int count) {
            noCoinState = new NoCoinState(this);
            hasCoinState = new HasCoinState(this);
            soldState = new SoldState(this);
            soldOutState = new SoldOutState(this);

            this.count = count;
            this.currentState = count > 0 ? noCoinState : soldOutState;
        }

        public void setState(State state) { this.currentState = state; }
        public State getState() { return currentState; }
        public int getCount() { return count; }
        public void releaseProduct() {
            if (count > 0) {
                count--;
                System.out.println("A soda rolled down into the dispenser slot.");
            }
        }

        public void insertCoin() { currentState.insertCoin(); }
        public void ejectCoin() { currentState.ejectCoin(); }
        public void selectProduct() { currentState.selectProduct(); currentState.dispense(); }
    }

    static class NoCoinState implements State {
        private final VendingMachineContext machine;
        public NoCoinState(VendingMachineContext m) { this.machine = m; }

        public void insertCoin() {
            System.out.println("Coin inserted successfully.");
            machine.setState(machine.hasCoinState);
        }
        public void ejectCoin() { System.out.println("You haven't inserted a coin."); }
        public void selectProduct() { System.out.println("Please insert a coin first."); }
        public void dispense() { System.out.println("You need to pay first."); }
    }

    static class HasCoinState implements State {
        private final VendingMachineContext machine;
        public HasCoinState(VendingMachineContext m) { this.machine = m; }

        public void insertCoin() { System.out.println("Coin already inserted."); }
        public void ejectCoin() {
            System.out.println("Coin returned.");
            machine.setState(machine.noCoinState);
        }
        public void selectProduct() {
            System.out.println("Product selection confirmed.");
            machine.setState(machine.soldState);
        }
        public void dispense() { System.out.println("No product dispensed yet."); }
    }

    static class SoldState implements State {
        private final VendingMachineContext machine;
        public SoldState(VendingMachineContext m) { this.machine = m; }

        public void insertCoin() { System.out.println("Please wait, already dispensing."); }
        public void ejectCoin() { System.out.println("Sorry, you already selected a product."); }
        public void selectProduct() { System.out.println("Dispense in progress."); }
        public void dispense() {
            machine.releaseProduct();
            if (machine.getCount() > 0) {
                machine.setState(machine.noCoinState);
            } else {
                System.out.println("Oops, out of drinks!");
                machine.setState(machine.soldOutState);
            }
        }
    }

    static class SoldOutState implements State {
        private final VendingMachineContext machine;
        public SoldOutState(VendingMachineContext m) { this.machine = m; }

        public void insertCoin() { System.out.println("Machine is sold out. Coin rejected."); }
        public void ejectCoin() { System.out.println("You haven't inserted a coin."); }
        public void selectProduct() { System.out.println("Sold out! No items available."); }
        public void dispense() { System.out.println("No item to dispense."); }
    }

    public static void main(String[] args) {
        VendingMachineContext machine = new VendingMachineContext(2);

        System.out.println("--- Vending Machine State Pattern Demo ---");
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
    }
}

/*
 * Time Complexity: O(1) for all state transitions and user actions.
 * Space Complexity: O(1) fixed set of state objects.
 */
