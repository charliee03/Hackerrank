#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int abs_diff(int a, int b) {
    return a > b ? a - b : b - a;
}

int longestSubarray(int *arr, int arr_count) {
    int ans = 0;
    
    // O(n^2) approach is fine given the constraints
    for (int i = 0; i < arr_count; i++) {
        int w[2] = {-1, -1}; // Store the two unique values
        int w_count = 0;     // Count of unique values
        int cnt = 0;         // Length of current subarray
        
        for (int j = i; j < arr_count; j++) {
            // Check if current value is already in our window
            int already_exists = 0;
            for (int k = 0; k < w_count; k++) {
                if (w[k] == arr[j]) {
                    already_exists = 1;
                    break;
                }
            }
            
            if (already_exists) {
                cnt++;
                continue;
            }
            
            // If we have less than 2 unique values, add the current one
            if (w_count == 0) {
                w[w_count++] = arr[j];
                cnt++;
            } else if (w_count == 1) {
                if (abs_diff(w[0], arr[j]) <= 1) {
                    w[w_count++] = arr[j];
                    cnt++;
                } else {
                    break;
                }
            } else {
                // We already have 2 values and this is a new one, so break
                break;
            }
        }
        
        ans = max(ans, cnt);
    }
    
    return ans;
}

int main() {
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int arr_count;
    scanf("%d", &arr_count);
    
    int *arr = malloc(arr_count * sizeof(int));
    for (int i = 0; i < arr_count; i++) {
        scanf("%d", &arr[i]);
    }

    int result = longestSubarray(arr, arr_count);
    fprintf(fptr, "%d\n", result);

    free(arr);
    fclose(fptr);
    return 0;
}