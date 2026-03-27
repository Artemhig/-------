#include "consoles.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

// ==================== Класс Console ====================

Console::Console() 
    : name(""), manufacturer(""), type(""), year(0), price(0.0), stock(0) {}

Console::Console(const string& name, const string& manufacturer, 
                 const string& type, int year, double price, int stock)
    : name(name), manufacturer(manufacturer), type(type), 
      year(year), price(price), stock(stock) {}

string Console::getTypeRussian() const {
    if (type == "portable") return "портативная";
    if (type == "home") return "домашняя";
    if (type == "hybrid") return "гибридная";
    return type;
}

void Console::display() const {
    cout << "Название: " << name << endl;
    cout << "Производитель: " << manufacturer << endl;
    cout << "Тип: " << getTypeRussian() << endl;
    cout << "Год выпуска: " << year << endl;
    cout << "Цена: " << fixed << setprecision(2) << price << " руб." << endl;
    cout << "На складе: " << stock << " шт." << endl;
}

bool Console::operator==(const Console& other) const {
    return name == other.name;
}

// ==================== Класс ConsoleDatabase ====================

ConsoleDatabase::ConsoleDatabase(const string& filename) : filename(filename) {
    loadFromFile();
}

string ConsoleDatabase::getTypeFromChoice(int choice) const {
    switch(choice) {
        case 1: return "portable";
        case 2: return "home";
        case 3: return "hybrid";
        default: return "unknown";
    }
}

int ConsoleDatabase::getChoiceFromType(const string& type) const {
    if (type == "portable") return 1;
    if (type == "home") return 2;
    if (type == "hybrid") return 3;
    return 0;
}

void ConsoleDatabase::clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool ConsoleDatabase::loadFromFile() {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Файл не найден. Будет создан новый при сохранении." << endl;
        return false;
    }
    
    consoles.clear();
    string name, manufacturer, type;
    int year, stock;
    double price;
    
    while (getline(file, name, ',') &&
           getline(file, manufacturer, ',') &&
           getline(file, type, ',') &&
           (file >> year) && file.ignore() &&
           (file >> price) && file.ignore() &&
           (file >> stock) && file.ignore()) {
        
        consoles.emplace_back(name, manufacturer, type, year, price, stock);
    }
    
    file.close();
    cout << "Данные загружены из файла '" << filename << "' (" << consoles.size() << " записей)." << endl;
    return true;
}

bool ConsoleDatabase::saveToFile() const {
    return saveToFile(filename);
}

bool ConsoleDatabase::saveToFile(const string& newFilename) const {
    ofstream file(newFilename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return false;
    }
    
    for (const auto& console : consoles) {
        file << console.getName() << ","
             << console.getManufacturer() << ","
             << console.getType() << ","
             << console.getYear() << ","
             << fixed << setprecision(2) << console.getPrice() << ","
             << console.getStock() << endl;
    }
    
    file.close();
    cout << "Данные сохранены в файл '" << newFilename << "'." << endl;
    return true;
}

void ConsoleDatabase::printAll() const {
    if (consoles.empty()) {
        cout << "База данных пуста." << endl;
        return;
    }
    
    cout << "\n=== Список игровых консолей (" << consoles.size() << " шт.) ===\n";
    for (size_t i = 0; i < consoles.size(); ++i) {
        cout << i + 1 << ". ";
        consoles[i].display();
        cout << endl;
    }
}

void ConsoleDatabase::addConsole() {
    string name, manufacturer;
    int year, stock, typeChoice;
    double price;
    
    cout << "Введите название консоли: ";
    clearInputBuffer();
    getline(cin, name);
    
    cout << "Введите производителя: ";
    getline(cin, manufacturer);
    
    cout << "Выберите тип:\n";
    cout << "1. Портативная\n";
    cout << "2. Домашняя\n";
    cout << "3. Гибридная\n";
    cout << "Ваш выбор (1-3): ";
    cin >> typeChoice;
    
    string type = getTypeFromChoice(typeChoice);
    
    cout << "Введите год выпуска: ";
    cin >> year;
    
    cout << "Введите цену (руб.): ";
    cin >> price;
    
    cout << "Введите количество на складе: ";
    cin >> stock;
    
    consoles.emplace_back(name, manufacturer, type, year, price, stock);
    cout << "Консоль '" << name << "' добавлена." << endl;
}

bool ConsoleDatabase::deleteConsole(const string& name) {
    auto it = find_if(consoles.begin(), consoles.end(),
        [&name](const Console& c) { return c.getName() == name; });
    
    if (it != consoles.end()) {
        consoles.erase(it);
        cout << "Консоль '" << name << "' удалена." << endl;
        return true;
    }
    
    cout << "Консоль с названием '" << name << "' не найдена." << endl;
    return false;
}

bool ConsoleDatabase::editConsole(const string& name) {
    auto it = find_if(consoles.begin(), consoles.end(),
        [&name](const Console& c) { return c.getName() == name; });
    
    if (it == consoles.end()) {
        cout << "Консоль с названием '" << name << "' не найдена." << endl;
        return false;
    }
    
    Console& console = *it;
    cout << "Редактирование консоли '" << name << "':" << endl;
    
    // Редактирование названия
    cout << "Новое название (Enter для сохранения текущего): ";
    clearInputBuffer();
    string newName;
    getline(cin, newName);
    if (!newName.empty()) console.setName(newName);
    
    // Редактирование производителя
    cout << "Новый производитель (Enter для сохранения текущего): ";
    string newManufacturer;
    getline(cin, newManufacturer);
    if (!newManufacturer.empty()) console.setManufacturer(newManufacturer);
    
    // Редактирование типа
    cout << "Новый тип (1-портативная, 2-домашняя, 3-гибридная, 0-оставить текущий): ";
    int newTypeChoice;
    cin >> newTypeChoice;
    if (newTypeChoice >= 1 && newTypeChoice <= 3) {
        console.setType(getTypeFromChoice(newTypeChoice));
    }
    
    // Редактирование года
    cout << "Новый год выпуска (0 для сохранения текущего): ";
    int newYear;
    cin >> newYear;
    if (newYear != 0) console.setYear(newYear);
    
    // Редактирование цены
    cout << "Новая цена (0 для сохранения текущей): ";
    double newPrice;
    cin >> newPrice;
    if (newPrice != 0) console.setPrice(newPrice);
    
    // Редактирование количества
    cout << "Новое количество на складе (-1 для сохранения текущего): ";
    int newStock;
    cin >> newStock;
    if (newStock != -1) console.setStock(newStock);
    
    cout << "Данные обновлены." << endl;
    return true;
}

void ConsoleDatabase::searchByManufacturer(const string& manufacturer) const {
    cout << "\nРезультаты поиска по производителю '" << manufacturer << "':\n";
    
    bool found = false;
    for (const auto& console : consoles) {
        if (console.getManufacturer() == manufacturer) {
            cout << " - ";
            console.display();
            cout << endl;
            found = true;
        }
    }
    
    if (!found) cout << "Ничего не найдено." << endl;
}

void ConsoleDatabase::searchByYear(int year) const {
    cout << "\nРезультаты поиска по году выпуска '" << year << "':\n";
    
    bool found = false;
    for (const auto& console : consoles) {
        if (console.getYear() == year) {
            cout << " - ";
            console.display();
            cout << endl;
            found = true;
        }
    }
    
    if (!found) cout << "Ничего не найдено." << endl;
}

vector<Console> ConsoleDatabase::findByName(const string& name) const {
    vector<Console> result;
    copy_if(consoles.begin(), consoles.end(), back_inserter(result),
        [&name](const Console& c) { return c.getName() == name; });
    return result;
}

void ConsoleDatabase::clear() {
    consoles.clear();
    cout << "База данных очищена." << endl;
}