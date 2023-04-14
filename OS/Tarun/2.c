#include<stdio.h>
#include<stdlib.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int remaining_time;
};

int main() {
    int num_processes, i, time, remaining, count = 0, quantum;
    float avg_tat = 0, avg_wt = 0;
    
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    
    struct Process *processes = (struct Process*) malloc(num_processes * sizeof(struct Process));
    
    printf("Enter the arrival time and burst time of each process:\n");
    for(i = 0; i < num_processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);
    
    printf("\nGantt chart:\n");
    time = 0;
    while(count != num_processes) {
        remaining = -1;
        for(i = 0; i < num_processes; i++) {
            if(processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                if(remaining == -1 || processes[i].remaining_time > processes[remaining].remaining_time) {
                    remaining = i;
                }
            }
        }
        if(remaining == -1) {
            time++;
            continue;
        }
        printf("%d P%d ", time, processes[remaining].pid);
        if(processes[remaining].remaining_time > quantum) {
            time += quantum;
            processes[remaining].remaining_time -= quantum;
        } else {
            time += processes[remaining].remaining_time;
            processes[remaining].completion_time = time;
            processes[remaining].turnaround_time = processes[remaining].completion_time - processes[remaining].arrival_time;
            processes[remaining].waiting_time = processes[remaining].turnaround_time - processes[remaining].burst_time;
            avg_tat += processes[remaining].turnaround_time;
            avg_wt += processes[remaining].waiting_time;
            processes[remaining].remaining_time = 0;
            count++;
        }
    }
    
    printf("%d\n\n", time);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < num_processes; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("Average Turnaround Time: %.2f\n", avg_tat / num_processes);
    printf("Average Waiting Time: %.2f\n", avg_wt / num_processes);
    
    return 0;
}
