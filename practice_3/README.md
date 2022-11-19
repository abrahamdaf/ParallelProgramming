
# Heat Calculation

Heat calculation using finite difference method

To compile: gcc temp.c -o temp -lpthread -fopenmp

To execute ./temp \<Number of threads\>

An argument is required to run the program.

<img src="https://github.com/abrahamdaf/parallel-programming-ITESM/blob/main/practice_3/visualResources/Execution%20time.png" width="600">

Runtimes when running with 1,2,4,8,16,100 threads

<img src="https://github.com/abrahamdaf/parallel-programming-ITESM/blob/main/practice_3/visualResources/CPU%20usage%20graph.png" width="600">

CPU usage graph and process list when using 100 threads

## Conclusions

To solve this problem both the use of OpenMP and pthreads were needed. While OpenMP allows for an easier implementation of parallel computing, pthreads by itself can be better for a lower level implementation. In this case, pthread was used to simulate a defined number of sensors as threads moving along a plane and to simulate a master node to check if all the cells have been fulfilled. Since the heat calculation did not require a specific behaviour for individual threads, OpenMP was the best of the 2 alternatives given.
