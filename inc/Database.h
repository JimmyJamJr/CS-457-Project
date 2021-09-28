#pragma once

#include "Table.h"
#include <vector>
#include <memory>
#include <string>

class Database {
    private:
    static std::string getDatabaseFolder();

    public:
    static std::shared_ptr<std::vector<Database>> readDBs();
    static std::string getDatabase(std::string name);
    static bool createDatabase(std::string name);
    static bool deleteDatabase(std::string name);
};