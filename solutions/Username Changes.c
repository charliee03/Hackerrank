#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 1001
#define MAX_USERNAMES 1000

// Function to check if a username can be changed to a lexicographically smaller version
const char* canBeChanged(const char* username) {
    int len = strlen(username);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (username[i] > username[j]) {
                return "YES";
            }
        }
    }
    return "NO";
}

int main() {
    int usernames_count;
    scanf("%d\n", &usernames_count);

    char usernames[MAX_USERNAMES][MAX_USERNAME_LEN];
    char results[MAX_USERNAMES][4]; // "YES" or "NO"

    // Read usernames
    for (int i = 0; i < usernames_count; i++) {
        fgets(usernames[i], MAX_USERNAME_LEN, stdin);
        usernames[i][strcspn(usernames[i], "\n")] = 0; // Remove newline
    }

    // Process each username
    for (int i = 0; i < usernames_count; i++) {
        strcpy(results[i], canBeChanged(usernames[i]));
    }

    // Write output to OUTPUT_PATH
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");
    if (!fptr) {
        fprintf(stderr, "Error opening OUTPUT_PATH\n");
        return 1;
    }

    for (int i = 0; i < usernames_count; i++) {
        fprintf(fptr, "%s\n", results[i]);
    }

    fclose(fptr);
    return 0;
}
