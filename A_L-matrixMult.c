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

int main(int argc, string argv[]) {
    
}

void *matMult( void *param ) {
}

void matIntake(){
    //create matrix struct
    //loop1 while there is still info in the file
        //read first two numbers i and j
        //loop2 for i 
            //loop3 for j
                //store stuff in matrix struct
    //end loop 1
    
    //now should we read this a byte at a time or should we read them in as ints?
            
}
