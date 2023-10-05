#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};


int find_highest_priority(struct Process processes[], int n, int current_time) {
    int highest_priority = TMP_MAX;
    int selected_process = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].priority < highest_priority && processes[i].remaining_time > 0) {
            highest_priority = processes[i].priority;
            selected_process = i;
        }
    }

    return selected_process;
}


void calculate_turnaround_waiting_time(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

  
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    int current_time = 0;
    int completed_processes = 0;

    printf("\nGantt Chart:\n");

  
    while (completed_processes < n) {
        int selected_process = find_highest_priority(processes, n, current_time);

        if (selected_process == -1) {
            current_time++;
        } else {
            processes[selected_process].remaining_time--;

            printf("| P%d ", processes[selected_process].pid);
            current_time++;

            if (processes[selected_process].remaining_time == 0) {
                completed_processes++;
                processes[selected_process].turnaround_time = current_time - processes[selected_process].arrival_time;
                processes[selected_process].waiting_time = processes[selected_process].turnaround_time - processes[selected_process].burst_time;
            }
        }
    }

    
    printf("|\n\n");
    printf("Process\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].pid, processes[i].turnaround_time, processes[i].waiting_time);
    }

   
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }

    float avg_turnaround_time = (float)total_turnaround_time / n;
    float avg_waiting_time = (float)total_waiting_time / n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);

    return 0;
}

