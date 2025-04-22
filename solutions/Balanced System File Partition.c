#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct node {
    int id;
    int file_size;
    struct node **children;
    int children_count;
    int children_capacity;
    long long total_size;
} Node;

void add_child(Node *parent, Node *child) {
    if (parent->children_count >= parent->children_capacity) {
        parent->children_capacity = parent->children_capacity ? parent->children_capacity * 2 : 2;
        parent->children = realloc(parent->children, parent->children_capacity * sizeof(Node *));
    }
    parent->children[parent->children_count++] = child;
}

long long calculate_total_size(Node *node) {
    node->total_size = node->file_size;
    for (int i = 0; i < node->children_count; i++) {
        node->total_size += calculate_total_size(node->children[i]);
    }
    return node->total_size;
}

int min_abs_diff(Node *root, long long total_size) {
    int min_diff = INT_MAX;
    
    // Helper function to find minimum difference
    void dfs(Node *node) {
        if (node->id != 0) {  // Skip the root node
            int diff = abs(total_size - 2 * node->total_size);
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
        
        for (int i = 0; i < node->children_count; i++) {
            dfs(node->children[i]);
        }
    }
    
    dfs(root);
    return min_diff;
}

int mostBalancedPartition(int *parent, int parent_count, int *files_size, int files_size_count) {
    // Create nodes
    Node *nodes = malloc(parent_count * sizeof(Node));
    for (int i = 0; i < parent_count; i++) {
        nodes[i].id = i;
        nodes[i].file_size = files_size[i];
        nodes[i].children = NULL;
        nodes[i].children_count = 0;
        nodes[i].children_capacity = 0;
        nodes[i].total_size = 0;
    }
    
    // Build the tree
    for (int i = 1; i < parent_count; i++) {
        add_child(&nodes[parent[i]], &nodes[i]);
    }
    
    // Calculate total sizes
    long long total_size = calculate_total_size(&nodes[0]);
    
    // Find minimum difference
    int result = min_abs_diff(&nodes[0], total_size);
    
    // Free allocated memory
    for (int i = 0; i < parent_count; i++) {
        free(nodes[i].children);
    }
    free(nodes);
    
    return result;
}

int main() {
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int parent_count;
    scanf("%d", &parent_count);
    
    int *parent = malloc(parent_count * sizeof(int));
    for (int i = 0; i < parent_count; i++) {
        scanf("%d", &parent[i]);
    }

    int files_size_count;
    scanf("%d", &files_size_count);
    
    int *files_size = malloc(files_size_count * sizeof(int));
    for (int i = 0; i < files_size_count; i++) {
        scanf("%d", &files_size[i]);
    }

    int result = mostBalancedPartition(parent, parent_count, files_size, files_size_count);
    fprintf(fptr, "%d\n", result);

    free(parent);
    free(files_size);
    fclose(fptr);
    return 0;
}