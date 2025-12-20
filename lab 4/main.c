#include <stdio.h>
#include <stdlib.h>
#include "consoles.h"

#define FILENAME "database.txt"

void displayMenu() {
    printf("\n=== Меню управления базой данных игровых консолей ===\n");
    printf("1. Вывести все консоли\n");
    printf("2. Добавить новую консоль\n");
    printf("3. Удалить консоль\n");
    printf("4. Редактировать консоль\n");
    printf("5. Поиск по производителю\n");
    printf("6. Поиск по году выпуска\n");
    printf("7. Сохранить и выйти\n");
    printf("====================================================\n");
    printf("Введите номер действия: ");
}

int main() {
    Console *database = loadFromFile(FILENAME);
    int choice;
    char query[100];
    int year;

    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // очистка буфера

        switch (choice) {
            case 1:
                printDatabase(database);
                break;
            case 2:
                database = addConsole(database);
                break;
            case 3:
                printf("Введите название консоли для удаления: ");
                scanf(" %[^\n]", query);
                database = deleteConsole(database, query);
                break;
            case 4:
                printf("Введите название консоли для редактирования: ");
                scanf(" %[^\n]", query);
                database = editConsole(database, query);
                break;
            case 5:
                printf("Введите производителя для поиска: ");
                scanf(" %[^\n]", query);
                searchByManufacturer(database, query);
                break;
            case 6:
                printf("Введите год выпуска для поиска: ");
                scanf("%d", &year);
                searchByYear(database, year);
                break;
            case 7:
                saveToFile(FILENAME, database);
                printf("Данные сохранены. Выход...\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 7);

    freeDatabase(database);
    return 0;
}
