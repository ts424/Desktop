#include <stdio.h>
#include <stdlib.h>

struct process {
    int id;
    int burst_time;
};

int compare(const void *a, const void *b) {
    struct process *processA = (struct process *)a;
    struct process *processB = (struct process *)b;
    return (processA->burst_time - processB->burst_time);
}

int main() {
    int n, i;
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    int waiting_time[20], turnaround_time[20];
    struct process p[20];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        p[i].id = i+1;
        printf("Enter the id and burst time for process.");
        scanf("%d %d",&p[i].id,&p[i].burst_time);
    }

    qsort(p, n, sizeof(struct process), compare);

    waiting_time[0] = 0;
    for(i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i-1] + p[i-1].burst_time;
    }

    for(i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + p[i].burst_time;
    }

    for(i = 0; i < n; i++) {
        avg_waiting_time = avg_waiting_time + waiting_time[i];
        avg_turnaround_time = avg_turnaround_time + turnaround_time[i];
    }
    avg_waiting_time = avg_waiting_time/n;
    avg_turnaround_time = avg_turnaround_time/n;

    printf("\nProcess      \tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("Process ID %d\t\t\t%d\t\t\t%d\t\t\t\t%d\n", p[i].id, p[i].burst_time, waiting_time[i], turnaround_time[i]);
    }
    printf("\nAverage waiting time: %.2f\n", avg_waiting_time);
    printf("Average turnaround time: %.2f\n", avg_turnaround_time);

    return 0;
}
