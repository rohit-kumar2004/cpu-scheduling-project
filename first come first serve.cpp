#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Function to calculate FCFS scheduling
void fcfsScheduling(vector<int>& arrivalTime, vector<int>& burstTime) {
    int n = arrivalTime.size();
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> completionTime(n, 0);

    // Calculate waiting times and turnaround times
    completionTime[0] = burstTime[0];
    for (int i = 1; i < n; i++) {
        completionTime[i] = completionTime[i - 1] + burstTime[i];
    }

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = completionTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
    }

    // Calculate average waiting time and average turnaround time
    double totalWaitingTime = accumulate(waitingTime.begin(), waitingTime.end(), 0);
    double totalTurnaroundTime = accumulate(turnaroundTime.begin(), turnaroundTime.end(), 0);
    double avgWaitingTime = totalWaitingTime / n;
    double avgTurnaroundTime = totalTurnaroundTime / n;

    // Calculate CPU utilization and throughput
    double cpuUtilization = (double) accumulate(burstTime.begin(), burstTime.end(), 0) / completionTime.back();
    double throughput = (double) n / completionTime.back();

    // Display results
    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" 
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

    fcfsScheduling(arrivalTime, burstTime);

    return 0;
}
