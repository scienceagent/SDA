#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Array management functions
int *create_random_array(int length);
void display_array(const int *array, int length);
void release_array(int *array);
int *duplicate_array(const int *array, int length);

// Simple sorting algorithms
void sort_selection(int *array, int length);
void sort_insertion(int *array, int length);
void sort_bubble(int *array, int length);

// Advanced sorting algorithms
void sort_merge(int *array, int left, int right);
void sort_quick(int *array, int low, int high);
void sort_heap(int *array, int length);

// Benchmark menu
void benchmark_menu();

int main() {
    srand((unsigned int)time(0));
    benchmark_menu();
    return 0;
}

int *create_random_array(int length) {
    int *array = (int *)malloc(length * sizeof(int));
    if (!array) {
        perror("Memory allocation failed");
        return NULL;
    }
    for (int i = 0; i < length; i++) {
        array[i] = rand() % 100;
    }
    return array;
}

void display_array(const int *array, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void release_array(int *array) {
    free(array);
}

int *duplicate_array(const int *array, int length) {
    int *copy = (int *)malloc(length * sizeof(int));
    if (!copy) {
        perror("Memory allocation failed");
        return NULL;
    }
    for (int i = 0; i < length; i++) {
        copy[i] = array[i];
    }
    return copy;
}

void sort_selection(int *array, int length) {
    for (int i = 0; i < length - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < length; j++) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }
        int temp = array[min_index];
        array[min_index] = array[i];
        array[i] = temp;
    }
}

void sort_insertion(int *array, int length) {
    for (int i = 1; i < length; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void sort_bubble(int *array, int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void merge(int *array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = array[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

void sort_merge(int *array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        sort_merge(array, left, mid);
        sort_merge(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

int partition(int *array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (array[j] <= pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;
}

void sort_quick(int *array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        sort_quick(array, low, pi - 1);
        sort_quick(array, pi + 1, high);
    }
}

void heapify(int *array, int length, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < length && array[left] > array[largest])
        largest = left;

    if (right < length && array[right] > array[largest])
        largest = right;

    if (largest != i) {
        int swap = array[i];
        array[i] = array[largest];
        array[largest] = swap;
        heapify(array, length, largest);
    }
}

void sort_heap(int *array, int length) {
    for (int i = length / 2 - 1; i >= 0; i--)
        heapify(array, length, i);

    for (int i = length - 1; i >= 0; i--) {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        heapify(array, i, 0);
    }
}

void benchmark_menu() {
    int length;
    printf("Enter the size of the array: ");
    scanf("%d", &length);

    int *array = create_random_array(length);
    if (!array) {
        return;
    }

    printf("Generated array:\n");
    display_array(array, length);

    while (1) {
        printf("\n1. Selection Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Bubble Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Quick Sort\n");
        printf("6. Heap Sort\n");
        printf("7. Exit\n");
        printf("Choose a sorting algorithm: ");

        int choice;
        scanf("%d", &choice);

        clock_t start, end;
        double elapsed_time;

        int *copy = duplicate_array(array, length);
        if (!copy) {
            printf("Memory allocation failed for array copy\n");
            continue;
        }

        switch (choice) {
            case 1:
                start = clock();
                sort_selection(copy, length);
                end = clock();
                break;
            case 2:
                start = clock();
                sort_insertion(copy, length);
                end = clock();
                break;
            case 3:
                start = clock();
                sort_bubble(copy, length);
                end = clock();
                break;
            case 4:
                start = clock();
                sort_merge(copy, 0, length - 1);
                end = clock();
                break;
            case 5:
                start = clock();
                sort_quick(copy, 0, length - 1);
                end = clock();
                break;
            case 6:
                start = clock();
                sort_heap(copy, length);
                end = clock();
                break;
            case 7:
                release_array(array);
                return;
            default:
                printf("Invalid choice\n");
                continue;
        }

        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Sorted array:\n");
        display_array(copy, length);
        printf("Time taken: %f seconds\n", elapsed_time);

        release_array(copy);
    }
}
