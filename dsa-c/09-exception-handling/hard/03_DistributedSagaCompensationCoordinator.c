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

interface SagaStep {
        const char* getName();
        void execute() throws Exception;
        void compensate();
    }

    static class SagaOrchestrator {
        static const int* steps = new ArrayList<>();
        static const int* executedSteps = new ArrayList<>();

        void addStep(SagaStep step) {
            steps.add(step);
        }

        bool runSaga() {
            printf(">>> Starting Saga Execution Pipeline <<<\n");

            for (SagaStep step : steps) {
                try {
                    printf("Executing: %d\n", step.getName());
                    step.execute();
                    executedSteps.add(step);
                } catch (Exception ex) {
                    System.err.printf("[Saga Failure] Step '%s' threw: %s%n", step.getName(), ex.getMessage());
                    triggerCompensation();
                    return false;
                }
            }

            printf(">>> Saga completed successfully! <<<\n");
            return true;
        }

        static void triggerCompensation() {
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

    int main(void) {
        SagaOrchestrator saga = new SagaOrchestrator();

        saga.addStep(new SagaStep() {
            const char* getName() { return "OrderService: Create Pending Order"; }
            void execute() { printf("  -> Order ORD-100 created with status PENDING\n"); }
            void compensate() { printf("  <- Order ORD-100 status set to CANCELLED\n"); }
        });

        saga.addStep(new SagaStep() {
            const char* getName() { return "PaymentService: Reserve Customer Funds"; }
            void execute() { printf("  -> Reserved $150 from Customer Wallet\n"); }
            void compensate() { printf("  <- Refunded $150 back to Customer Wallet\n"); }
        });

        saga.addStep(new SagaStep() {
            const char* getName() { return "InventoryService: Reserve Stock"; }
            void execute() throws Exception {
                // Simulating out-of-stock failure
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            void compensate() { printf("  <- Released stock lock\n"); }
        });

        saga.runSaga();
    }

/*
 * Time Complexity: O(K) where K is number of steps in the distributed saga.
 * Space Complexity: O(K) memory to hold executed steps history for compensation.
 */
