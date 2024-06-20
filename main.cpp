#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <limits>
using namespace std;
void fcfsScheduling(vector<int>& arrivalTime, vector<int>& burstTime, vector<vector<double>> &results,bool check) {
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
    if(check){
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
   
    results[0]={avgWaitingTime,avgTurnaroundTime,cpuUtilization * 100,throughput};
}
void sjf_scheduling(vector<int> arrival_times, vector<int> burst_times, vector<int> process_ids,vector<vector<double>> &results,bool check) {
    int n = arrival_times.size();
    vector<int> completion_times(n, 0);
    vector<int> waiting_times(n, 0);
    vector<int> turnaround_times(n, 0);
    vector<int> response_times(n, 0);
    vector<int> start_times(n, -1);
    vector<bool> started(n, false);
    
    vector<int> remaining_processes(n);
    for (int i = 0; i < n; ++i) {
        remaining_processes[i] = i;
    }
    
    int current_time = 0;
    int completed = 0;
    double total_waiting_time = 0;
    double total_turnaround_time = 0;
    double total_response_time = 0;
    int total_burst_time = 0;
    
    while (completed < n) {
        vector<int> available_processes;
        for (int i : remaining_processes) {
            if (arrival_times[i] <= current_time && !started[i]) {
                available_processes.push_back(i);
            }
        }

        if (available_processes.empty()) {
            current_time++;
            continue;
        }

        auto shortest_job = min_element(available_processes.begin(), available_processes.end(), [&burst_times](int a, int b) {
            return burst_times[a] < burst_times[b];
        });

        int job_index = *shortest_job;
        start_times[job_index] = current_time;
        completion_times[job_index] = current_time + burst_times[job_index];
        waiting_times[job_index] = start_times[job_index] - arrival_times[job_index];
        turnaround_times[job_index] = completion_times[job_index] - arrival_times[job_index];
        response_times[job_index] = start_times[job_index] - arrival_times[job_index];
        started[job_index] = true;

        total_waiting_time += waiting_times[job_index];
        total_turnaround_time += turnaround_times[job_index];
        total_response_time += response_times[job_index];
        total_burst_time += burst_times[job_index];

        current_time = completion_times[job_index];
        completed++;
    }

    double avg_waiting_time = total_waiting_time / n;
    double avg_turnaround_time = total_turnaround_time / n;
    double avg_response_time = total_response_time / n;
    double throughput = static_cast<double>(n) / current_time;
    double cpu_utilization = (total_burst_time / static_cast<double>(current_time)) * 100;
    if(check){
        cout << "Process ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time | Response Time" << endl;
    for (int i = 0; i < n; ++i) {
        cout << setw(10) << process_ids[i] << " | "
             << setw(12) << arrival_times[i] << " | "
             << setw(10) << burst_times[i] << " | "
             << setw(15) << completion_times[i] << " | "
             << setw(12) << waiting_times[i] << " | "
             << setw(15) << turnaround_times[i] << " | "
             << setw(13) << response_times[i] << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    cout << "Average Response Time: " << avg_response_time << endl;
    cout << "Throughput: " << throughput << " processes/unit time" << endl;
    cout << "CPU Utilization: " << cpu_utilization << "%" << endl;
    }

   
     results[1]={avg_waiting_time,avg_turnaround_time,cpu_utilization,throughput};
}
void srtfScheduling(const vector<int>& arrivalTime, const vector<int>& burstTime,vector<vector<double>> &results,bool check) {
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
     if(check){
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
    
    results[2]={avgWaitingTime,avgTurnaroundTime,cpuUtilization * 100,throughput};

}
void roundRobinScheduling(vector<int>& arrivalTime, vector<int>& burstTime, int timeQuantum,vector<vector<double>> &results,bool check) {
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
    if(check){
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
   
    results[3]={avgWaitingTime,avgTurnaroundTime,cpuUtilization * 100,throughput};
}
    bool isBetter(vector<double> &result1, vector<double> &result2) {
    // Compare based on average waiting time
    if (result1[0] < result2[0]) {
        return true;
    } else if (result1[0] > result2[0]) {
        return false;
    }

    // If waiting times are equal, compare based on average turnaround time
    if (result1[1] < result2[1]) {
        return true;
    } else if (result1[1] > result2[1]) {
        return false;
    }

    // If turnaround times are equal, compare based on CPU utilization
    if (result1[3] > result2[3]) {
        return true;
    } else if (result1[3] < result2[3]) {
        return false;
    }

    // If all metrics are equal, return false (they are equivalent in performance)
    return false;
}
int main(){
int n, timeQuantum;
    cout << "Enter the number of processes: ";  cin >> n;
  vector<int> arrivalTime(n),burstTime(n);vector<int> process_ids = {1, 2, 3, 4};
   cout << "Enter arrival times and burst times for each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> arrivalTime[i];
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> burstTime[i];
    }
  cout << "Enter the time quantum in case if optimal algo is RR: ";  cin >> timeQuantum;
//   comparision matrix-->results
       vector<vector<double>> results(4, vector<double>(4));
      fcfsScheduling(arrivalTime, burstTime,results,false);
       sjf_scheduling(arrivalTime, burstTime, process_ids,results,false);
        srtfScheduling(arrivalTime, burstTime,results,false);
roundRobinScheduling(arrivalTime, burstTime, timeQuantum,results,false);
 int bestIndex = 0;
     // Compare each algorithm's results to find the best performing one
    for (int i = 1; i < 4; i++) {
        if (isBetter(results[i], results[bestIndex])) {
            bestIndex = i;
        }
    }
 // cout << "Best algorithm is at index: " << bestIndex << endl; 
    unordered_map<int,string>mp;
    mp[0]="FCFS";
    mp[1]="SJF";
    mp[2]="SRTF";
    mp[3]="RR";
    cout<<"best algorithm :  "<<mp[bestIndex];
    cout<<endl;
    // print best algorithm output
  switch(bestIndex){
  case 0: 
        fcfsScheduling(arrivalTime, burstTime,results,true);
        break;
  
  case 1:
       sjf_scheduling(arrivalTime, burstTime, process_ids,results,true);
       break;
  case 2:
       srtfScheduling(arrivalTime, burstTime,results,true);
       break;
 case 3:
       roundRobinScheduling(arrivalTime, burstTime, timeQuantum,results,true);
       break;

  }
return 0;
}
