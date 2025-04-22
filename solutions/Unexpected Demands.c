#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int filledOrders(int* order, int order_count, int k) {
    // Sort the orders
    qsort(order, order_count, sizeof(int), compare);
    
    int fulfilled = 0;
    
    // Process orders in ascending order
    for (int i = 0; i < order_count; i++) {
        if (order[i] <= k) {
            fulfilled++;
            k -= order[i];
        } else {
            break;
        }
    }
    
    return fulfilled;
}

int main() {
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int order_count;
    scanf("%d", &order_count);
    
    int *order = malloc(order_count * sizeof(int));
    for (int i = 0; i < order_count; i++) {
        scanf("%d", &order[i]);
    }

    int k;
    scanf("%d", &k);

    int result = filledOrders(order, order_count, k);
    fprintf(fptr, "%d\n", result);

    free(order);
    fclose(fptr);
    return 0;
}