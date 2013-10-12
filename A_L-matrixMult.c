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
	matrix_t *leftMat;
	matrix_t *rightMat;
} pos_t;

//thread function prototype
void *matMult( void *param );
//File read function prototype
void matIntake(matrix_t * firstMat, matrix_t * secMat, char * fileName);

int main(int argc, string argv[]) {
	unsigned int i,j,k; // k is to manage the threads
	pos_t * params;
	matrix_t * leftMat;
	matrix_t * rightMat;
	pthread_t threads[];
	pthread_attr_t thread attrs[];
	
	
	matIntake(&leftMat, &rightMat);
	
	pthread_t threads[((leftMat -> rows) * (rightMat -> col))];
	pthread_attr_t thread attrs[((leftMat -> rows) * (rightMat -> col))];
	
	//we are going to need a thread for every cell of the matrix if I figured this right
	//print Matrices
	//Matrix 1 (left)
	printf("d% X d%", leftMat->row, leftMat->col);
	for(i = 0; i < leftMat -> row; i++;){
		for(j = 0; j < leftMat -> col; j++;){
			printf("[d%] ", MATRIX(leftMat,row,col));
		}
		printf("\n");
	}
	
	printf("\n");
	
	//rightMat
	printf("d% X d%", rightMat->row, rightMat->col);
	for(i = 0; i < rightMat -> row; i++;){
		for(j = 0; j < rightMat -> col; j++;){
			printf("[d%] ", MATRIX(rightMat,row,col));
		}
		printf("\n");
	}
	
	//allocate array of thread params
	params = (pos_t *) malloc(sizeof(pos_t) * leftMat->rows * rightMat->cols);
	
	if(params == NULL) {
		//bad things happened
		printf("Out of memory. Could not allocate thread param array.");
		//clean up
		free(leftMat);
		free(rightMat);
		exit(1);
	}
	
	//initializing attrs
	for(i = 0; i < ((leftMat -> rows) * (rightMat -> col)); i++){
		pthread_attr_init(&attrs[i]);
	}
	
	k=0;
	
	for(i=0; i < leftMat->rows; i++) {
		for(j=o; j < rightMat->cols; j++) {
			//make thread param in params array
			//why? I don't follow your logic.
			//run thread with param
		}
	}
	
	//wait for threads to complete
	//print output
}

void *matMult( void *param ) {
	// hey now that I'm thinkinh about this this just might be the thing the threads use
	//to multiply the matrix I think that it would be possible to set everything up in main
	// in a reasoable fashion.
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
		//clean up
		free(firstMat);
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
