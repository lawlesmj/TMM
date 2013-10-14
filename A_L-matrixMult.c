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
#define PMATRIX(matrix, row, col) matrix->array[row + col * matrix->height]
#define MATRIX(matrix, row, col) matrix.array[row + col * matrix.height]

//Structures
//Matrix structure
typedef struct {
	unsigned int height;
	unsigned int width;
	int *array;
} matrix_t;

//thread param structure
typedef struct {
	unsigned int row;
	unsigned int col;
} pos_t;

//thread function prototype
void *matMult( void *param );
//File read function prototype
void matIntake(matrix_t * firstMat, matrix_t * secMat, char * fileName);

//mutex! for good measure
pthread_mutex_t deadBolt;

//globals
matrix_t leftMat;
matrix_t rightMat;
matrix_t resultMat;

int main(int argc, char * argv[]) {
	unsigned int i,j;
	pos_t * params;
	pthread_t * threads;
	FILE * output;
	
	//init mutex
	if (pthread_mutex_init(&deadBolt, NULL) != 0){
		printf("Mutex intialization has failed\n");
		exit(1);
	}
	
	//read in input file
	matIntake(&leftMat, &rightMat, "input.dat");
	
	//prep result matrix
	resultMat.height = leftMat.height;
	resultMat.width = rightMat.width;
	
	resultMat.array = (int*) malloc(sizeof(int) * (resultMat.height) * (resultMat.width));
	
	if(resultMat.array == NULL) {
		//bad things happened
		printf("Out of memory. Could not allocate result array.\n");
		//clean up
		free(leftMat.array);
		free(rightMat.array);
		exit(1);
	}
	
	//we are going to need a thread for every cell of the matrix
	threads = (pthread_t *) malloc(sizeof(pthread_t) * (resultMat . height) * (resultMat . width));
	
	if(threads == NULL) {
		//bad things happened
		printf("Out of memory. Could not allocate threads array.\n");
		//clean up
		free(leftMat.array);
		free(rightMat.array);
		free(resultMat.array);
		exit(1);
	}
	
	//allocate array of thread params
	params = (pos_t *) malloc(sizeof(pos_t) * leftMat.height * rightMat.width);
	
	if(params == NULL) {
		//bad things happened
		printf("Out of memory. Could not allocate thread param array.\n");
		//clean up
		free(leftMat.array);
		free(rightMat.array);
		free(resultMat.array);
		free(threads);
		exit(1);
	}
	
	//open output file
	output = fopen("output.dat", "w");
	
	if( output == NULL)
	{
		printf("There is no file by the name %s Closing program\n", "output.dat");
		//clean up
		free(leftMat.array);
		free(rightMat.array);
		free(resultMat.array);
		free(threads);
		free(params);
		exit(1);
	}
	
	//print Matrices
	//Matrix 1 (left)
	printf("A[%d][%d] = {\n ", leftMat.height, leftMat.width);
	fprintf(output, "A[%d][%d] = {\n ", leftMat.height, leftMat.width);
	for(i = 0; i < leftMat . height; i++) {
		for(j = 0; j < leftMat . width; j++){
			printf("\t%d", MATRIX(leftMat,i,j));
			fprintf(output, "\t%d", MATRIX(leftMat,i,j));
		}
		printf("\n");
		fprintf(output, "\n");
	}
	printf("}\n\n");
	fprintf(output, "}\n\n");
	
	//print Matrices
	//Matrix 1 (right)
	printf("B[%d][%d] = {\n ", rightMat.height, rightMat.width);
	fprintf(output, "B[%d][%d] = {\n ", rightMat.height, rightMat.width);
	for(i = 0; i < rightMat . height; i++) {
		for(j = 0; j < rightMat . width; j++){
			printf("\t%d", MATRIX(rightMat,i,j));
			fprintf(output, "\t%d", MATRIX(rightMat,i,j));
		}
		printf("\n");
		fprintf(output, "\n");
	}
	printf("}\n\n");
	fprintf(output, "}\n\n");
	
	//create the threads
	for(i=0; i < leftMat.height; i++) {
		for(j=0; j < rightMat.width; j++) {
			params[i + j * resultMat.height].row = i;
			params[i + j * resultMat.height].col = j;
			pthread_create(&threads[i + j * resultMat.height], NULL,
			 &matMult, &params[i + j * resultMat.height]);
		}
	}
	
	//wait for each thread to complete
	for(i=0; i < resultMat.height; i++) {
		for(j=0; j < resultMat.width; j++) {
			pthread_join(threads[i + j * resultMat.height], NULL);
		}
	}
	
	printf("### ALL threads have terminated\n\n");
	
	//result matrix
	printf("C[%d][%d] = {\n ", resultMat.height, resultMat.width);
	fprintf(output, "C[%d][%d] = {\n ", resultMat.height, resultMat.width);
	for(i = 0; i < resultMat . height; i++) {
		for(j = 0; j < resultMat . width; j++){
			printf("\t%d", MATRIX(resultMat,i,j));
			fprintf(output, "\t%d", MATRIX(resultMat,i,j));
		}
		printf("\n");
		fprintf(output, "\n");
	}
	printf("}\n");
	fprintf(output, "}\n");
	
	//clean up at the end
	free(leftMat.array);
	free(rightMat.array);
	free(resultMat.array);
	free(threads);
	free(params);
	fclose(output);

	return 0;
}

void *matMult( void *param ) {
	unsigned int i;
	int result = 0;
	pos_t *pos = (pos_t *) param;
	
	//sum when multiply left's row by right's col
	for(i=0; i < leftMat.width; i++) {
        	result += MATRIX(leftMat, pos->row, i) * MATRIX(rightMat, i, pos->col);
	}
	pthread_mutex_lock(&deadBolt);
	MATRIX(resultMat, pos->row, pos->col) = result;
	pthread_mutex_unlock(&deadBolt);

	return NULL;
}

void matIntake(matrix_t * firstMat, matrix_t * secMat, char * fileName){
	unsigned int i,j;
	unsigned int input;
	FILE *file = fopen(fileName, "r"); //say r as the second param because we only look to read the file
	
	if( file == NULL)
	{
		printf("There is no file by the name %s Closing program\n", fileName);
		exit(1);
	}
	
	//read first two numbers height and width for first matrix
	fscanf(file, "%u", &input);
	firstMat->height = input;
	fscanf(file, "%u", &input);
	firstMat->width = input;
	
	//create array for matrix data
	firstMat->array = (int*) malloc(sizeof(int) * firstMat->height * firstMat->width);
	
	if(firstMat->array == NULL) {
		//bad stuff happened
		printf("Out of memory. Could not allocate Matrix.\n");
		exit(1);
	}
	
	//loop1 for height
	for(i=0; i < firstMat->height; i++) {
	//loop2 for width
		for(j=0; j < firstMat->width; j++) {
			//store stuff in matrix struct
			fscanf(file, "%i", &PMATRIX(firstMat, i, j));
		}
	}
	
	//read two numbers height and width for second matrix
	fscanf(file, "%u", &secMat->height);
	fscanf(file, "%u", &secMat->width);
	
	//create array for matrix data
	secMat->array = (int*) malloc(sizeof(int) * secMat->height * secMat->width);
	
	if(secMat->array == NULL) {
		//bad stuff happened
		printf("Out of memory. Could not allocate Matrix.\n");
		//clean up
		free(firstMat);
		exit(1); 
	}
	
	//loop1 for height
	for(i=0; i < secMat->height; i++) {
		//loop2 for width
		for(j=0; j < secMat->width; j++) {
			//store stuff in matrix struct
			fscanf(file, "%i", &PMATRIX(secMat, i, j));
		}
	}
	//close file
	fclose(file);
}
