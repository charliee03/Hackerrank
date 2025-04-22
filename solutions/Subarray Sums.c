#include <stdio.h>
#include <stdlib.h>

long* findSum(int* numbers, int numbers_count, int** queries, int queries_rows, int queries_columns, int* result_count) {
    // Prefix sums for numbers and zero count
    long *prefix_sum = malloc((numbers_count + 1) * sizeof(long));
    int *zero_count = malloc((numbers_count + 1) * sizeof(int));
    
    prefix_sum[0] = 0;
    zero_count[0] = 0;
    
    for (int i = 0; i < numbers_count; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + numbers[i];
        zero_count[i + 1] = zero_count[i] + (numbers[i] == 0 ? 1 : 0);
    }
    
    // Allocate memory for results
    *result_count = queries_rows;
    long *result = malloc(queries_rows * sizeof(long));
    
    // Process each query
    for (int i = 0; i < queries_rows; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        int x = queries[i][2];
        
        // Calculate sum of subarray and add x * (count of zeros)
        result[i] = prefix_sum[r] - prefix_sum[l - 1] + x * (zero_count[r] - zero_count[l - 1]);
    }
    
    free(prefix_sum);
    free(zero_count);
    
    return result;
}

int main() {
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int numbers_count;
    scanf("%d", &numbers_count);
    
    int *numbers = malloc(numbers_count * sizeof(int));
    for (int i = 0; i < numbers_count; i++) {
        scanf("%d", &numbers[i]);
    }

    int queries_rows, queries_columns;
    scanf("%d %d", &queries_rows, &queries_columns);
    
    int **queries = malloc(queries_rows * sizeof(int*));
    for (int i = 0; i < queries_rows; i++) {
        queries[i] = malloc(queries_columns * sizeof(int));
        for (int j = 0; j < queries_columns; j++) {
            scanf("%d", &queries[i][j]);
        }
    }

    int result_count;
    long *result = findSum(numbers, numbers_count, queries, queries_rows, queries_columns, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%ld\n", result[i]);
    }

    // Free allocated memory
    free(numbers);
    for (int i = 0; i < queries_rows; i++) {
        free(queries[i]);
    }
    free(queries);
    free(result);
    
    fclose(fptr);
    return 0;
}