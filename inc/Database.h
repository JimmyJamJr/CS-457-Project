#pragma once

#include "Table.h"
#include <vector>
#include <memory>
#include <string>

class Database {
    private:
    int tableCount_;
    std::vector<std::shared_ptr<Table>> tables_;

    static std::string getDatabaseFolder();

    public:
    static std::shared_ptr<std::vector<Database>> readDBs();
    static std::shared_ptr<Database> getDatabase(std::string name);
    static bool createDatabase(std::string name);
    static bool deleteDatabase(std::string name);
    Database(std::string name);
    std::shared_ptr<Table> getTable(std::string name);
};