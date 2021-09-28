#include "Table.h"
#include <fstream>
#include <iostream>
#include <filesystem>

Table::Table(std::string _database, std::string _name) {
    name = _name;
    database = _database;
}

bool Table::createTable(std::string database, std::string name, std::string schema) {
    if (std::filesystem::exists(database + name + ".txt")) {
        return false;
    }
    std::ofstream f(database + name + ".txt");
    f << schema;
    f.close();
    return true;
}