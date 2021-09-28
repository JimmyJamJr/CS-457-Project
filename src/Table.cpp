#include "Table.h"

#include <fstream>
#include <iostream>
#include <filesystem>

bool Table::createTable(std::string database, std::string name, std::string schema) {
    if (std::filesystem::exists(database + name + ".txt")) {
        return false;
    }
    std::ofstream f(database + name + ".txt");
    f << schema;
    f.close();
    return true;
}

std::vector<std::string> Table::getSchema(std::string database, std::string name) {
    if (!std::filesystem::exists(database + name + ".txt")) {
        return {};
    }

    std::string schema_str;
    std::ifstream f(database + name + ".txt");
    getline(f, schema_str);
    f.close();

    std::vector<std::string> schema = split(schema_str, " | ");
    return schema;
}

std::ifstream Table::getFile(std::string database, std::string name) {
    std::ifstream f(database + name + ".txt");
    return f;
}

bool Table::deleteTable(std::string database, std::string name) {
    if (std::filesystem::exists(database + name + ".txt")) {
        std::filesystem::remove(database + name + ".txt");
        return true;
    }
    return false;
}