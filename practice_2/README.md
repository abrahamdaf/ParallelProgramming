
# Parallel Matrix Multiplication

Matrix Multiplication using OpenMP

Matrix sizes = N x N; N = 700

To compile: gcc MatMult.c -o MatMult -fopenmp

To execute ./MatMult \<Number of threads\>

An argument is required to run the program.

<img src="https://github.com/abrahamdaf/parallel-programming-ITESM/blob/main/practice_2/screenshots/running_time.png?raw=true" width="600">

Runtimes when running with 1,2,4,8,16,100 threads

<img src="https://github.com/abrahamdaf/parallel-programming-ITESM/blob/main/practice_2/screenshots/htop.png?raw=true" width="600">

CPU usage graph and process list to show the different threads of the running program

## Conclusions

OpenMP is a quick and easy solution that allows to parallelize processes without directly using the lpthreads library, leading to a simpler implementation.
The previous graph demonstrates the drop in runtime when the number of threads is increased, although there is a limit after which the increment in the number of threads is counterproductive to the processing time.
