#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Define a struct for each process
struct Process {
    int processID;
    int burstTime;
    int responseTime;
    int priority;
    int arrivalTime;
};

// Define a comparison function for the min-heap based on priority
struct ComparePriority {
    bool operator()(Process const& p1, Process const& p2) {
        return p1.priority > p2.priority;
    }
};

int main() {
    // Define the processes
    vector<Process> processes = {
        {1, 10, 0, 1, 0},
        {2, 5, 0, 2, 2},
        {3, 8, 0, 3, 4},
        {4, 3, 0, 1, 5},
        {5, 6, 0, 2, 7}
    };
    
    // Define a min-heap for the processes based on priority
    priority_queue<Process, vector<Process>, ComparePriority> pq;
    
    // Insert the processes into the min-heap
    for (auto p : processes) {
        pq.push(p);
    }
    
    // Sort the processes based on arrival time using quicksort
    sort(processes.begin(), processes.end(), [](Process const& p1, Process const& p2) {
        return p1.arrivalTime < p2.arrivalTime;
    });
    
    // Define a variable to hold the current time
    int currentTime = 0;
    
    // Define a variable to hold the total response time
    int totalResponseTime = 0;
    
    // While there are still processes in the min-heap
    while (!pq.empty()) {
        // Get the next process in the heap
        Process p = pq.top();
        
        // Check if the process has arrived
        if (p.arrivalTime <= currentTime) {
            // Extract the process from the heap
            pq.pop();
            
            // Execute the process for a certain amount of time (here, the burst time is used)
            currentTime += p.burstTime;
            
            // Update the process's response time
            p.responseTime = currentTime - p.arrivalTime;
            totalResponseTime += p.responseTime;
            
            // Insert any other processes that have arrived since the last execution into the heap based on their priority
            for (auto q : processes) {
                if (q.arrivalTime > currentTime) {
                    break;
                }
                if (q.processID != p.processID) {
                    pq.push(q);
                }
            }
        } else {
            // If the process has not arrived yet, wait until it does
            currentTime = p.arrivalTime;
        }
    }
    
    // Calculate the average response time of all processes
    float avgResponseTime = (float)totalResponseTime / processes.size();
    
    // Output the result
    cout << "Average Response Time: " << avgResponseTime << endl;
    
    return 0;
}
