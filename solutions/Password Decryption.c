#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* decryptPassword(char* s) {
    int len = strlen(s);
    char* result = malloc((len + 1) * sizeof(char));
    strcpy(result, s);
    
    // Find the position where digits end
    int i = 0;
    while (i < len && result[i] >= '1' && result[i] <= '9') {
        i++;
    }
    
    // Replace zeros with digits from the beginning
    int zero_count = 0;
    for (int j = i; j < len; j++) {
        if (result[j] == '0') {
            result[j] = result[i - zero_count - 1];
            zero_count++;
        }
    }
    
    // Swap letters around '*'
    for (int j = i; j < len; j++) {
        if (result[j] == '*') {
            char temp = result[j-1];
            result[j-1] = result[j-2];
            result[j-2] = temp;
        }
    }
    
    // Remove digits at the beginning and '*' characters
    char* final_result = malloc((len + 1) * sizeof(char));
    int k = 0;
    for (int j = i; j < len; j++) {
        if (result[j] != '*') {
            final_result[k++] = result[j];
        }
    }
    final_result[k] = '\0';
    
    free(result);
    return final_result;
}

int main() {
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char s[100001];
    scanf("%s", s);

    char* result = decryptPassword(s);
    fprintf(fptr, "%s\n", result);

    free(result);
    fclose(fptr);
    return 0;
}