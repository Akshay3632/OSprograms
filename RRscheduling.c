#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_PROCESS 10

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
};

// Function to generate random CPU burst time for a process
int generate_random_burst() {
    return (rand() % 10) + 1; // Generates a random burst time between 1 and 10
}

int main() {
    srand(time(NULL));

    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAX_PROCESS];
    int time_quantum;

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    // Input for arrival time and first CPU burst time
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter first CPU burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    int total_time = 0;
    int io_waiting_time = 2; // Fixed IO waiting time
    int completed_processes = 0;
    int current_process = 0;

    printf("\nGantt Chart:\n");

    while (completed_processes < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= total_time && processes[i].remaining_time > 0) {
                found = true;
                if (processes[i].remaining_time <= time_quantum) {
                    // Process completes within time quantum
                    total_time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                } else {
                    // Process still has remaining burst time
                    total_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                }
                printf("| P%d ", processes[i].id);
                // Generate random next CPU burst
                int next_burst = generate_random_burst();
                total_time += io_waiting_time;
                printf("(I/O) |");
                total_time += next_burst;
                processes[i].turnaround_time = total_time - processes[i].arrival_time;
                processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                completed_processes++;
            }
        }
        if (!found) {
            // No process is ready to execute, increase total_time
            total_time++;
        }
    }

    printf("\n\nProcess\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}

