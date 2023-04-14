#include <stdio.h>

#define MAX_PROCESS 10

int main() {
    int num_process, time_slice, i, j, time = 0, completed = 0;
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    int burst_time[MAX_PROCESS], remaining_time[MAX_PROCESS], waiting_time[MAX_PROCESS], turnaround_time[MAX_PROCESS], id[MAX_PROCESS];

    // Accept the number of processes and time quantum
    printf("Enter the number of processes: ");
    scanf("%d", &num_process);

    printf("Enter the time quantum: ");
    scanf("%d", &time_slice);

    // Accept the burst time for each process
    for (i = 0; i < num_process; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);

        id[i] = i + 1;
        remaining_time[i] = burst_time[i];
    }

    // Implement Round Robin algorithm
    while (completed != num_process) {
        for (i = 0; i < num_process; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] <= time_slice) {
                    time += remaining_time[i];
                    remaining_time[i] = 0;
                    completed++;
                }
                else {
                    time += time_slice;
                    remaining_time[i] -= time_slice;
                }

                for (j = 0; j < num_process; j++) {
                    if (j != i && remaining_time[j] > 0) {
                        waiting_time[j] += time_slice;
                    }
                }
            }
        }
    }

    // Calculate waiting time and turnaround time for each process
    for (i = 0; i < num_process; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }

    // Calculate the average waiting time and average turnaround time
    avg_waiting_time /= num_process;
    avg_turnaround_time /= num_process;

    // Display the results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < num_process; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", id[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time = %.2f", avg_turnaround_time);

    return 0;
}
