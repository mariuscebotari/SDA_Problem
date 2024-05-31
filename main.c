#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Sorting functions
void selection_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void bubble_sort(int arr[], int n);
void merge_sort(int arr[], int l, int r);
void quick_sort(int arr[], int low, int high);
void heap_sort(int arr[], int n);

// Auxiliary functions for sorting
void merge(int arr[], int l, int m, int r);
int partition(int arr[], int low, int high);
void heapify(int arr[], int n, int i);

// Search functions
int linear_search(int arr[], int n, int x);
int binary_search(int arr[], int l, int r, int x);

// Utility functions
void initialize_array(int arr[], int n);
void print_array(int arr[], int n);
void free_array(int *arr);

int main() {
    int n, choice, method, search_method, x;
    int *arr;
    clock_t start, end;
    double cpu_time_used;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Initialize array with random numbers\n");
        printf("2. Display array\n");
        printf("3. Free array memory\n");
        printf("4. Sort array\n");
        printf("5. Search for a number in the array\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initialize_array(arr, n);
                break;
            case 2:
                print_array(arr, n);
                break;
            case 3:
                free_array(arr);
                break;
            case 4:
                printf("Choose sorting method:\n");
                printf("1. Selection Sort\n");
                printf("2. Insertion Sort\n");
                printf("3. Bubble Sort\n");
                printf("4. Merge Sort\n");
                printf("5. Quick Sort\n");
                printf("6. Heap Sort\n");
                printf("Choose an option: ");
                scanf("%d", &method);

                start = clock();
                switch (method) {
                    case 1:
                        selection_sort(arr, n);
                        break;
                    case 2:
                        insertion_sort(arr, n);
                        break;
                    case 3:
                        bubble_sort(arr, n);
                        break;
                    case 4:
                        merge_sort(arr, 0, n - 1);
                        break;
                    case 5:
                        quick_sort(arr, 0, n - 1);
                        break;
                    case 6:
                        heap_sort(arr, n);
                        break;
                    default:
                        printf("Invalid option\n");
                        continue;
                }
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                printf("Sorting executed in %f seconds\n", cpu_time_used);
                break;
            case 5:
                printf("Enter the number to search for: ");
                scanf("%d", &x);
                printf("Choose search method:\n");
                printf("1. Linear Search\n");
                printf("2. Binary Search\n");
                printf("Choose an option: ");
                scanf("%d", &search_method);

                start = clock();
                switch (search_method) {
                    case 1:
                        linear_search(arr, n, x);
                        break;
                    case 2:
                        binary_search(arr, 0, n - 1, x);
                        break;
                    default:
                        printf("Invalid option\n");
                        continue;
                }
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                printf("Search executed in %f seconds\n", cpu_time_used);
                break;
            case 6:
                free(arr);
                return 0;
            default:
                printf("Invalid option\n");
        }
    }
}

// Initialize the array with random numbers
void initialize_array(int arr[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

// Print the array
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Free the allocated memory for the array
void free_array(int *arr) {
    free(arr);
    printf("Memory has been freed\n");
}

// Selection Sort implementation
void selection_sort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// Insertion Sort implementation
void insertion_sort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Bubble Sort implementation
void bubble_sort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

// Merge function used in Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort implementation
void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Partition function used in Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Quick Sort implementation
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// Heapify function used in Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        int swap = arr[i];
        arr[i] = arr[largest];
        arr[largest] = swap;
        heapify(arr, n, largest);
    }
}

// Heap Sort implementation
void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// Linear Search implementation
int linear_search(int arr[], int n, int x) {
    for (int i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
    return -1;
}

// Binary Search implementation
int binary_search(int arr[], int l, int r, int x) {
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == x)
            return m;
        if (arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}
