#include <stdio.h>

int main() {
    int n, i;
    float awt = 0, att = 0;
    int btime[20], wtime[20], ttime[20];

    printf("Enter the total number of processes to be executed.");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter the burst time for process %d: ", i+1);
        scanf("%d", &btime[i]);
    }

    
    wtime[0] = 0;
    for(i = 1; i < n; i++) {
        wtime[i] = wtime[i-1] + btime[i-1];
    }

    // Calculate turnaround time for each process
    printf("GANTT CHART \n");
    printf("----------------------------------------\n");
    printf("0 | ");
    for(i = 0; i < n; i++) {
        ttime[i] = wtime[i] + btime[i];
        printf("P%d | %d | ",i+1,ttime[i]);
    }
    printf("\n----------------------------------------");

    // Calculate average waiting time and average turnaround time
    for(i = 0; i < n; i++) {
        awt = awt + wtime[i];
        att = att + ttime[i];
    }
    awt = awt/n;
    att = att/n;

    // Print the results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t\t\t%d\t\t\t%d\t\t\t\t%d\n", i+1, btime[i], wtime[i], ttime[i]);
    }
    printf("\nAverage waiting time: %.2f\n", awt);
    printf("Average turnaround time: %.2f\n", att);

    return 0;
}
