#include <stdio.h>
#include <stdlib.h>

// GCD function
long gcd(long a, long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Structure to represent a reduced ratio
typedef struct {
    long w;
    long h;
} Ratio;

// Structure to store count of each ratio
typedef struct {
    Ratio ratio;
    int count;
} RatioCount;

long nearlySimilarRectangles(long **sides, int sides_rows, int sides_columns) {
    RatioCount *ratios = malloc(sides_rows * sizeof(RatioCount));
    int unique_count = 0;
    
    // Process each rectangle
    for (int i = 0; i < sides_rows; i++) {
        long w = sides[i][0];
        long h = sides[i][1];
        long common_factor = gcd(w, h);
        
        // Reduce the ratio
        Ratio current_ratio = {w / common_factor, h / common_factor};
        
        // Check if this ratio already exists
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (ratios[j].ratio.w == current_ratio.w && ratios[j].ratio.h == current_ratio.h) {
                ratios[j].count++;
                found = 1;
                break;
            }
        }
        
        // If not found, add new ratio
        if (!found) {
            ratios[unique_count].ratio = current_ratio;
            ratios[unique_count].count = 1;
            unique_count++;
        }
    }
    
    // Calculate the number of pairs
    long result = 0;
    for (int i = 0; i < unique_count; i++) {
        long c = ratios[i].count;
        result += (c * (c - 1)) / 2;
    }
    
    free(ratios);
    return result;
}

int main() {
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int sides_rows, sides_columns;
    scanf("%d %d", &sides_rows, &sides_columns);
    
    long **sides = malloc(sides_rows * sizeof(long*));
    for (int i = 0; i < sides_rows; i++) {
        sides[i] = malloc(sides_columns * sizeof(long));
        for (int j = 0; j < sides_columns; j++) {
            scanf("%ld", &sides[i][j]);
        }
    }

    long result = nearlySimilarRectangles(sides, sides_rows, sides_columns);
    fprintf(fptr, "%ld\n", result);

    for (int i = 0; i < sides_rows; i++) {
        free(sides[i]);
    }
    free(sides);
    
    fclose(fptr);
    return 0;
}