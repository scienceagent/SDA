#include <gmp.h>
#include <time.h>
#include <stdio.h>

void multiply_matrices(mpz_t A[2][2], mpz_t B[2][2]);
void matrix_exponentiation(mpz_t A[2][2], int exp);
void compute_fibonacci(int num, mpz_t fib_result);
void compute_fibonacci_iterative(int num, mpz_t fib_result);

int main() {
    int test_cases[] = {50, 100, 1000, 10000, 100000, 1000000};
    int total_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < total_tests; i++) {
        int n = test_cases[i];
        mpz_t matrix_result, iterative_result;
        mpz_inits(matrix_result, iterative_result, NULL);

        clock_t start_matrix = clock();
        compute_fibonacci(n, matrix_result);
        clock_t end_matrix = clock();

        double matrix_time = ((double) (end_matrix - start_matrix)) / CLOCKS_PER_SEC;
        printf("Matrix method execution time for the %dth Fibonacci number: %f seconds\n", n, matrix_time);

        clock_t start_iterative = clock();
        compute_fibonacci_iterative(n, iterative_result);
        clock_t end_iterative = clock();

        double iterative_time = ((double) (end_iterative - start_iterative)) / CLOCKS_PER_SEC;
        printf("Iterative method execution time for the %dth Fibonacci number: %f seconds\n", n, iterative_time);

        mpz_clears(matrix_result, iterative_result, NULL);
    }

    return 0;
}

// Function to multiply two 2x2 matrices A and B, and store the result in A
void multiply_matrices(mpz_t A[2][2], mpz_t B[2][2]) {
    mpz_t a, b, c, d;
    mpz_inits(a, b, c, d, NULL);

    // Compute the product values to store in matrix A
    mpz_mul(a, A[0][0], B[0][0]);
    mpz_addmul(a, A[0][1], B[1][0]);

    mpz_mul(b, A[0][0], B[0][1]);
    mpz_addmul(b, A[0][1], B[1][1]);

    mpz_mul(c, A[1][0], B[0][0]);
    mpz_addmul(c, A[1][1], B[1][0]);

    mpz_mul(d, A[1][0], B[0][1]);
    mpz_addmul(d, A[1][1], B[1][1]);

    // Store the product back in matrix A
    mpz_set(A[0][0], a);
    mpz_set(A[0][1], b);
    mpz_set(A[1][0], c);
    mpz_set(A[1][1], d);

    mpz_clears(a, b, c, d, NULL);
}

// Function to raise matrix A to the power exp and store the result in A
void matrix_exponentiation(mpz_t A[2][2], int exp) {
    if (exp == 0 || exp == 1)
        return;
    mpz_t B[2][2];
    mpz_inits(B[0][0], B[0][1], B[1][0], B[1][1], NULL);
    mpz_set_ui(B[0][0], 1);
    mpz_set_ui(B[0][1], 1);
    mpz_set_ui(B[1][0], 1);
    mpz_set_ui(B[1][1], 0);

    matrix_exponentiation(A, exp / 2);
    multiply_matrices(A, A);

    if (exp % 2 != 0)
        multiply_matrices(A, B);

    mpz_clears(B[0][0], B[0][1], B[1][0], B[1][1], NULL);
}

// Function to compute the nth Fibonacci number using matrix exponentiation
void compute_fibonacci(int num, mpz_t fib_result) {
    mpz_t A[2][2];
    mpz_inits(A[0][0], A[0][1], A[1][0], A[1][1], NULL);
    mpz_set_ui(A[0][0], 1);
    mpz_set_ui(A[0][1], 1);
    mpz_set_ui(A[1][0], 1);
    mpz_set_ui(A[1][1], 0);
    if (num == 0) {
        mpz_set_ui(fib_result, 0);
        mpz_clears(A[0][0], A[0][1], A[1][0], A[1][1], NULL);
        return;
    }

    matrix_exponentiation(A, num - 1);
    mpz_set(fib_result, A[0][0]);
    mpz_clears(A[0][0], A[0][1], A[1][0], A[1][1], NULL);
}

// Function to compute the nth Fibonacci number using iterative method
void compute_fibonacci_iterative(int num, mpz_t fib_result) {
    if (num <= 1) {
        mpz_set_ui(fib_result, num);
    } else {
        mpz_t prev1, prev2;
        mpz_inits(prev1, prev2, NULL);
        mpz_set_ui(prev1, 1);
        mpz_set_ui(prev2, 0);

        for (int i = 2; i <= num; i++) {
            mpz_add(fib_result, prev1, prev2);
            mpz_set(prev2, prev1);
            mpz_set(prev1, fib_result);
        }

        mpz_clears(prev1, prev2, NULL);
    }
}
