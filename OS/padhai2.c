#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;  // process ID
    int arrival_time;  // arrival time
    int burst_time;  // burst time
    int remaining_time;  // remaining burst time
};

void lrtf_scheduling(struct process *procs, int n) {
    int time = 0;
    int complete = 0;
    int i, max_i;
    float avg_tat = 0, avg_wt = 0;
    printf("Gantt Chart:\n|");
    while (complete < n) {
        max_i = -1;
        for (i = 0; i < n; i++) {
            if (procs[i].arrival_time <= time && procs[i].remaining_time > 0) {
                if (max_i == -1 || procs[i].remaining_time > procs[max_i].remaining_time) {
                    max_i = i;
                }
            }
        }
        if (max_i == -1) {
            printf("IDLE|");
            time++;
        } else {
            printf("P%d|", procs[max_i].pid);
            procs[max_i].remaining_time--;
            if (procs[max_i].remaining_time == 0) {
                complete++;
                procs[max_i].remaining_time = -1;
                int ct = time + 1;
                int tat = ct - procs[max_i].arrival_time;
                int wt = tat - procs[max_i].burst_time;
                avg_tat += tat;
                avg_wt += wt;
            }
            time++;
        }
    }
    printf("\n\nProcess\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", procs[i].pid, procs[i].arrival_time + procs[i].burst_time, procs[i].arrival_time + procs[i].burst_time - procs[i].arrival_time, procs[i].arrival_time + procs[i].burst_time - procs[i].arrival_time - procs[i].burst_time);
    }
    printf("\nAverage Turnaround Time = %f\n", avg_tat / n);
    printf("Average Waiting Time = %f\n", avg_wt / n);
}

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process *procs = (struct process *) malloc(n * sizeof(struct process));
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &procs[i].arrival_time, &procs[i].burst_time);
        procs[i].pid = i + 1;
        procs[i].remaining_time = procs[i].burst_time;
    }
    lrtf_scheduling(procs, n);
    free(procs);
    return 0;
}
