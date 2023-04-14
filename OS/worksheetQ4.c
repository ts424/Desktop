#include <stdio.h>

#define MAX_PROCESS 10

int main() {
    int num_process, i, j, min_priority, min_priority_index;
    int process_id[MAX_PROCESS], burst_time[MAX_PROCESS], priority[MAX_PROCESS], waiting_time[MAX_PROCESS], turnaround_time[MAX_PROCESS];

    // Accept the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &num_process);

    // Accept the burst time and priority for each process
    for (i = 0; i < num_process; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);

        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &priority[i]);

        process_id[i] = i + 1;
    }

    // Sort the processes based on priority
    for (i = 0; i < num_process - 1; i++) {
        min_priority = priority[i];
        min_priority_index = i;
        for (j = i + 1; j < num_process; j++) {
            if (priority[j] < min_priority) {
                min_priority = priority[j];
                min_priority_index = j;
            }
        }
        int temp_burst_time = burst_time[i];
        burst_time[i] = burst_time[min_priority_index];
        burst_time[min_priority_index] = temp_burst_time;

        int temp_priority = priority[i];
        priority[i] = priority[min_priority_index];
        priority[min_priority_index] = temp_priority;

        int temp_process_id = process_id[i];
        process_id[i] = process_id[min_priority_index];
        process_id[min_priority_index] = temp_process_id;
    }

    // Calculate waiting time and turnaround time for each process
    waiting_time[0] = 0;
    turnaround_time[0] = burst_time[0];

    for (i = 1; i < num_process; i++) {
        waiting_time[i] = waiting_time[i-1] + burst_time[i-1];
        turnaround_time[i] = waiting_time[i] + burst_time[i];
    }

    // Calculate the average waiting time and average turnaround time
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (i = 0; i < num_process; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }

    avg_waiting_time /= num_process;
    avg_turnaround_time /= num_process;

    // Display the results
    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < num_process; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process_id[i], burst_time[i], priority[i], waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time = %.2f", avg_turnaround_time);

    return 0;
}
