#include <malloc.h>
#include <stdio.h>
#include <limits.h>

/* ----------------------------------------------------------------------------------------- *
 *                                          HEADER                                           *
 * ----------------------------------------------------------------------------------------- */

/**
 * A struct that represents a dynamic integer matrix, containing its size.
 * To use, you'll need to allocate memory for matrix variable.
 */
typedef struct Matrix {
    int size;
    int **matrix;
} Matrix;

/**
 * Fill a dynamic integer matrix, reading from standard input (using scanf).
 *
 * @param matrix Matrix * A pointer to the matrix that will be filled.
 */
void fillMatrix(Matrix *matrix);

/**
 * Free all memory space allocated by a dynamic integer matrix.
 * This function deallocate either param's matrix pointer and Matrix's matrix variable.
 *
 * @param matrix
 */
void deleteMatrix(Matrix *matrix);

/**
 * Given a 1-dimensional array of positive and negative integers, this function finds
 * the largest sum of subsequent elements.
 *
 * @param array int * A pointer to the 1-dimensional array.
 * @param size int Array size.
 * @return int Maximum sum of subsequent elements.
 */
int maxSumArray(int *array, int size);

/**
 * Given a 2-dimensional array of positive and negative integers, this functions finds
 * the sub-rectangle with the largest sum. The sum of the rectangle is
 * the sum of all elements in that rectangle.
 *
 * @param matrix Matrix * A pointer to the 2-dimensional array.
 * @return the sum of all elements in the sub-rectangle.
 */
int maxSumMatrix(Matrix *matrix);
/* ----------------------------------------------------------------------------------------- *
 *                                        IMPLEMENTATION                                     *
 * ----------------------------------------------------------------------------------------- */

int main() {
    int size;
    while (scanf("%d", &size) != EOF) {
        Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
        matrix->size = size;

        fillMatrix(matrix);
        int sum = maxSumMatrix(matrix);
        printf("%d\n", sum);

        deleteMatrix(matrix);
    }

    return 0;
}

void fillMatrix(Matrix *matrix) {
    matrix->matrix = (int**) malloc(sizeof(int*) * matrix->size);

    for (int i = 0; i < matrix->size; i++) {
        matrix->matrix[i] = (int *) malloc(sizeof(int) * matrix->size);

        for (int j = 0; j < matrix->size; j++) {
            scanf("%d", &matrix->matrix[i][j]);
        }
    }
}

void deleteMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->size; i++) {
        free(matrix->matrix[i]);
    }

    free(matrix->matrix);
    free(matrix);
}

int maxSumArray(int *array, int size) {
    int maxSum = array[0];
    int currentSum = array[0];

    for (int i = 1; i < size; i++) {
        currentSum += array[i];
        currentSum = (array[i] > currentSum) ? array[i] : currentSum;
        maxSum = (currentSum > maxSum) ? currentSum : maxSum;
    }

    return  maxSum;
}

int maxSumMatrix(Matrix *matrix) {
    int maxSum = INT_MIN;

    for (int i = 0; i < matrix->size; i++) {
        int *array = (int*) calloc((size_t) matrix->size, sizeof(int));

        for (int j = i; j < matrix->size; j++) {
            for (int k = 0; k < matrix->size; k++) {
                array[k] += matrix->matrix[j][k];
            }

            int sumArray = maxSumArray(array, matrix->size);
            maxSum = (sumArray > maxSum) ? sumArray : maxSum;
        }

        free(array);
    }

    return maxSum;
}