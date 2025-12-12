#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Сортировка пузырьком
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Сортировка вставками
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

// Функция слияния для сортировки слиянием
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int* L = malloc(n1 * sizeof(int));
    int* R = malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
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
    
    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

void copyArray(int dest[], int src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main() {
    srand(time(NULL));
    
    int sizes[] = {10, 1000, 10000, 100000};
    int num_sizes = 4;
    
    printf("Размер | Пузырьком | Вставками | Слиянием\n");
    printf("-------|-----------|-----------|----------\n");
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        
        int* original = malloc(n * sizeof(int));
        int* arr1 = malloc(n * sizeof(int));
        int* arr2 = malloc(n * sizeof(int));
        int* arr3 = malloc(n * sizeof(int));
        
        generateArray(original, n);
        
        copyArray(arr1, original, n);
        clock_t start = clock();
        bubbleSort(arr1, n);
        clock_t end = clock();
        double time1 = (double)(end - start) / CLOCKS_PER_SEC;
        
        copyArray(arr2, original, n);
        start = clock();
        insertionSort(arr2, n);
        end = clock();
        double time2 = (double)(end - start) / CLOCKS_PER_SEC;
        
        copyArray(arr3, original, n);
        start = clock();
        mergeSort(arr3, 0, n-1);
        end = clock();
        double time3 = (double)(end - start) / CLOCKS_PER_SEC;
        
        printf("%6d | %9.3f | %9.3f | %8.3f\n", n, time1, time2, time3);
    }
    
    return 0;
}