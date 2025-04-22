#include <stdio.h>
#include <stdlib.h>

// Comparison function for sorting in descending order
int compare_desc(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

long minTime(int *files, int files_count, int numCores, int limit) {
    int *divisible = malloc(files_count * sizeof(int));
    int *non_divisible = malloc(files_count * sizeof(int));
    int div_count = 0, non_div_count = 0;
    
    // Separate files into divisible and non-divisible by numCores
    for (int i = 0; i < files_count; i++) {
        if (files[i] % numCores == 0) {
            divisible[div_count++] = files[i];
        } else {
            non_divisible[non_div_count++] = files[i];
        }
    }
    
    // Sort divisible files in descending order
    qsort(divisible, div_count, sizeof(int), compare_desc);
    
    // Calculate the total time
    long total_time = 0;
    
    // Process divisible files up to the limit with parallel cores
    for (int i = 0; i < div_count; i++) {
        if (i < limit) {
            total_time += divisible[i] / numCores;
        } else {
            total_time += divisible[i]; // Process sequentially
        }
    }
    
    // Add the time for non-divisible files
    for (int i = 0; i < non_div_count; i++) {
        total_time += non_divisible[i];
    }
    
    free(divisible);
    free(non_divisible);
    
    return total_time;
}

int main() {
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int files_count;
    scanf("%d", &files_count);
    
    int *files = malloc(files_count * sizeof(int));
    for (int i = 0; i < files_count; i++) {
        scanf("%d", &files[i]);
    }

    int numCores, limit;
    scanf("%d %d", &numCores, &limit);

    long result = minTime(files, files_count, numCores, limit);
    fprintf(fptr, "%ld\n", result);

    free(files);
    fclose(fptr);
    return 0;
}