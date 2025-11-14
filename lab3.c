#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Использование: %s \n", argv[0]);
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Ошибка: не могу открыть файл %s\n", argv[1]);
        return 1;
    }
    
    int matrix[100][100];
    int n, i, j;
    
    n = 0;
    while (fscanf(file, "%d", &matrix[0][n]) == 1) {
        n++;
    }
    
    for (i = 1; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);
    
    printf("Матрица %dx%d:\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    
    int max_neg = 0;
    int found = 0;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (matrix[i][j] < 0 && (!found || matrix[i][j] > max_neg)) {
                max_neg = matrix[i][j];
                found = 1;
            }
        }
    }
    
    if (found) {
        printf("\n1. Максимальный отрицательный над побочной диагональю: %d\n", max_neg);
    } else {
        printf("\n1. Отрицательных элементов над побочной диагональю нет\n");
    }
    
    printf("\n2. S для столбцов:\n");
    double a23 = n > 2 ? 3 * matrix[1][2] : 0;
    
    for (j = 0; j < n; j++) {
        double sum = 0;
        for (i = 0; i < n; i++) {
            sum += matrix[i][j];
        }
        double S = sin(sum + a23);
        printf("Столбец %d: S = %.3f\n", j + 1, S);
    }
    
    return 0;
}