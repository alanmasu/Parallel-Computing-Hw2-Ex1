# Introduction to parallel computing - Homework 2 - Exercise 1
## Compiling and running whit an interactive session
Request for an interactive session with the following command:
```bash
qsub -I -q short_cpuQ
```
So, after cloning the repository and open it, you can compile and run the program using the following scripts:
 - `doStrongScaling.sh` for strong scaling
 - `doWeakScaling.sh` for weak scaling
 - `testParallelism.sh` for see the difference performance between the serial and the parallel version of the program

>At the end they will create also the graphs of the results (See [results](#results) for more information).

For test correctness of the program you can use the following script:
 - `debugScript.sh` for see the correctness of the program
  
There are also some scripts for get the graphs of the results:
 - `pytonStrongScalingCharts.sh` for strong scaling
 - `pytonWeakScalingCharts.sh` for weak scaling
 - `pytonCharts.sh` for the parallelism test 

## How to submit the job with PBS
For submitting the job whit the scheduler I have created some others script for the specific goal:
 - `doStrongScaling.pbs` for strong scaling
 - `doWeakScaling.pbs` for weak scaling
 - `testParallelism.pbs` for the parallelism test

>At the end they will create also the graphs of the results. (See [results](#results) for more information).

## Results 
The results of the tests are in the folder `results` and each run can create a folder whit the results of the run. The name of the folder is the date and the time of the run. In each folder there are the results of the run and the graphs of the results. The graphs are in the format `png` and the resoults in `csv`.

