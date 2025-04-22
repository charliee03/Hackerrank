#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

long getMinCost(int *crew_id, int crew_id_count, int *job_id, int job_id_count) {
    // Sort both arrays
    qsort(crew_id, crew_id_count, sizeof(int), compare);
    qsort(job_id, job_id_count, sizeof(int), compare);
    
    // Calculate minimum cost
    long total_cost = 0;
    for (int i = 0; i < crew_id_count; i++) {
        int diff = crew_id[i] - job_id[i];
        // Calculate absolute value
        if (diff < 0) {
            diff = -diff;
        }
        total_cost += diff;
    }
    
    return total_cost;
}

int main() {
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int crew_id_count;
    scanf("%d", &crew_id_count);
    
    int *crew_id = malloc(crew_id_count * sizeof(int));
    for (int i = 0; i < crew_id_count; i++) {
        scanf("%d", &crew_id[i]);
    }

    int job_id_count;
    scanf("%d", &job_id_count);
    
    int *job_id = malloc(job_id_count * sizeof(int));
    for (int i = 0; i < job_id_count; i++) {
        scanf("%d", &job_id[i]);
    }

    long result = getMinCost(crew_id, crew_id_count, job_id, job_id_count);
    fprintf(fptr, "%ld\n", result);

    free(crew_id);
    free(job_id);
    fclose(fptr);
    return 0;
}