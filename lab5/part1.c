#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUMBER 1000001

int size;
int array1[NUMBER];
int array2[NUMBER];
int merge_sort_result[NUMBER];

int sum_result[1001];
int array_a[1001];
int array_b[1001];

void add_arrays(int array_a[1001], int array_b[1001]) {
    int carry = 0;
    bool done = false;
    for (int i = 1000; i > 1; i--) {
        sum_result[i] = (array_a[i] + array_b[i] + carry) % 10;
        carry = (array_a[i] + array_b[i] + carry) / 10;
        if (sum_result[i] == 0 && array_a[i-1] == 0 && array_b[i-1] == 0 && carry == 0)
            break;
    }
    for (int i = 1; i <= 1000; i++)
        array_a[i] = array_b[i];
    for (int i = 1; i <= 1000; i++)
        array_b[i] = sum_result[i];
}

void bubble_sort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void selection_sort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++)
            if (array[j] < array[min_index])
                min_index = j;
        int temp = array[min_index];
        array[min_index] = array[i];
        array[i] = temp;
    }
}

void merge_sort(int *array, int left, int right, int *result) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    merge_sort(array, left, mid, result);
    merge_sort(array, mid + 1, right, result);

    int left_index = left;
    int right_index = mid + 1;
    int index = 0;
    while (left_index <= mid && right_index <= right) {
        if (array[left_index] <= array[right_index])
            result[index++] = array[left_index++];
        else
            result[index++] = array[right_index++];
    }
    while (left_index <= mid)
        result[index++] = array[left_index++];

    while (right_index <= right)
        result[index++] = array[right_index++];

    for (int i = left; i <= right; i++)
        array[i] = result[i - left];
}

void linear_search(int *array, int size, int target) {
    for (int i = 0; i < size; i++)
        if (target == array[i]) {
            printf("The number was found\n");
            return;
        }
    printf("No such number in the randomly chosen array\n");
}

void binary_search(int *array, int left, int right, int target) {
    while (left <= right) {
        int mid = (left + right) / 2;

        if (array[mid] == target) {
            printf("The number was found\n");
            return;
        }

        if (array[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    printf("No such number in the randomly chosen array\n");
}

void initialize_array(int **array, int size) {
    srand(time(NULL));
    *array = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        (*array)[i] = rand() % 100;
    }
}

void display_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void free_array(int **array) {
    free(*array);
    *array = NULL;
}

void menu() {
    int *dynamic_array = NULL;
    int choice;
    clock_t start_time, end_time;
    double execution_time;

    do {
        printf("Menu:\n");
        printf("1. Initialize array with random numbers\n");
        printf("2. Display array\n");
        printf("3. Free array memory\n");
        printf("4. Sort array using Bubble Sort\n");
        printf("5. Sort array using Merge Sort\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (dynamic_array != NULL) {
                    printf("Array is already initialized. Free the memory first.\n");
                    break;
                }
                printf("Enter the size of the array: ");
                scanf("%d", &size);
                initialize_array(&dynamic_array, size);
                printf("Array initialized.\n");
                break;

            case 2:
                if (dynamic_array == NULL) {
                    printf("Array not initialized.\n");
                    break;
                }
                display_array(dynamic_array, size);
                break;

            case 3:
                if (dynamic_array == NULL) {
                    printf("Array not initialized.\n");
                    break;
                }
                free_array(&dynamic_array);
                printf("Array memory freed.\n");
                break;

            case 4:
                if (dynamic_array == NULL) {
                    printf("Array not initialized.\n");
                    break;
                }
                start_time = clock();
                bubble_sort(dynamic_array, size);
                end_time = clock();
                execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
                printf("Array sorted using Bubble Sort in %f seconds.\n", execution_time);
                break;

            case 5:
                if (dynamic_array == NULL) {
                    printf("Array not initialized.\n");
                    break;
                }
                start_time = clock();
                merge_sort(dynamic_array, 0, size - 1, merge_sort_result);
                end_time = clock();
                execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
                printf("Array sorted using Merge Sort in %f seconds.\n", execution_time);
                break;

            case 0:
                if (dynamic_array != NULL) {
                    free_array(&dynamic_array);
                }
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}
