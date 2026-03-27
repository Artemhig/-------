#include <iostream>
#include <string>
#include <limits>
#include "consoles.h"

using namespace std;

void displayMenu() {
    cout << "\n=== Меню управления базой данных игровых консолей ===\n";
    cout << "1. Вывести все консоли\n";
    cout << "2. Добавить новую консоль\n";
    cout << "3. Удалить консоль\n";
    cout << "4. Редактировать консоль\n";
    cout << "5. Поиск по производителю\n";
    cout << "6. Поиск по году выпуска\n";
    cout <<"7. Сохранить и выйти\n";
    cout <<"====================================================\n";
    cout << "Введите номер действия: ";
}

int main() {
    string filename;
    
    cout << "=== База данных игровых консолей ===\n\n";
    cout << "Введите имя файла базы данных\n";
    cout << "(например: 'consoles.txt', или нажмите Enter для 'database.txt'): ";
    
    getline(cin, filename);
    if (filename.empty()) {
        filename = "database.txt";
    } else if (filename.find(".txt") == string::npos) {
        filename += ".txt";
    }
    
    cout << "\nИспользуем файл: " << filename << endl;
    
    ConsoleDatabase database(filename);
    int choice;
    string query;
    int year;
    
    do {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:  // Вывести все
                database.printAll();
                break;
                
            case 2:  // Добавить
                database.addConsole();
                break;
                
            case 3:  // Удалить
                cout << "Введите название консоли для удаления: ";
                getline(cin, query);
                database.deleteConsole(query);
                break;
                
            case 4:  // Редактировать
                cout << "Введите название консоли для редактирования: ";
                getline(cin, query);
                database.editConsole(query);
                break;
                
            case 5:  // Поиск по производителю
                cout << "Введите производителя для поиска: ";
                getline(cin, query);
                database.searchByManufacturer(query);
                break;
                
            case 6:  // Поиск по году
                cout << "Введите год выпуска для поиска: ";
                cin >> year;
                database.searchByYear(year);
                break;
                
            case 7:  // Сохранить и выйти
                database.saveToFile();
                cout << "Данные сохранены в файл '" << filename << "'. Выход...\n";
                break;
                
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 7);
    
    return 0;
}