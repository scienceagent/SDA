#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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

void linear_search(int *array, int size, int target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return;
        }
    }
}

void binary_search(int *array, int left, int right, int target) {
    while (left <= right) {
        int mid = (left + right) / 2;
        if (array[mid] == target) {
            return;
        }
        if (array[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
}

void sort_array(int *array, int size) {
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

void empirical_analysis() {
    int sizes[] = {100, 1000, 10000, 100000};
    int num_searches = 10000;
    int *array = NULL;
    clock_t start_time, end_time;
    double linear_search_time, binary_search_time;

    printf("N\t100\t1000\t10000\t100000\n");
    printf("Linear search\t");
    for (int i = 0; i < 4; i++) {
        int size = sizes[i];
        initialize_array(&array, size);
        
        start_time = clock();
        for (int j = 0; j < num_searches; j++) {
            int target = rand() % 100;
            linear_search(array, size, target);
        }
        end_time = clock();
        linear_search_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("%f\t", linear_search_time);

        free_array(&array);
    }
    printf("\n");

    printf("Binary search\t");
    for (int i = 0; i < 4; i++) {
        int size = sizes[i];
        initialize_array(&array, size);
        sort_array(array, size);
        
        start_time = clock();
        for (int j = 0; j < num_searches; j++) {
            int target = rand() % 100;
            binary_search(array, 0, size - 1, target);
        }
        end_time = clock();
        binary_search_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("%f\t", binary_search_time);

        free_array(&array);
    }
    printf("\n");
}

void menu() {
    int *dynamic_array = NULL;
    int size;
    int choice;
    int target;

    do {
        printf("Menu:\n");
        printf("1. Initialize array with random numbers\n");
        printf("2. Display array\n");
        printf("3. Free array memory\n");
        printf("4. Search number using Linear Search\n");
        printf("5. Search number using Binary Search\n");
        printf("6. Perform empirical analysis\n");
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
                printf("Enter the number to search: ");
                scanf("%d", &target);
                linear_search(dynamic_array, size, target);
                break;

            case 5:
                if (dynamic_array == NULL) {
                    printf("Array not initialized.\n");
                    break;
                }
                printf("Enter the number to search: ");
                scanf("%d", &target);
                sort_array(dynamic_array, size);
                binary_search(dynamic_array, 0, size - 1, target);
                break;

            case 6:
                empirical_analysis();
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
