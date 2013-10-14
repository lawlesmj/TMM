/*-------------------------------------------------------------------------------

CS-450  Fall 2013

Programming Assignment #1: Matrix Multiplication using Multithreading

Written By: Team-Applegate_Lawless

1- Michael Lawless

2- Douglas Applegate

Submitted on: 10/14/2013

-------------------------------------------------------------------------------*/

// includes
#include <stdio.h>          /* lets me play with files */
#include <stdlib.h>         /* adds useful system functions */
#include <pthread.h>        /* lets us play with threads */
                            //will need to complid with -lpthread
                            
//A macro to emulate a 2d array. Works just like matrix[row][col].
#define MATRIX(matrix, row, col) matrix->array[row + col * matrix->height]

//Structures
//Matrix structure
typedef struct {
	uint height;
	uint width;
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

//mutex! for good measure
pthread_mutex_t deadBolt;

//globals
matrix_t * leftMat;
matrix_t * rightMat;
matrix_t * resultMat;

int main(int argc, char * argv[]) {
	unsigned int i,j,k; // k is to manage the threads
	pos_t * params;
	pthreads_t * threads;
	FILE * output;
	
	//init mutex
	if (pthread_mutex_init(&deadBolt, NULL) != 0){
		printf("Mutex intialization has failed");
		exit(1);
	}
	
	//read in input file
	matIntake(leftMat, rightMat, "input.dat");
	
	//prep result matrix
	resultMat->row = leftMat->row;
	resultMat->col = rightMat->col;
	
	resultMat->array = (int*) malloc(sizeof(int) * (resultMat -> height) * (resultMat -> col));
	
	if(resultMat->array == NULL) {
		//bad things happened
		printf("Out of memory. Could not allocate result array.");
		//clean up
		free(leftMat);
		free(rightMat);
		exit(1);
	}
	
	//we are going to need a thread for every cell of the matrix
	threads = (pthreads_t *) malloc(sizeof(pthreads_t) * (resultMat -> height) * (resultMat -> col));
	
	if(threads == NULL) {
		//bad things happened
		printf("Out of memory. Could not allocate threads array.");
		//clean up
		free(leftMat);
		free(rightMat);
		free(resultMat);
		exit(1);
	}
	
	//allocate array of thread params
	params = (pos_t *) malloc(sizeof(pos_t) * leftMat->height * rightMat->width);
	
	if(params == NULL) {
		//bad things happened
		printf("Out of memory. Could not allocate thread param array.");
		//clean up
		free(leftMat);
		free(rightMat);
		free(resultMat);
		free(threads);
		exit(1);
	}
	
	//open output file
	output = fopen("output.dat", "w");
	
	if( output == NULL)
	{
		printf("There is no file by the name %s Closing program", "output.dat");
		//clean up
		free(leftMat);
		free(rightMat);
		free(resultMat);
		free(threads);
		free(params);
		exit(1);
	}
	
	//print Matrices
	//Matrix 1 (left)
	printf("A[d%][d%] = {\n ", leftMat->height, leftMat->width);
	fprintf(output, "A[d%][d%] = {\n ", leftMat->height, leftMat->width);
	for(i = 0; i < leftMat -> height; i++;){
		for(j = 0; j < leftMat -> width; j++;){
			printf("\td%", MATRIX(leftMat,i,j));
			fprintf(output, "\td%", MATRIX(leftMat,i,j));
		}
		printf("\n");
		fprintf(output, "\n");
	}
	printf("}\n\n");
	fprintf(output, "}\n\n");
	
	//rightMat
	printf("B[d%][d%] = {\n ", rightMat->height, rightMat->width);
	fprintf(output, "B[d%][d%] = {\n ", rightMat->height, rightMat->width);
	for(i = 0; i < rightMat -> height; i++;){
		for(j = 0; j < rightMat -> width; j++;){
			printf("\td%", MATRIX(rightMat,i,j));
			fprintf(output, "\td%", MATRIX(rightMat,i,j));
		}
		printf("\n");
		fprintf(output, "\n");
	}
	printf("}\n\n");
	fprintf(output, "}\n\n");
	
	//create the threads
	for(i=0; i < leftMat->height; i++) {
		for(j=0; j < rightMat->width; j++) {
			MATRIX(params, i, j)->row = i;
			MATRIX(params, i, j)->col = j;
			pthread_create(MATRIX(threads, i, j) ,NULL, &matMult, MATRIX(params, i, j));
		}
	}
	
	//wait for each thread to complete
	for(i=0; i < leftMat->height; i++) {
		for(j=0; j < rightMat->width; j++) {
			pthread_join(MATRIX(threads, i, j), NULL);
		}
	}
	
	printf("### ALL threads have terminated\n\n");
	
	//result matrix
	printf("C[d%][d%] = {\n ", resultMat->height, resultMat->width);
	fprintf(output, "C[d%][d%] = {\n ", resultMat->height, resultMat->width);
	for(i = 0; i < resultMat -> height; i++;){
		for(j = 0; j < resultMat -> width; j++;){
			printf("\td%", MATRIX(resultMat,i,j));
			fprintf(output, "\td%", MATRIX(resultMat,i,j));
		}
		printf("\n");
		fprintf(output, "\n");
	}
	printf("}\n");
	fprintf(output, "}\n");
	
	//clean up at the end
	free(leftMat);
	free(rightMat);
	free(resultMat);
	free(threads);
	free(params);
	
	fclose(output);
}

void *matMult( void *param ) {
	// hey now that I'm thinkinh about this this just might be the thing the threads use
	//to multiply the matrix I think that it would be possible to set everything up in main
	// in a reasonable fashion.
	unsigned int i;
	int result = 0;
	pos_t *pos = (pos_t *) param;
	
	//sum when multiply left's row by right's col
	for(i=0; i < leftMat->width; i++) {
        result += MATRIX(leftMat->array, pos->row, i) * MATRIX(rightMat->array, i, pos->col);
	}
	pthread_mutex_lock(&deadBolt);
	MATRIX(resultMat, pos->row, pos->col);
	pthread_mutex_unlock(&deadBolt);
}

void matIntake(matrix_t * firstMat, matrix_t * secMat, char * fileName){
	unsigned int i,j;
	FILE *file = fopen(fileName, "r"); //say r as the second param because we only look to read the file
	
	if( file == NULL)
	{
		printf("There is no file by the name %s Closing program", fileName);
		return 1;
	}
	
	//read first two numbers height and width for first matrix
	firstMat->height = fscanf(file, "u");
	firstMat->width = fscanf(file, "u");
	
	//create array for matrix data
	firstMat->array = (int*) malloc(sizeof(int) * firstMat->height * firstMat->width);
	
	if(firstMat->array == NULL) {
		//bad shit happened
		printf("Out of memory. Could not allocate Matrix.");
		exit(1);
	}
	
	//loop1 for height
	for(i=0; i < firstMat->height; i++) {
	//loop2 for width
		for(j=0; j < firstMat->width; j++) {
			//store stuff in matrix struct
			MATRIX(firstMat, i, j) = fscanf(file, "i");
		}
	}
	
	//read two numbers height and width for second matrix
	secMat->height = fscanf(file, "u");
	secMat->width = fscanf(file, "u");
	
	//create array for matrix data
	secMat->array = (int*) malloc(sizeof(int) * secMat->height * secMat->width);
	
	if(secMat->array == NULL) {
		//bad stuff happened
		printf("Out of memory. Could not allocate Matrix.");
		//clean up
		free(firstMat);
		exit(1); 
	}
	
	//loop1 for height
	for(i=0; i < secMat->height; i++) {
		//loop2 for width
		for(j=0; j < secMat->width; j++) {
			//store stuff in matrix struct
			MATRIX(secMat, i, j) = fscanf(file, "i");
		}
	}
	//close file
	fclose(file);
}
