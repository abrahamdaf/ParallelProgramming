#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 700
void multMatrix( int rows1, int cols1, int rows2, int cols2, int mat1[rows1][cols1], int mat2[rows2][cols2], int sol[rows1][cols2], int threads){
    int i, j;
    #pragma omp parallel for collapse(2) num_threads(threads) private(i,j)
    for(i = 0; i < rows1; i++){
        for(j = 0; j < cols2; j++){
            sol[i][j] = 0;
            for(int elements = 0; elements < cols1; elements++){
                sol[i][j] += mat1[i][elements] * mat2[elements][j];                
            }
        }
    }
}

void printMatrix(int rows, int cols, int mat[rows][cols]){

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }

}

void fillMatrix(int rows, int cols, int mat[rows][cols]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            mat[i][j] = 2;
        }
    }
}


int main(int argc, char* argv[]){
    int threadNum = atoi(argv[1]);
    /*int mat1[2][3] = {{1,2,3},{4,5,6}};
    int mat2[3][2] = {{7,8},{9,10},{11,12}};
    int sol[3][3];
    multMatrix(2,3,3,2,mat1,mat2,sol,threadNum);
    printMatrix(2,2,sol);*/


    int mat1[N][N];
    int mat2[N][N];
    fillMatrix(N,N,mat1);
    fillMatrix(N,N,mat2);
    const int rows1 = sizeof(mat1)/sizeof(mat1[0]);
    const int cols1 = sizeof(mat1[0])/sizeof(mat1[0][0]);
    const int rows2 = sizeof(mat2)/sizeof(mat2[0]);
    const int cols2 = sizeof(mat2[0])/sizeof(mat2[0][0]);
    if(cols1 == rows2){
        int sol[rows1][cols2];
        multMatrix(rows1,cols1,rows2,cols2,mat1,mat2,sol,threadNum);
        //printMatrix(rows1,cols2,sol);
    }
    else{
        printf("Multiplications are not possible with given dimensions\n");
    }
}
