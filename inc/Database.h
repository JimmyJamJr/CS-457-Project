// Jimson Huang
// CS457
// 9/29/2021
// Database class consisting of entirely static functions for the purpose of 
// managing/manipulating the folders associated with each database.

#pragma once

#include "Table.h"
#include <vector>
#include <memory>
#include <string>

class Database {
    private:
    // Gets the root folder of all the databases.
    static std::string getDatabaseFolder();

    public:
    // Gets the path of a database given its name, std::string::empty if it doesn't exist.
    static std::string getDatabase(std::string name);
    // Creates a new database folder given its name, returns false if the folder already exists.
    static bool createDatabase(std::string name);
    // Delete a database given its name, returns false if it doesn't exist.
    static bool deleteDatabase(std::string name);
};