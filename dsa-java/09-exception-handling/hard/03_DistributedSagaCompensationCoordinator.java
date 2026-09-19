/*
 * Problem Statement:
 * Implement a Distributed Saga Orchestrator with Compensating Transactions:
 * - Distributed microservices cannot use 2-Phase Commit (2PC) easily.
 * - Sagas execute a sequence of local transactions: T1, T2, ..., Tn.
 * - If Ti fails with an exception, the orchestrator triggers compensating transactions
 *   Ci-1, ..., C1 in reverse order to restore eventual consistency.
 * 
 * Asked in: Uber, Amazon, Airbnb, Stripe
 */

import java.util.ArrayList;
import java.util.List;

class DistributedSagaCompensationCoordinator {

    interface SagaStep {
        String getName();
        void execute() throws Exception;
        void compensate();
    }

    static class SagaOrchestrator {
        private final List<SagaStep> steps = new ArrayList<>();
        private final List<SagaStep> executedSteps = new ArrayList<>();

        public void addStep(SagaStep step) {
            steps.add(step);
        }

        public boolean runSaga() {
            System.out.println(">>> Starting Saga Execution Pipeline <<<");

            for (SagaStep step : steps) {
                try {
                    System.out.println("Executing: " + step.getName());
                    step.execute();
                    executedSteps.add(step);
                } catch (Exception ex) {
                    System.err.printf("[Saga Failure] Step '%s' threw: %s%n", step.getName(), ex.getMessage());
                    triggerCompensation();
                    return false;
                }
            }

            System.out.println(">>> Saga completed successfully! <<<");
            return true;
        }

        private void triggerCompensation() {
            System.err.println("\n[Saga Rollback] Triggering compensating transactions in reverse order:");
            for (int i = executedSteps.size() - 1; i >= 0; i--) {
                SagaStep step = executedSteps.get(i);
                try {
                    System.err.println("  Compensating: " + step.getName());
                    step.compensate();
                } catch (Exception compEx) {
                    System.err.println("  CRITICAL: Compensation failed for " + step.getName() + ": " + compEx.getMessage());
                }
            }
        }
    }

    public static void main(String[] args) {
        SagaOrchestrator saga = new SagaOrchestrator();

        saga.addStep(new SagaStep() {
            public String getName() { return "OrderService: Create Pending Order"; }
            public void execute() { System.out.println("  -> Order ORD-100 created with status PENDING"); }
            public void compensate() { System.out.println("  <- Order ORD-100 status set to CANCELLED"); }
        });

        saga.addStep(new SagaStep() {
            public String getName() { return "PaymentService: Reserve Customer Funds"; }
            public void execute() { System.out.println("  -> Reserved $150 from Customer Wallet"); }
            public void compensate() { System.out.println("  <- Refunded $150 back to Customer Wallet"); }
        });

        saga.addStep(new SagaStep() {
            public String getName() { return "InventoryService: Reserve Stock"; }
            public void execute() throws Exception {
                // Simulating out-of-stock failure
                throw new IllegalStateException("Item 'Wireless Mouse' out of stock!");
            }
            public void compensate() { System.out.println("  <- Released stock lock"); }
        });

        saga.runSaga();
    }
}

/*
 * Time Complexity: O(K) where K is number of steps in the distributed saga.
 * Space Complexity: O(K) memory to hold executed steps history for compensation.
 */
