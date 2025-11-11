#include <stdio.h>

int isValidInput(int n, int m) {
    return (n > 0 && m > 0);
}

int countPaths(int x, int y, int n, int m) {
    if (x == n - 1 && y == m - 1) {
        return 1;
    }
    int paths = 0;
    if (y < m - 1) {
        paths += countPaths(x, y + 1, n, m);
    }
    if (x < n - 1) {
        paths += countPaths(x + 1, y, n, m);
    }
    return paths;
}

int main() {
    int N, M;

    printf("N = ");
    scanf("%d", &N);
    printf("M = ");
    scanf("%d", &M);
    
    if (!isValidInput(N, M)) {
        printf("Ошибка\n");
        return 1;
    }

    int totalPaths = countPaths(0, 0, N, M);
    printf("Количество путей в сетке %dx%d: %d\n", N, M, totalPaths);
    
    return 0;
}