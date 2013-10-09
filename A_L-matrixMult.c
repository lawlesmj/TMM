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
                            
//A macro to emulate a 2d array. Works just like matrix[row][col].
#define MATRIX(matrix, row, col) matrix->array[row + col * matrix->rows]

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
void matIntake(matrix_t * firstMat, matrix_t * secMat, char * fileName);

int main(int argc, string argv[]) {
	matrix_t * matrix1;
	matrix_t * matrix2;
	matIntake(&matrix1, &matrix2);
	//stuff
}

void *matMult( void *param ) {
}

void matIntake(matrix_t * firstMat, matrix_t * secMat, char * fileName){
	unsigned int i,j;
	FILE *file = fopen(fileName, "r"); //say r as the second param because we only look to read the file
	
	if( file == NULL)
	{
		printf("There is no file by the name %s Closing program", fileName);
		return 1;
	}
	
	//read first two numbers rows and cols for first matrix
	firstMat->rows = fscanf(file, "u");
	firstMat->cols = fscanf(file, "u");
	
	//create array for matrix data
	firstMat->array = (int*) malloc(sizeof(int) * firstMat->rows * firstMat->cols);
	
	if(firstMat->array == NULL) {
		//bad shit happened
		printf("Out of memory. Could not allocate Matrix.");
		exit(1);
	}
	
	//loop1 for rows
	for(i=0; i < firstMat->rows; i++) {
	//loop2 for cols
		for(j=0; j < firstMat->cols; j++) {
			//store stuff in matrix struct
			MATRIX(firstMat, i, j) = fscanf(file, "i");
		}
	}
	
	//read two numbers rows and cols for second matrix
	secMat->rows = fscanf(file, "u");
	secMat->cols = fscanf(file, "u");
	
	//create array for matrix data
	secMat->array = (int*) malloc(sizeof(int) * secMat->rows * secMat->cols);
	
	if(secMat->array == NULL) {
		//bad shit happened
		printf("Out of memory. Could not allocate Matrix.");
		exit(1); 
	}
	
	//loop1 for rows
	for(i=0; i < secMat->rows; i++) {
		//loop2 for cols
		for(j=0; j < secMat->cols; j++) {
			//store stuff in matrix struct
			MATRIX(secMat, i, j) = fscanf(file, "i");
		}
	}
}
