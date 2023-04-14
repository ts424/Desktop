#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
};

int compare_arrival_time(const void *a, const void *b) {
    const struct Process *p1 = (const struct Process *)a;
    const struct Process *p2 = (const struct Process *)b;
    return p1->arrival_time - p2->arrival_time;
}

int compare_burst_time(const void *a, const void *b) {
    const struct Process *p1 = (const struct Process *)a;
    const struct Process *p2 = (const struct Process *)b;
    return p2->burst_time - p1->burst_time;
}

int main() {
    int n, i, j, current_time = 0;
    float avg_waiting_time = 0.0, avg_turnaround_time = 0.0;
    struct Process *processes;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    processes = (struct Process *)malloc(n * sizeof(struct Process));

    printf("Enter the arrival time and burst time of each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
    }

    qsort(processes, n, sizeof(struct Process), compare_arrival_time);

    printf("\nGantt Chart Presentation.\n");

    for (i = 0; i < n; i++) {
        int max_burst_time = -1, max_burst_time_index = -1;
        for (j = 0; j < n; j++) {
            if (processes[j].arrival_time <= current_time && processes[j].burst_time > max_burst_time) {
                max_burst_time = processes[j].burst_time;
                max_burst_time_index = j;
            }
        }

        if (max_burst_time_index == -1) {
            printf("idle ");
            current_time++;
            continue;
        }

        printf("P%d ", processes[max_burst_time_index].pid);
        avg_waiting_time += current_time - processes[max_burst_time_index].arrival_time;
        current_time += processes[max_burst_time_index].burst_time;
        avg_turnaround_time += current_time - processes[max_burst_time_index].arrival_time;

        processes[max_burst_time_index].burst_time = 0;
    }

    printf("\n\nAverage waiting time: %.2f", avg_waiting_time / n);
    printf("\nAverage turnaround time: %.2f", avg_turnaround_time / n);

    free(processes);
    return 0;
}
