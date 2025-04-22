#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 10000
#define MAX_NAME_LEN 51

// Structure for storing customer name and count
typedef struct {
    char name[MAX_NAME_LEN];
    int count;
} Customer;

// Comparator for qsort (alphabetical order)
int compareNames(const void *a, const void *b) {
    return strcmp(((Customer *)a)->name, ((Customer *)b)->name);
}

// Find or add customer to list
int findOrAddCustomer(Customer customers[], int *size, const char *name) {
    for (int i = 0; i < *size; ++i) {
        if (strcmp(customers[i].name, name) == 0) {
            customers[i].count++;
            return i;
        }
    }
    strcpy(customers[*size].name, name);
    customers[*size].count = 1;
    (*size)++;
    return *size - 1;
}

int main() {
    int customers_count;
    scanf("%d\n", &customers_count);

    Customer customers[MAX_CUSTOMERS];
    int size = 0;

    char name[MAX_NAME_LEN];

    for (int i = 0; i < customers_count; ++i) {
        fgets(name, MAX_NAME_LEN, stdin);
        name[strcspn(name, "\n")] = 0; // Remove newline
        findOrAddCustomer(customers, &size, name);
    }

    // Calculate 5% threshold
    double threshold = 0.05 * customers_count;

    // Filter and collect active customers
    Customer active[MAX_CUSTOMERS];
    int active_count = 0;
    for (int i = 0; i < size; ++i) {
        if (customers[i].count >= threshold) {
            active[active_count++] = customers[i];
        }
    }

    // Sort the active customers alphabetically
    qsort(active, active_count, sizeof(Customer), compareNames);

    // Write output to OUTPUT_PATH file
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");
    for (int i = 0; i < active_count; ++i) {
        fprintf(fptr, "%s\n", active[i].name);
    }
    fclose(fptr);

    return 0;
}
