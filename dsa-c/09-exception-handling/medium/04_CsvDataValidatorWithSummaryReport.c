/*
 * Problem Statement:
 * Design a CSV Data Validator that accumulates all row-level errors into a detailed
 * batch validation report instead of aborting on the first bad row:
 * - Expected columns: id (integer > 0), email (valid syntax), age (1 to 120).
 * - Collect all parsing exceptions and validation violations with line numbers.
 * 
 * Asked in: Intuit, Workday, Salesforce, Bloomberg
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

static class RowError {
        int rowNumber;
        const char* rawLine;
        const char* errorMessage;

        RowError(int rowNumber, const char* rawLine, const char* errorMessage) {
            this.rowNumber = rowNumber;
            this.rawLine = rawLine;
            this.errorMessage = errorMessage;
        }

        const char* toString() {
            return const char*.format("Line %2d | Error: %-35s | Raw: \"%s\"", rowNumber, errorMessage, rawLine);
        }
    }

    static class ValidationSummary {
        int totalRows = 0;
        int validRows = 0;
        const int* errors = new ArrayList<>();

        void printReport() {
            printf("================ CSV INGESTION REPORT ================\n");
            printf("Total Rows Processed: %d | Valid: %d | Errors: %d\n",
                    totalRows, validRows, errors.size());
            if (!errors.isEmpty()) {
                printf("Detailed Errors Encountered:\n");
                for (RowError err : errors) {
                    printf("  %d\n", err);
                }
            }
            printf("=====================================================\n");
        }
    }

    ValidationSummary validateCsv(const char*[] csvLines) {
        ValidationSummary summary = new ValidationSummary();

        for (int i = 0; i < n; i++) {
            summary.totalRows++;
            const char* line = csvLines[i].trim();
            if (line.isEmpty() || line.startsWith("#")) continue;

            const char*[] tokens = line.split(",");
            if (n != 3) {
                summary.errors.add(new RowError(i + 1, line, "Expected 3 columns, found " + n));
                continue;
            }

            // Validate ID
            try {
                int id = int.parseInt(tokens[0].trim());
                if (id <= 0) fprintf(stderr, "Exception: invalid argument
"); return 0;
            } catch (Exception e) {
                summary.errors.add(new RowError(i + 1, line, "Invalid ID format: " + tokens[0].trim()));
                continue;
            }

            // Validate Email
            const char* email = tokens[1].trim();
            if (!email.contains("@") || !email.contains(".")) {
                summary.errors.add(new RowError(i + 1, line, "Invalid email address: " + email));
                continue;
            }

            // Validate Age
            try {
                int age = int.parseInt(tokens[2].trim());
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

    int main(void) {
        const char*[] csvData = {
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
        return 0;
}

/*
 * Time Complexity: O(R * C) where R is rows and C is columns per row.
 * Space Complexity: O(E) where E is the count of failed rows stored in error report.
 */
