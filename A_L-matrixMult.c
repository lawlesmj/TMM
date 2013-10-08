/*-------------------------------------------------------------------------------

CS-450  Fall 2013

Programming Assignment #1: Matrix Multiplication using Multithreading

Written By: Team-Applegate_Lawless

1- Michael Lawless

2- Douglas Applegate

Submitted on: ?

-------------------------------------------------------------------------------*/

// includes
#include <stdio.h>          /* lets me play with files */
#include <stdlib.h>         /* adds useful system functions */
#include <pthread.h>        /* lets us play with threads */
                            //will need to complid with -lpthread
//Structures
//Matrix structure
typedef struct {
    uint rows;
    uint cols;
    int *array;
} matrix_t;

//thread param structure
typedef struct {
    uint row;
    uint col;
} pos_t;

//thread function prototype
void *matMult( void *param );
//File read function prototype
void matIntake(matrix_t * firstMat, matrix_t * secMat, String fileName);

int main(int argc, string argv[]) {
    matrix_t * matrix1;
    matrix_t * matrix2;
    matIntake(&matrix1, &matrix2);
    
}

void *matMult( void *param ) {
}

void matIntake(matrix_t * firstMat, matrix_t * secMat, String fileName){
    
    FILE *file = fopen(fileName, "r"); //say r as the second param because we only look to read the file
    
    if( file == NULL)
    {
        printf("There is no file by the name %s Closing program", fileName);
        return 1;
    }
   
    //loop1 while there is still info in the file
        //read first two numbers i and j
        //loop2 for i 
            //loop3 for j
                //store stuff in matrix struct
    //end loop 1
    
    //now should we read this a byte at a time or should we read them in as ints?
            
}
