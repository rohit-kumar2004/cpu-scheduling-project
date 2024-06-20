# cpu-scheduling-project
This project implements and evaluates four CPU scheduling algorithms: First-Come, First-Served (FCFS), Shortest Job First (SJF), Shortest Remaining Time First (SRTF), and Round Robin (RR). The project aims to determine the optimal scheduling algorithm based on key performance metrics.
### Table of contents
* Introduction
* Features
* Installation
* steps of usage
* Theory


### Introduction
The project provides an implementation of four CPU scheduling algorithms and evaluates them based on average waiting time, average turnaround time, CPU utilization, and throughput. It determines the optimal algorithm for a given set of processes and displays the results. Each algorithm is designed to manage processes efficiently by prioritizing tasks based on arrival times and burst durations.

### Features
- Implementation of FCFS, SJF, SRTF, and RR scheduling algorithms
- Calculation of performance metrics for each algorithm
- Comparison of algorithms to determine the optimal one
- Display of the optimal algorithm and its performance metrics
### Installation
#### Prerequisites
- Visual Studio Code (VS Code) or any C++ IDE
- C++ compiler (e.g., GCC or MSVC)
### Steps of usage:
1. Open the project("main.cpp") file  in your IDE
2. Compile the C++ program
3. Input process data
 - Specify the number of processes.
- Enter the arrival time and burst time for each process.
- Enter the time quantum for the Round Robin algorithm.
4. View the results
  ### Theory
  My program implements and evaluates four fundamental CPU scheduling algorithms: FirstCome, First-Served (FCFS), Shortest Job First (SJF), Shortest Remaining Time First (SRTF), 
and Round Robin (RR). Each algorithm is designed to manage processes efficiently by 
prioritizing tasks based on arrival times and burst durations. The project collects 
user input, including process details and scheduling parameters. The implementation includes 
dedicated functions for each algorithm, computing key metrics such as average waiting time, 
average turnaround time, CPU utilization, and throughput. These metrics serve as 
benchmarks for comparing algorithm performance. The isBetter function facilitates this 
comparison by prioritizing algorithms based on metrics hierarchy: waiting time, turnaround 
time, CPU utilization, and throughput. Results are compiled into a comparison matrix, 
allowing for a systematic evaluation of each algorithm's effectiveness under varying 
workloads. The optimal algorithm is determined based on which achieves the best overall 
performance across these metrics.

  



