#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int num_processes, num_resources;
int available[MAX_RESOURCES];
int max_demand[MAX_PROCESSES][MAX_RESOURCES];
int allocated[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

void initialize() {
    // Initialize available resources, maximum demand, and allocated resources here
    // Example:
    num_processes = 5;
    num_resources = 3;

    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int alloc[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    for (int i = 0; i < num_resources; i++) {
        available[i] = 0;
        for (int j = 0; j < num_processes; j++) {
            allocated[j][i] = alloc[j][i];
            max_demand[j][i] = max[j][i];
            need[j][i] = max[j][i] - alloc[j][i];
        }
    }
}

bool is_safe_state() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = { false };

    // Initialize work and finish arrays
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    // Check for a safe state
    for (int i = 0; i < num_processes; i++) {
        if (!finish[i]) {
            bool can_execute = true;
            for (int j = 0; j < num_resources; j++) {
                if (need[i][j] > work[j]) {
                    can_execute = false;
                    break;
                }
            }

            if (can_execute) {
                for (int j = 0; j < num_resources; j++) {
                    work[j] += allocated[i][j];
                }
                finish[i] = true;
                i = -1; // Start from the beginning of the process list
            }
        }
    }

    // If all processes are marked as finished, it's a safe state
    for (int i = 0; i < num_processes; i++) {
        if (!finish[i]) {
            return false; // Unsafe state
        }
    }
    return true; // Safe state
}

void calculate_min_resources() {
    int min_resources[MAX_RESOURCES] = { 0 };
    int temp_available[MAX_RESOURCES];

    // Copy available to temp_available
    for (int i = 0; i < num_resources; i++) {
        temp_available[i] = available[i];
    }

    // Try allocating resources incrementally to find the minimum
    for (int i = 0; i < num_resources; i++) {
        for (int j = 0; j < num_processes; j++) {
            if (!is_safe_state()) {
                temp_available[i]++;
                min_resources[i]++;
            } else {
                break;
            }
        }
    }

    printf("Minimum resources needed to avoid deadlock: ");
    for (int i = 0; i < num_resources; i++) {
        printf("%d ", min_resources[i]);
    }
    printf("\n");
}

int main() {
    initialize();
    calculate_min_resources();

    return 0;
}

