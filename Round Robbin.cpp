#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

// Function to calculate Round Robin scheduling
void roundRobinScheduling(vector<int>& arrivalTime, vector<int>& burstTime, int timeQuantum) {
    int n = arrivalTime.size();
    vector<int> remainingTime = burstTime;
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> completionTime(n, 0);
    
    queue<int> processQueue;
    int currentTime = 0;
    int completed = 0;

    // Enqueue processes as they arrive
    int index = 0;
    while (completed != n) {
        while (index < n && arrivalTime[index] <= currentTime) {
            processQueue.push(index);
            index++;
        }

        if (processQueue.empty()) {
            currentTime++;
            continue;
        }

        int currentProcess = processQueue.front();
        processQueue.pop();

        int timeToRun = min(timeQuantum, remainingTime[currentProcess]);
        currentTime += timeToRun;
        remainingTime[currentProcess] -= timeToRun;

        while (index < n && arrivalTime[index] <= currentTime) {
            processQueue.push(index);
            index++;
        }

        if (remainingTime[currentProcess] > 0) {
            processQueue.push(currentProcess);
        } else {
            completed++;
            completionTime[currentProcess] = currentTime;
            turnaroundTime[currentProcess] = completionTime[currentProcess] - arrivalTime[currentProcess];
            waitingTime[currentProcess] = turnaroundTime[currentProcess] - burstTime[currentProcess];
        }
    }

    // Calculate CPU utilization and throughput
    int totalBurstTime = accumulate(burstTime.begin(), burstTime.end(), 0);
    double cpuUtilization = (double) totalBurstTime / currentTime;
    double throughput = (double) n / currentTime;

    // Calculate average waiting time and average turnaround time
    double totalWaitingTime = accumulate(waitingTime.begin(), waitingTime.end(), 0);
    double totalTurnaroundTime = accumulate(turnaroundTime.begin(), turnaroundTime.end(), 0);
    double avgWaitingTime = totalWaitingTime / n;
    double avgTurnaroundTime = totalTurnaroundTime / n;

    // Display results
    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" 
             << waitingTime[i] << "\t\t" << turnaroundTime[i] << endl;
    }
    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "CPU Utilization: " << cpuUtilization * 100 << "%" << endl;
    cout << "Throughput: " << throughput << " processes per unit time" << endl;
}

int main() {
    int n, timeQuantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> arrivalTime(n);
    vector<int> burstTime(n);

    cout << "Enter arrival times and burst times for each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> arrivalTime[i];
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> burstTime[i];
    }

    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    roundRobinScheduling(arrivalTime, burstTime, timeQuantum);

    return 0;
}
