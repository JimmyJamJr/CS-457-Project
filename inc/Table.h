#pragma once

#include <string>
#include "Util.h"

class Table {
    public:
    static bool createTable(std::string database, std::string name, std::string schema);
    static std::vector<std::string> getSchema(std::string database, std::string name);
    static std::ifstream getFile(std::string database, std::string name);
    static bool deleteTable(std::string database, std::string name);
};