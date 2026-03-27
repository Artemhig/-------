#ifndef CONSOLES_H
#define CONSOLES_H

#include <string>
#include <vector>
#include <fstream>

class Console {
private:
    std::string name;
    std::string manufacturer;
    std::string type;  // "portable", "home", "hybrid"
    int year;
    double price;
    int stock;

public:
    // Конструкторы
    Console();
    Console(const std::string& name, const std::string& manufacturer, 
            const std::string& type, int year, double price, int stock);
    
    // Геттеры
    std::string getName() const { return name; }
    std::string getManufacturer() const { return manufacturer; }
    std::string getType() const { return type; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
    
    // Сеттеры
    void setName(const std::string& newName) { name = newName; }
    void setManufacturer(const std::string& newManufacturer) { manufacturer = newManufacturer; }
    void setType(const std::string& newType) { type = newType; }
    void setYear(int newYear) { year = newYear; }
    void setPrice(double newPrice) { price = newPrice; }
    void setStock(int newStock) { stock = newStock; }
    
    // Вспомогательные методы
    std::string getTypeRussian() const;
    void display() const;
    
    // Операторы для сравнения
    bool operator==(const Console& other) const;
};

class ConsoleDatabase {
private:
    std::vector<Console> consoles;
    std::string filename;
    
    // Вспомогательные методы
    std::string getTypeFromChoice(int choice) const;
    int getChoiceFromType(const std::string& type) const;
    void clearInputBuffer();

public:
    // Конструктор
    explicit ConsoleDatabase(const std::string& filename = "database.txt");
    
    // Работа с файлами
    bool loadFromFile();
    bool saveToFile() const;
    bool saveToFile(const std::string& newFilename) const;
    
    // CRUD операции
    void printAll() const;
    void addConsole();
    bool deleteConsole(const std::string& name);
    bool editConsole(const std::string& name);
    
    // Поиск
    void searchByManufacturer(const std::string& manufacturer) const;
    void searchByYear(int year) const;
    std::vector<Console> findByName(const std::string& name) const;
    
    // Получение данных
    bool isEmpty() const { return consoles.empty(); }
    size_t getSize() const { return consoles.size(); }
    const std::vector<Console>& getAll() const { return consoles; }
    
    // Очистка
    void clear();
};

#endif