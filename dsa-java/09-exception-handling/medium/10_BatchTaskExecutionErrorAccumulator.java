/*
 * Problem Statement:
 * Design a Batch Task Execution Engine that executes N independent tasks:
 * - Tasks can fail due to unpredictable exceptions.
 * - Do NOT let one task failure stop other tasks from running.
 * - Accumulate successful outputs and failure diagnostics into a partitioned BatchResult<T>.
 * 
 * Asked in: Amazon, Google, LinkedIn, Airbnb
 */

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;

class BatchTaskExecutionErrorAccumulator {

    static class TaskFailure {
        String taskName;
        Exception error;

        TaskFailure(String taskName, Exception error) {
            this.taskName = taskName;
            this.error = error;
        }

        @Override
        public String toString() {
            return taskName + " -> " + error.getClass().getSimpleName() + ": " + error.getMessage();
        }
    }

    static class BatchResult<T> {
        final List<T> successes = new ArrayList<>();
        final List<TaskFailure> failures = new ArrayList<>();

        public void printSummary() {
            System.out.println("================ BATCH EXECUTION SUMMARY ================");
            System.out.println("Successes (" + successes.size() + "): " + successes);
            System.out.println("Failures  (" + failures.size() + "):");
            for (TaskFailure f : failures) {
                System.out.println("  * " + f);
            }
            System.out.println("=========================================================");
        }
    }

    static class NamedTask<T> {
        String name;
        Callable<T> action;

        NamedTask(String name, Callable<T> action) {
            this.name = name;
            this.action = action;
        }
    }

    public static <T> BatchResult<T> executeBatch(List<NamedTask<T>> tasks) {
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

    public static void main(String[] args) {
        List<NamedTask<String>> batch = new ArrayList<>();

        batch.add(new NamedTask<>("Sync-Users", () -> "Users synchronized (150 rows)"));
        batch.add(new NamedTask<>("Export-PDF", () -> {
            throw new IllegalStateException("Disk write space exhausted");
        }));
        batch.add(new NamedTask<>("Send-Emails", () -> "Sent 45 welcome emails"));
        batch.add(new NamedTask<>("Fetch-Forex-Rates", () -> {
            throw new RuntimeException("API key expired");
        }));
        batch.add(new NamedTask<>("Prune-Logs", () -> "Deleted 12 old log archives"));

        BatchResult<String> result = executeBatch(batch);
        result.printSummary();
    }
}

/*
 * Time Complexity: O(N) where N is the number of batch tasks.
 * Space Complexity: O(N) to hold success and failure records.
 */
