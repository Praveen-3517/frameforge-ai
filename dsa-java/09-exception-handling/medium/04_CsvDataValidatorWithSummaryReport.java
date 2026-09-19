/*
 * Problem Statement:
 * Design a CSV Data Validator that accumulates all row-level errors into a detailed
 * batch validation report instead of aborting on the first bad row:
 * - Expected columns: id (integer > 0), email (valid syntax), age (1 to 120).
 * - Collect all parsing exceptions and validation violations with line numbers.
 * 
 * Asked in: Intuit, Workday, Salesforce, Bloomberg
 */

import java.util.ArrayList;
import java.util.List;

class CsvDataValidatorWithSummaryReport {

    static class RowError {
        int rowNumber;
        String rawLine;
        String errorMessage;

        RowError(int rowNumber, String rawLine, String errorMessage) {
            this.rowNumber = rowNumber;
            this.rawLine = rawLine;
            this.errorMessage = errorMessage;
        }

        @Override
        public String toString() {
            return String.format("Line %2d | Error: %-35s | Raw: \"%s\"", rowNumber, errorMessage, rawLine);
        }
    }

    static class ValidationSummary {
        int totalRows = 0;
        int validRows = 0;
        final List<RowError> errors = new ArrayList<>();

        public void printReport() {
            System.out.println("================ CSV INGESTION REPORT ================");
            System.out.printf("Total Rows Processed: %d | Valid: %d | Errors: %d%n",
                    totalRows, validRows, errors.size());
            if (!errors.isEmpty()) {
                System.out.println("Detailed Errors Encountered:");
                for (RowError err : errors) {
                    System.out.println("  " + err);
                }
            }
            System.out.println("=====================================================");
        }
    }

    public static ValidationSummary validateCsv(String[] csvLines) {
        ValidationSummary summary = new ValidationSummary();

        for (int i = 0; i < csvLines.length; i++) {
            summary.totalRows++;
            String line = csvLines[i].trim();
            if (line.isEmpty() || line.startsWith("#")) continue;

            String[] tokens = line.split(",");
            if (tokens.length != 3) {
                summary.errors.add(new RowError(i + 1, line, "Expected 3 columns, found " + tokens.length));
                continue;
            }

            // Validate ID
            try {
                int id = Integer.parseInt(tokens[0].trim());
                if (id <= 0) throw new IllegalArgumentException("ID must be positive");
            } catch (Exception e) {
                summary.errors.add(new RowError(i + 1, line, "Invalid ID format: " + tokens[0].trim()));
                continue;
            }

            // Validate Email
            String email = tokens[1].trim();
            if (!email.contains("@") || !email.contains(".")) {
                summary.errors.add(new RowError(i + 1, line, "Invalid email address: " + email));
                continue;
            }

            // Validate Age
            try {
                int age = Integer.parseInt(tokens[2].trim());
                if (age < 1 || age > 120) {
                    summary.errors.add(new RowError(i + 1, line, "Age out of range [1-120]: " + age));
                    continue;
                }
            } catch (Exception e) {
                summary.errors.add(new RowError(i + 1, line, "Invalid age number: " + tokens[2].trim()));
                continue;
            }

            summary.validRows++;
        }

        return summary;
    }

    public static void main(String[] args) {
        String[] csvData = {
            "1, alice@example.com, 28",
            "2, bad_email_format, 34",
            "-5, charlie@corp.org, 45",
            "4, david@test.com, 150",
            "not_an_id, eve@example.com, 22",
            "6, frank@company.com, 29, extra_field",
            "7, grace@domain.io, 31"
        };

        ValidationSummary summary = validateCsv(csvData);
        summary.printReport();
    }
}

/*
 * Time Complexity: O(R * C) where R is rows and C is columns per row.
 * Space Complexity: O(E) where E is the count of failed rows stored in error report.
 */
