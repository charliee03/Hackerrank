#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100001

// Function to check if a character is a vowel
int isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

// Function to find substring with the maximum number of vowels
char* findSubstring(const char* s, int k) {
    int len = strlen(s);
    int cur = 0, best = 0, start = -1;

    // Count vowels in the first window
    for (int i = 0; i < k && i < len; i++) {
        cur += isVowel(s[i]);
    }

    best = cur;
    if (best > 0) start = 0;

    // Slide the window
    for (int i = k; i < len; i++) {
        cur += isVowel(s[i]);
        cur -= isVowel(s[i - k]);
        if (cur > best) {
            best = cur;
            start = i - k + 1;
        }
    }

    // Return result
    char* result = (char*)malloc((k + 20) * sizeof(char));
    if (best > 0 && start != -1) {
        strncpy(result, s + start, k);
        result[k] = '\0';
    } else {
        strcpy(result, "Not found!");
    }
    return result;
}

int main() {
    char s[MAX_LEN];
    int k;

    fgets(s, MAX_LEN, stdin);
    s[strcspn(s, "\n")] = '\0'; // Remove newline

    scanf("%d", &k);

    char* result = findSubstring(s, k);

    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    if (!fptr) {
        fprintf(stderr, "Error opening OUTPUT_PATH\n");
        return 1;
    }

    fprintf(fptr, "%s\n", result);
    fclose(fptr);

    free(result);
    return 0;
}
