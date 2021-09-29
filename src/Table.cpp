// Jimson Huang
// CS457
// 9/29/2021
// See header file for descriptions.

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

bool Table::alterSchema(std::string database, std::string name, std::string schema) {
    if (!std::filesystem::exists(database + name + ".txt")) {
        return false;;
    }

    // Read all lines of table file into a vector
    std::ifstream inf(database + name + ".txt");
    std::vector<std::string> lines;
    std::string line;
    while (getline(inf, line)) {
        if (line.size() > 0) 
            lines.push_back(line);
    }
    inf.close();

    // Change the first line (schema) then write all the lines back into file
    lines[0] = schema;
    std::ofstream outf(database + name + ".txt");
    for (std::string l : lines) {
        outf << l << "\n";
    }
    outf.close();
    return true;
}