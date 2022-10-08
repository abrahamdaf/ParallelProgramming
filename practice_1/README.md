# Pi Calculation

Aproximation of the number pi through the Montecarlo method

n = 10000 points

To compile: gcc pi\_calculation.c -o pi\_calculation -lpthread

To execute ./pi\_calculation \<Number of threads\>

An argument is required to run the program.

<img src="https://github.com/abrahamdaf/parallel-programming-ITESM/blob/main/practice_1/screenshots/runtime%20graph.png" width="600">

Average runtime for 6 samples with 1, 2, 4, 8 & 16 threads

<img src="https://github.com/abrahamdaf/parallel-programming-ITESM/blob/main/practice_1/screenshots/htop%20ss.png" width="600">

CPU usage graph and process list to show the different threads of the running program (In this case the value of n = 10,000,000 and the number of threads was set to 4000 for it to be visible in the htop window)

## Conclusions

Threads can be used to enable parallel execution in a program, dividing a complex task into several independent subprocesses. In this practice, the total amount of points (n) to be counted was divided over the number of threads received as an argument and then each supbrocess "did its own part" parallel to other subprocesses.

Mutex was used to reserve the global variable to count the number of points inside of the circle to a single thread while other were still counting the points inside of the circle.

As it can be seen in the screen shots, the processes are running in parallel, dividing the total sum to be done into smaller segments that the different threads are able to complete. It was expected to see the total time to run the code decrease by dividing it into easier tasks, but as shown in the first screen shot, the total time increased with the total thread number.
