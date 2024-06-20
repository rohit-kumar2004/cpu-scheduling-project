#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>

using namespace std;

void srtfScheduling(const vector<int>& arrivalTime, const vector<int>& burstTime) {
    int n = arrivalTime.size();
    vector<int> remainingTime = burstTime;
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> completionTime(n, 0);

    int currentTime = 0;
    int completed = 0;
    int shortest = 0;
    int minRemainingTime = numeric_limits<int>::max();
    bool foundProcess = false;

    while (completed != n) {
        // Find the process with the smallest remaining time at the current time
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0 && remainingTime[i] < minRemainingTime) {
                minRemainingTime = remainingTime[i];
                shortest = i;
                foundProcess = true;
            }
        }

        if (!foundProcess) {
            currentTime++;
            continue;
        }

        // Decrement the remaining time of the selected process
        remainingTime[shortest]--;
        minRemainingTime = remainingTime[shortest];

        if (minRemainingTime == 0) {
            minRemainingTime = numeric_limits<int>::max();
        }

        // If a process gets completely executed
        if (remainingTime[shortest] == 0) {
            completed++;
            foundProcess = false;
            int finishTime = currentTime + 1;
            completionTime[shortest] = finishTime;
            turnaroundTime[shortest] = finishTime - arrivalTime[shortest];
            waitingTime[shortest] = turnaroundTime[shortest] - burstTime[shortest];
        }

        currentTime++;
    }

    // Calculate CPU utilization and throughput
    double totalBurstTime = accumulate(burstTime.begin(), burstTime.end(), 0);
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
    int n;
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

    srtfScheduling(arrivalTime, burstTime);

    return 0;
}
