#pragma once

#include <string>

class Table {
    private:
    std::string name;
    std::string database;
    public:
    static bool createTable(std::string databse, std::string name, std::string schema);
    Table(std::string database, std::string name);

};