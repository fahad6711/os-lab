#include <stdio.h>

#define MAX_PROCESSES 10

void roundRobin(int processes[], int n, int burst_time[], int quantum) {
    int remaining_time[MAX_PROCESSES], waiting_time[MAX_PROCESSES], turnaround_time[MAX_PROCESSES];
    int i, time = 0, completed = 0;

    // Copy burst times to remaining time array
    for (i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
        waiting_time[i] = 0;
    }

    // Round Robin scheduling
    while (completed < n) {
        for (i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    waiting_time[i] = time - burst_time[i];
                    remaining_time[i] = 0;
                    completed++;
                }
            }
        }
    }

    // Calculate turnaround time
    for (i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }

    // Print results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    float total_wt = 0, total_tat = 0;
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
        total_wt += waiting_time[i];
        total_tat += turnaround_time[i];
    }

    // Print average values
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n, quantum, i;
    int processes[MAX_PROCESSES], burst_time[MAX_PROCESSES];

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input process IDs and burst times
    printf("Enter burst times for %d processes: ", n);
    for (i = 0; i < n; i++) {
        processes[i] = i + 1;
        scanf("%d", &burst_time[i]);
    }

    // Input time quantum
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Call Round Robin function
    roundRobin(processes, n, burst_time, quantum);

    return 0;
}
