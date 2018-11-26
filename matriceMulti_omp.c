//
// MatriceMulti_omp.c
// The objective is to implement openMP in this programm to know how it work.
// Source code : UPHF Moodle - NIAR S.
// Source OpenMP functions : https://www.openmp.org/wp-content/uploads/OpenMP-4.0-C.pdf
// Edited by : MARECHAL Anthony - MOZDZIERZ Ombeline
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

/* ------------------- START - DEFINITIONS ------------------- */

// Size of the matrices (SIZE x SIZE)
#define SIZE 8000
// Number of threads used to execute the program
#define NBTHREAD 2

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

    /*
     * Matrices a, b and r will be shared through the threads.
     * i, j and k loop variables will be private to a thread.
     */

#pragma omp parallel shared(a, b, r) private(i, j, k)
    {

        /*
         * Iterations will be executed in parallel from threads.
         * schedule is the clause which specify the sharing politic.
         * static will divide the iterations into chunk blocks.
         */
#pragma omp for schedule(static)
        for (i = 0; i < n; i = i + 1) {
            for (j = 0; j < n; j = j + 1) {
                a[i][j] = 0;
                for (k = 0; k < n; k = k + 1) {
                    a[i][j] = (a[i][j]) + ((b[i][k]) * (r[k][j]));
                }
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

    double start, finish, wtime;

    // Setting the number of threads
    omp_set_num_threads(NBTHREAD);

    matA = init_mat(size);
    matB = init_mat(size);
    matR = init_mat(size);

    // Collect the time at the start of the programm
    start = omp_get_wtime();

    matR = mult_mat(matA, matB, matR, size);

    // Collect the time at the end of the programm
    finish = omp_get_wtime();

    // Total time during the execution
    wtime = finish - start;

    printf("Running with %d threads. \n", NBTHREAD);
    printf("Elapsed wall clock time = %f seconds.\n", wtime);

    printf("\nTerminé !\n\n");
}

/* ------------------- END - MAIN ------------------- */
