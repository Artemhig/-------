#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consoles.h"

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
    char filename[MAX_FILENAME_LEN];
    Console *database = NULL;
    int choice;
    char query[100];
    int year;
    
    printf("=== База данных игровых консолей ===\n\n");
    printf("Введите имя файла базы данных\n");
    printf("(например: 'consoles.txt', или нажмите Enter для 'database.txt'): ");
    
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        strcpy(filename, "database.txt");
    } else {
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }
        
        if (strlen(filename) == 0) {
            strcpy(filename, "database.txt");
        } else {
            if (strstr(filename, ".txt") == NULL) {
                strcat(filename, ".txt");
            }
        }
    }
    
    printf("\nИспользуем файл: %s\n", filename);
    
    database = loadFromFile(filename);
    
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); 

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
                saveToFile(filename, database);
                printf("Данные сохранены в файл '%s'. Выход...\n", filename);
                break;
                
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 7);

    freeDatabase(database);
    return 0;
}