#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

void sjf_scheduling(vector<int> arrival_times, vector<int> burst_times, vector<int> process_ids) {
    int n = arrival_times.size();
    vector<int> completion_times(n, 0), waiting_times(n, 0),turnaround_times(n, 0);
   vector<int> response_times(n, 0),start_times(n, -1),remaining_processes(n);
    vector<bool> started(n, false);
    for (int i = 0; i < n; ++i) {
        remaining_processes[i] = i;
    }
    int current_time = 0, completed = 0,total_burst_time = 0;
     double total_waiting_time = 0,total_turnaround_time = 0,total_response_time = 0;;

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

int main() {
    vector<int> arrival_times = {0, 1, 2, 3};
    vector<int> burst_times = {5, 3, 8, 6};
    vector<int> process_ids = {1, 2, 3, 4};

    sjf_scheduling(arrival_times, burst_times, process_ids);

    return 0;
}
