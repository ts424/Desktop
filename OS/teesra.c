#include<stdio.h>

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int burst_time[], int waiting_time[], int arrival_time[])
{
    int remaining_time[n];
    for(int i=0;i<n;i++){
        remaining_time[i]=burst_time[i];
    }

    int complete = 0;
    int time = 0;
    int highest_response_ratio_process_index;
    int max_response_ratio;
    int waiting_time_sum=0;

    // Loop until all processes are completed
    while (complete != n) {

        max_response_ratio = -99999; //initialize with a very small value

        // Find process with highest response ratio
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= time && remaining_time[i] > 0) {
                int response_ratio = 1 + (time - arrival_time[i] + remaining_time[i]) / remaining_time[i];
                if (response_ratio > max_response_ratio) {
                    max_response_ratio = response_ratio;
                    highest_response_ratio_process_index = i;
                }
            }
        }

        // Reduce remaining time of the process
        remaining_time[highest_response_ratio_process_index]--;

        // If process is completed
        if (remaining_time[highest_response_ratio_process_index] == 0) {

            // Increment complete
            complete++;

            // Calculate waiting time and add to sum
            waiting_time[highest_response_ratio_process_index] = time - arrival_time[highest_response_ratio_process_index] - burst_time[highest_response_ratio_process_index];
            waiting_time_sum+=waiting_time[highest_response_ratio_process_index];
        }
        // Increment time
        time++;
    }
    printf("Average Waiting Time: %f\n",(float)waiting_time_sum/n); //Prints the average waiting time
}

// Function to find turn around time for all processes
void findTurnAroundTime(int processes[], int n, int burst_time[], int waiting_time[], int turn_around_time[])
{
    // Calculate turn around time using waiting time and burst time
    for (int i = 0; i < n; i++) {
        turn_around_time[i] = burst_time[i] + waiting_time[i];
    }

    int turn_around_time_sum=0;
    for(int i=0;i<n;i++){
        turn_around_time_sum+=turn_around_time[i];
    }
    printf("Average Turn Around Time: %f\n",(float)turn_around_time_sum/n); //Prints the average turn around time
}

int main()
{
    int n; //Number of processes
    printf("Enter the number of processes: ");
    scanf("%d",&n);

    int processes[n];
    int burst_time[n];
    int arrival_time[n];
    int waiting_time[n];
    int turn_around_time[n];

    //Input process details
    printf("Enter the process details:\n");
    for(int i=0;i<n;i++){
        printf("Enter arrival time and burst time for process %d: ",i+1);
        scanf("%d %d",&arrival_time[i],&burst_time[i]);
        processes[i]=i+1; //Assigns process ID
    }

    findWaitingTime(processes, n, burst_time, waiting_time, arrival_time);
    findTurnAroundTime(processes, n, burst_time, waiting_time, turn_around_time);

    return 0;
}
