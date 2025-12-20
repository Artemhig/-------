#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consoles.h"

Console* createNode(const char *name, const char *manufacturer, const char *type,
                    int year, float price, int stock) {
    Console *newNode = (Console*)malloc(sizeof(Console));
    if (!newNode) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    strcpy(newNode->name, name);
    strcpy(newNode->manufacturer, manufacturer);
    strcpy(newNode->type, type);
    newNode->year = year;
    newNode->price = price;
    newNode->stock = stock;
    newNode->next = NULL;
    return newNode;
}

Console* loadFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Файл не найден. Будет создан новый при сохранении.\n");
        return NULL;
    }

    Console *head = NULL, *tail = NULL;
    char name[MAX_NAME_LEN], manufacturer[MAX_MANUFACTURER_LEN], type[MAX_TYPE_LEN];
    int year, stock;
    float price;

    while (fscanf(file, "%99[^,],%49[^,],%19[^,],%d,%f,%d\n",
                  name, manufacturer, type, &year, &price, &stock) == 6) {
        Console *newNode = createNode(name, manufacturer, type, year, price, stock);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    fclose(file);
    printf("Данные загружены из файла '%s'.\n", filename);
    return head;
}

void saveToFile(const char *filename, Console *head) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка открытия файла для записи!\n");
        return;
    }

    Console *current = head;
    while (current) {
        fprintf(file, "%s,%s,%s,%d,%.2f,%d\n",
                current->name, current->manufacturer, current->type,
                current->year, current->price, current->stock);
        current = current->next;
    }

    fclose(file);
    printf("Данные сохранены в файл '%s'.\n", filename);
}

void printDatabase(Console *head) {
    if (!head) {
        printf("База данных пуста.\n");
        return;
    }

    printf("\n=== Список игровых консолей ===\n");
    Console *current = head;
    int count = 1;
    while (current) {
        printf("%d. Название: %s\n", count++, current->name);
        printf("   Производитель: %s\n", current->manufacturer);
        printf("   Тип: %s\n", current->type);
        printf("   Год выпуска: %d\n", current->year);
        printf("   Цена: %.2f руб.\n", current->price);
        printf("   На складе: %d шт.\n\n", current->stock);
        current = current->next;
    }
}

Console* addConsole(Console *head) {
    char name[MAX_NAME_LEN], manufacturer[MAX_MANUFACTURER_LEN], type[MAX_TYPE_LEN];
    int year, stock;
    float price;

    printf("Введите название консоли: ");
    scanf(" %[^\n]", name);
    printf("Введите производителя: ");
    scanf(" %[^\n]", manufacturer);
    printf("Введите тип (портативная/домашняя/гибридная): ");
    scanf(" %[^\n]", type);
    printf("Введите год выпуска: ");
    scanf("%d", &year);
    printf("Введите цену (руб.): ");
    scanf("%f", &price);
    printf("Введите количество на складе: ");
    scanf("%d", &stock);

    Console *newNode = createNode(name, manufacturer, type, year, price, stock);
    if (!head) {
        return newNode;
    }

    Console *current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
    printf("Консоль '%s' добавлена.\n", name);
    return head;
}

Console* deleteConsole(Console *head, const char *name) {
    Console *current = head, *prev = NULL;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            free(current);
            printf("Консоль '%s' удалена.\n", name);
            return head;
        }
        prev = current;
        current = current->next;
    }
    printf("Консоль с названием '%s' не найдена.\n", name);
    return head;
}

Console* editConsole(Console *head, const char *name) {
    Console *current = head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("Редактирование консоли '%s':\n", name);
            printf("Новое название (оставьте пустым для сохранения текущего): ");
            char newName[MAX_NAME_LEN];
            scanf(" %[^\n]", newName);
            if (strlen(newName) > 0) strcpy(current->name, newName);

            printf("Новый производитель: ");
            char newManufacturer[MAX_MANUFACTURER_LEN];
            scanf(" %[^\n]", newManufacturer);
            if (strlen(newManufacturer) > 0) strcpy(current->manufacturer, newManufacturer);

            printf("Новый тип: ");
            char newType[MAX_TYPE_LEN];
            scanf(" %[^\n]", newType);
            if (strlen(newType) > 0) strcpy(current->type, newType);

            printf("Новый год выпуска (0 для сохранения текущего): ");
            int newYear;
            scanf("%d", &newYear);
            if (newYear != 0) current->year = newYear;

            printf("Новая цена (0 для сохранения текущей): ");
            float newPrice;
            scanf("%f", &newPrice);
            if (newPrice != 0) current->price = newPrice;

            printf("Новое количество на складе (-1 для сохранения текущего): ");
            int newStock;
            scanf("%d", &newStock);
            if (newStock != -1) current->stock = newStock;

            printf("Данные обновлены.\n");
            return head;
        }
        current = current->next;
    }
    printf("Консоль с названием '%s' не найдена.\n", name);
    return head;
}

void searchByManufacturer(Console *head, const char *manufacturer) {
    Console *current = head;
    int found = 0;
    printf("\nРезультаты поиска по производителю '%s':\n", manufacturer);
    while (current) {
        if (strcmp(current->manufacturer, manufacturer) == 0) {
            printf(" - %s (Тип: %s, Год: %d, Цена: %.2f, В наличии: %d шт.)\n",
                   current->name, current->type, current->year, current->price, current->stock);
            found = 1;
        }
        current = current->next;
    }
    if (!found) printf("Ничего не найдено.\n");
}

void searchByYear(Console *head, int year) {
    Console *current = head;
    int found = 0;
    printf("\nРезультаты поиска по году выпуска '%d':\n", year);
    while (current) {
        if (current->year == year) {
            printf(" - %s (Производитель: %s, Тип: %s, Цена: %.2f, В наличии: %d шт.)\n",
                   current->name, current->manufacturer, current->type, current->price, current->stock);
            found = 1;
        }
        current = current->next;
    }
    if (!found) printf("Ничего не найдено.\n");
}

void freeDatabase(Console *head) {
    Console *current = head;
    while (current) {
        Console *temp = current;
        current = current->next;
        free(temp);
    }
}