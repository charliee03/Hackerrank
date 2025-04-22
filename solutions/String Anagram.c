#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compare characters for qsort
int compare_chars(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

// Structure to hold sorted words and their counts
typedef struct {
    char *sorted_word;
    int count;
} WordCount;

int* stringAnagram(char** dictionary, int dictionary_count, char** query, int query_count, int* result_count) {
    // Allocate memory for the result
    int *result = malloc(query_count * sizeof(int));
    *result_count = query_count;
    
    // Create an array to store sorted words and their counts
    WordCount *word_counts = malloc(dictionary_count * sizeof(WordCount));
    int unique_count = 0;
    
    // Process dictionary words
    for (int i = 0; i < dictionary_count; i++) {
        int len = strlen(dictionary[i]);
        char *sorted = malloc((len + 1) * sizeof(char));
        strcpy(sorted, dictionary[i]);
        
        // Sort the word
        qsort(sorted, len, sizeof(char), compare_chars);
        
        // Check if this sorted word already exists
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strcmp(sorted, word_counts[j].sorted_word) == 0) {
                word_counts[j].count++;
                found = 1;
                free(sorted);
                break;
            }
        }
        
        // If not found, add to the array
        if (!found) {
            word_counts[unique_count].sorted_word = sorted;
            word_counts[unique_count].count = 1;
            unique_count++;
        }
    }
    
    // Process queries
    for (int i = 0; i < query_count; i++) {
        int len = strlen(query[i]);
        char *sorted = malloc((len + 1) * sizeof(char));
        strcpy(sorted, query[i]);
        
        // Sort the query
        qsort(sorted, len, sizeof(char), compare_chars);
        
        // Find matching sorted word
        result[i] = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strcmp(sorted, word_counts[j].sorted_word) == 0) {
                result[i] = word_counts[j].count;
                break;
            }
        }
        
        free(sorted);
    }
    
    // Free allocated memory
    for (int i = 0; i < unique_count; i++) {
        free(word_counts[i].sorted_word);
    }
    free(word_counts);
    
    return result;
}

int main() {
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int dictionary_count;
    scanf("%d", &dictionary_count);
    
    char **dictionary = malloc(dictionary_count * sizeof(char*));
    for (int i = 0; i < dictionary_count; i++) {
        dictionary[i] = malloc(101 * sizeof(char)); // Assuming max word length is 100 chars
        scanf("%s", dictionary[i]);
    }

    int query_count;
    scanf("%d", &query_count);
    
    char **query = malloc(query_count * sizeof(char*));
    for (int i = 0; i < query_count; i++) {
        query[i] = malloc(101 * sizeof(char));
        scanf("%s", query[i]);
    }

    int result_count;
    int *result = stringAnagram(dictionary, dictionary_count, query, query_count, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d\n", result[i]);
    }

    // Free allocated memory
    for (int i = 0; i < dictionary_count; i++) {
        free(dictionary[i]);
    }
    free(dictionary);
    
    for (int i = 0; i < query_count; i++) {
        free(query[i]);
    }
    free(query);
    
    free(result);
    fclose(fptr);
    return 0;
}