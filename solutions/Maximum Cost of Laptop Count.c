#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int maxCost(int *cost, int cost_count, char **labels, int labels_count, int dailyCount) {
    int ans = 0;
    int cur_cnt = 0;
    int cur_cost = 0;
    
    for (int i = 0; i < cost_count; i++) {
        cur_cost += cost[i];
        
        if (strcmp(labels[i], "illegal") == 0) {
            continue;
        }
        
        cur_cnt++;
        
        if (cur_cnt == dailyCount) {
            ans = max(ans, cur_cost);
            cur_cnt = 0;
            cur_cost = 0;
        }
    }
    
    return ans;
}

int main() {
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int cost_count;
    scanf("%d", &cost_count);
    
    int *cost = malloc(cost_count * sizeof(int));
    for (int i = 0; i < cost_count; i++) {
        scanf("%d", &cost[i]);
    }

    int labels_count;
    scanf("%d", &labels_count);
    
    char **labels = malloc(labels_count * sizeof(char*));
    for (int i = 0; i < labels_count; i++) {
        labels[i] = malloc(8 * sizeof(char)); // "illegal" or "legal" + null terminator
        scanf("%s", labels[i]);
    }

    int dailyCount;
    scanf("%d", &dailyCount);

    int result = maxCost(cost, cost_count, labels, labels_count, dailyCount);
    fprintf(fptr, "%d\n", result);

    for (int i = 0; i < labels_count; i++) {
        free(labels[i]);
    }
    free(labels);
    free(cost);
    
    fclose(fptr);
    return 0;
}