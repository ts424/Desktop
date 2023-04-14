#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    int waiting_time[20], turnaround_time[20], burst_time[20];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter the burst time for process %d: ", i+1);
        scanf("%d", &burst_time[i]);
    }

    // sorting burst time in ascending order
    int temp;
    for(i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(burst_time[i] > burst_time[j]) {
                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;
            }
        }
    }

    waiting_time[0] = 0;
    for(i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i-1] + burst_time[i-1];
    }

    for(i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + burst_time[i];
        printf("P%d | %d | ",i+1,turnaround_time[i]);
    }

    for(i = 0; i < n; i++) {
        avg_waiting_time = avg_waiting_time + waiting_time[i];
        avg_turnaround_time = avg_turnaround_time + turnaround_time[i];
    }
    avg_waiting_time = avg_waiting_time/n;
    avg_turnaround_time = avg_turnaround_time/n;

    printf("\nProcess      \tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("Process ID %d\t\t\t%d\t\t\t%d\t\t\t\t%d\n", i+1, burst_time[i], waiting_time[i], turnaround_time[i]);
    }
    
    
    printf("\nAverage waiting time: %.2f\n", avg_waiting_time);
    printf("Average turnaround time: %.2f\n", avg_turnaround_time);

    return 0;
}
