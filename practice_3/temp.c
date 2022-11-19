#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

pthread_mutex_t lock;

#define width 7
#define height 6
#define hours 10

float heatMap[hours+1][width][height];


void delay(int ms){
    int delay = 1000 * ms;
 
    clock_t start_time = clock();
 
    while (clock() < start_time + delay);
}


void *readTemps(void* timeArg){
    int timeMs = *((int*) timeArg); 
    srand(time(NULL));

    int row = rand()%height;
    int col = rand()%width;
    char token;
    while(1){
        FILE* stream = fopen("heatMap.csv", "r");
        char line[1024];
        for(int i = 0; i <= row; i++){
            fgets(line, 1024, stream);
        }
     
        token = line[col*2];
        
        if(token == 'C'){
            heatMap[0][row][col] = rand()%61;
        }else{
            heatMap[0][row][col] = rand()%41 + 60;
        }
        delay(timeMs);

        bool valid = 0;
        while(!valid){
            int dir = rand()%4;
            switch (dir){
                case 0:
                    if(row-1 >= 0){
                        row--;
                        valid = 1;
                    }
                    break;
                case 1:
                    if(col+1 < width){
                        col++;
                        valid = 1;
                    }
                    break;
                case 2:
                    if(row+1 < height){
                        row++;
                        valid = 1;
                        }
                    break;
                case 3:
                    if(col-1 >= 0){
                        col--;
                        valid = 1;
                    }
                    break;
                default:
                    printf("failed");
                    break;
            }
        } 
    }
}

void* checkIfComplete(void* arg){
    bool check = 0;
    while(!check){
        check = 1;
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                if(heatMap[0][i][j] == -1){
                    check = 0;
                }
            }
        }
    }
}

void initMatrix(int h, int w, float matrix[width][height]){
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
        matrix[i][j] = -1;
        }
    }
}

void printMatrix(int h, int w, float matrix[width][height]){
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            printf("%3.0f", matrix[i][j]);
            if(j < w - 1)printf(",");
        }
        printf("\n");
    }
}

void finiteDiffCalculation(int threads){

    float gamma = 0.1;
    int i,j,k;
    for(k = 0; k < hours + 1; k++){
        #pragma omp parallel for collapse(2) num_threads(threads) private(i,j)
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j++){
                heatMap[k+1][i][j] = gamma * (heatMap[k][i+1][j] + heatMap[k][i-1][j] + heatMap[k][i][j+1] + heatMap[k][i][j-1] - 4 * heatMap[k][i][j]) + heatMap[k][i][j];
            }
        }
    }

}


int main(int argc, char* argv[]){
    int threadNum = atoi(argv[1]);

    pthread_t threads[threadNum + 1];
    int checkThreadCreation;
    if (pthread_mutex_init(&lock, NULL) != 0){
		printf("\n mutex init failed\n");
		return 1;
	}

    

    initMatrix(height,width,heatMap[0]);
    //printMatrix(height,width,heatMap[0]);
    int i = 0;
    int err;
    int delayMs = 100;
    while(i < threadNum) {
        err = pthread_create(&(threads[i]), NULL, &readTemps, &delayMs);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }
    err = pthread_create(&(threads[threadNum]), NULL, &checkIfComplete, NULL); //Master thread to check if the matrix has been completed
    if (err != 0)
        printf("\ncan't create thread :[%s]", strerror(err));
    pthread_join(threads[threadNum], NULL);
    i = 0;
    while(i < threadNum) {
        pthread_cancel(threads[i]);
        i++;
    }
    printf("Heat map when time  = 0 (initial conditions)\n");
    printMatrix(height,width,heatMap[0]);
    finiteDiffCalculation(threadNum);
    printf("Heat map when time  = 10 (final result)\n");
    printMatrix(height, width, heatMap[10]);
}