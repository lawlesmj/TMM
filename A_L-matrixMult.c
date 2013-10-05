/*-------------------------------------------------------------------------------

CS-450  Fall 2013

Programming Assignment #1: Matrix Multiplication using Multithreading

Written By: Team-Applegate_Lawless

1- Michael Lawless

2- Douglas Applegate

Submitted on: ?

-------------------------------------------------------------------------------*/

// includes
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fstream>          /* makes file input a thing*/

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

void matIntake()
