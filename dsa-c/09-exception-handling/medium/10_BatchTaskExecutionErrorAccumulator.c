/*
 * Problem Statement:
 * Design a Batch Task Execution Engine that executes N independent tasks:
 * - Tasks can fail due to unpredictable exceptions.
 * - Do NOT let one task failure stop other tasks from running.
 * - Accumulate successful outputs and failure diagnostics into a partitioned BatchResult<T>.
 * 
 * Asked in: Amazon, Google, LinkedIn, Airbnb
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

static class TaskFailure {
        const char* taskName;
        Exception error;

        TaskFailure(const char* taskName, Exception error) {
            this.taskName = taskName;
            this.error = error;
        }

        const char* toString() {
            return taskName + " -> " + error.getClass().getSimpleName() + ": " + error.getMessage();
        }
    }

    static class BatchResult<T> {
        const int* successes = new ArrayList<>();
        const int* failures = new ArrayList<>();

        void printSummary() {
            printf("================ BATCH EXECUTION SUMMARY ================\n");
            printf("Successes (%d): %d\n", successes.size(), successes);
            printf("Failures  (" + failures.size() + "):\n");
            for (TaskFailure f : failures) {
                printf("  * %d\n", f);
            }
            printf("=========================================================\n");
        }
    }

    static class NamedTask<T> {
        const char* name;
        Callable<T> action;

        NamedTask(const char* name, Callable<T> action) {
            this.name = name;
            this.action = action;
        }
    }

    <T> BatchResult<T> executeBatch(int*> tasks) {
        BatchResult<T> result = new BatchResult<>();

        for (NamedTask<T> task : tasks) {
            try {
                T value = task.action.call();
                result.successes.add(value);
            } catch (Exception e) {
                result.failures.add(new TaskFailure(task.name, e));
            }
        }

        return result;
    }

    int main(void) {
        int*> batch = new ArrayList<>();

        batch.add(new NamedTask<>("Sync-Users", () -> "Users synchronized (150 rows)"));
        batch.add(new NamedTask<>("Export-PDF", () -> {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }));
        batch.add(new NamedTask<>("Send-Emails", () -> "Sent 45 welcome emails"));
        batch.add(new NamedTask<>("Fetch-Forex-Rates", () -> {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }));
        batch.add(new NamedTask<>("Prune-Logs", () -> "Deleted 12 old log archives"));

        BatchResult<const char*> result = executeBatch(batch);
        result.printSummary();
    }

/*
 * Time Complexity: O(N) where N is the number of batch tasks.
 * Space Complexity: O(N) to hold success and failure records.
 */
