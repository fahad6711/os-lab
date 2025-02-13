#include <stdio.h>

struct Process {
    int pid, burst_time, arrival_time, priority, remaining_time, completion_time, waiting_time, turnaround_time;
};

void sjf(struct Process p[], int n) {
    int time = 0, completed = 0;
    for (int i = 0; i < n; i++) p[i].remaining_time = p[i].burst_time;
    
    while (completed < n) {
        int shortest = -1, min_burst = __INT_MAX__;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && p[i].remaining_time > 0 && p[i].remaining_time < min_burst) {
                shortest = i;
                min_burst = p[i].remaining_time;
            }
        }
        if (shortest == -1) {
            time++;
            continue;
        }
        p[shortest].remaining_time--;
        time++;
        if (p[shortest].remaining_time == 0) {
            completed++;
            p[shortest].completion_time = time;
            p[shortest].turnaround_time = p[shortest].completion_time - p[shortest].arrival_time;
            p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].burst_time;
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d - Burst Time & Arrival Time: ", i + 1);
        scanf("%d %d", &p[i].burst_time, &p[i].arrival_time);
    }
    
    sjf(p, n);
    
    printf("\nProcess\tBT\tAT\tCT\tTAT\tWT\n");
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].burst_time, p[i].arrival_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
        avg_tat += p[i].turnaround_time;
        avg_wt += p[i].waiting_time;
    }
    
    printf("\nAverage TAT: %.2f\nAverage WT: %.2f\n", avg_tat / n, avg_wt / n);
    return 0;
}
