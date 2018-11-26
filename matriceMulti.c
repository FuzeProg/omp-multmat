//
// matriceMulti.c
// Source code : UPHF Moodle - NIAR S.
// Edited by : MARECHAL Anthony - MOZDZIERZ Ombeline
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ------------------- START - DEFINITIONS ------------------- */

// Size of the matrices (SIZE x SIZE)
#define SIZE 8000

/* ------------------- END - DEFINITIONS ------------------- */

/* ------------------- START - FUNCTIONS ------------------- */

// Initialize the matrice and fill it with 0
float **init_mat(int n) {
    int i, j;

    float **matrice;

    matrice = (float **) malloc(n * sizeof(int *));

    for (i = 0; i < n; i++) {
        matrice[i] = (float *) malloc(n * sizeof(int));

        for (j = 0; j < n; j++) {
            matrice[i][j] = 1.0;
        }
    }
    return matrice;
}

// Multiply the matrices between them and fill the r matrice with the result
float **mult_mat(float **a, float **b, float **r, int n) {
    int i, j, k;
        for (i = 0; i < n; i = i + 1) {
            for (j = 0; j < n; j = j + 1) {
                a[i][j] = 0;
                for (k = 0; k < n; k = k + 1) {
                    a[i][j] = (a[i][j]) + ((b[i][k]) * (r[k][j]));
                }
            }
        }
    return 0;
}

/* ------------------- END - FUNCTIONS ------------------- */


/* ------------------- START - MAIN ------------------- */

int main() {
    // Matrice A, B and Result
    float **matA, **matB, **matR = 0;

    clock_t start, finish;
    float exec_time;

    matA = init_mat(SIZE);
    matB = init_mat(SIZE);
    matR = init_mat(SIZE);

    // Collect the time at the start of the program
    start = clock();

    matR = mult_mat(matA, matB, matR, size);

    // Collect the time at the end of the program
    finish = clock();

    // Total time during the execution
    exec_time = (float)(finish-start)/CLOCKS_PER_SEC;

    printf("Running with %d threads. \n", nbthreads);
    printf("Elapsed wall clock time = %f seconds.\n", wtime);

    printf("\nTerminé !\n\n");
}

/* ------------------- END - MAIN ------------------- */
