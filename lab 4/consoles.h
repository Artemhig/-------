#ifndef CONSOLES_H
#define CONSOLES_H

#define MAX_NAME_LEN 100
#define MAX_MANUFACTURER_LEN 50
#define MAX_TYPE_LEN 20

typedef struct Console {
    char name[MAX_NAME_LEN];
    char manufacturer[MAX_MANUFACTURER_LEN];
    char type[MAX_TYPE_LEN]; // портативная, домашняя, гибридная
    int year;
    float price;
    int stock;
    struct Console *next;
} Console;

// Основные функции для работы с базой данных
Console* loadFromFile(const char *filename);
void saveToFile(const char *filename, Console *head);
void printDatabase(Console *head);
Console* addConsole(Console *head);
Console* deleteConsole(Console *head, const char *name);
Console* editConsole(Console *head, const char *name);
void searchByManufacturer(Console *head, const char *manufacturer);
void searchByYear(Console *head, int year);
void freeDatabase(Console *head);

#endif