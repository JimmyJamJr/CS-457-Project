// Jimson Huang
// CS457
// 9/29/2021
// Updated 10/19/2021
// See header file for descriptions.
// Converts all table names to lower case.

#include "Table.h"

#include <fstream>
#include <iostream>
#include <filesystem>

bool Table::createTable(std::string database, std::string name, std::string schema) {
    if (std::filesystem::exists(database + to_lower(name) + ".txt")) {
        return false;
    }
    std::ofstream f(database + to_lower(name) + ".txt");
    f << schema;
    f.close();
    return true;
}

std::vector<std::string> Table::getSchema(std::string database, std::string name) {
    if (!std::filesystem::exists(database + to_lower(name) + ".txt")) {
        return {};
    }

    std::string schema_str;
    std::ifstream f(database + to_lower(name) + ".txt");
    getline(f, schema_str);
    f.close();

    std::vector<std::string> schema = split(schema_str, " | ");
    return schema;
}

std::ifstream Table::getFile(std::string database, std::string name) {
    std::ifstream f(database + to_lower(name) + ".txt");
    return f;
}

bool Table::deleteTable(std::string database, std::string name) {
    if (std::filesystem::exists(database + to_lower(name) + ".txt")) {
        std::filesystem::remove(database + to_lower(name) + ".txt");
        return true;
    }
    return false;
}

bool Table::alterSchema(std::string database, std::string name, std::string schema) {
    if (!std::filesystem::exists(database + to_lower(name) + ".txt")) {
        return false;;
    }

    // Read all lines of table file into a vector
    std::ifstream inf(database + to_lower(name) + ".txt");
    std::vector<std::string> lines;
    std::string line;
    while (getline(inf, line)) {
        if (line.size() > 0) 
            lines.push_back(line);
    }
    inf.close();

    // Change the first line (schema) then write all the lines back into file
    lines[0] = schema;
    std::ofstream outf(database + to_lower(name) + ".txt");
    for (std::string l : lines) {
        outf << l << "\n";
    }
    outf.close();
    return true;
}

bool Table::insert(std::string database, std::string name, std::vector<std::string> tuple) {
    // Return false if table file doesn't exist
    if (!std::filesystem::exists(database + to_lower(name) + ".txt")) {
        return false;;
    }

    // Return false if the schema of the tuple doesn't match the schema of the table
    std::vector<std::string> schema = getSchema(database, name);
    if (schema.size() != tuple.size()) {
        throw "Schema mismatch";
        return false;
    }

    // Append the tuple to the end of the table file
    std::ofstream outf;
    outf.open(database + to_lower(name) + ".txt", std::ios::app);
    outf << "\n";
    for (int i = 0; i < tuple.size(); i++) {
        outf << tuple[i];
        if (i < tuple.size() - 1) {
            outf << " | ";
        }
    }
    outf.close();
    return true;
}

bool Table::replace(std::string database, std::string name, std::vector<std::string> lines) {
    std::ofstream f(database + to_lower(name) + ".txt");
    // Override contents of a table
    for (auto it = lines.begin(); it != lines.end(); it++) {
        f << *it;
        if (it != lines.end() - 1) {
            f << "\n";
        }
    }
    return true;
}
