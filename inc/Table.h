// Jimson Huang
// CS457
// 9/29/2021
// Table class consisting of entirely static functions for the purpose of 
// managing/manipulating the text files associated with each table.

#pragma once

#include <string>
#include "Util.h"

class Table {
    public:
    // Creates a table given a database, name, and table schema; returns false if the table already exists.
    static bool createTable(std::string database, std::string name, std::string schema);
    // Gets the schema of a table given its database and name, in the form of a vector of attribute, type.
    static std::vector<std::string> getSchema(std::string database, std::string name);
    // Gets the input stream of a table file given its database and name.
    static std::ifstream getFile(std::string database, std::string name);
    // Delete a table given its databse and name, returns false if the table does not exist.
    static bool deleteTable(std::string database, std::string name);
    // Changes the schema of a table given its database, name, and a new schema string, returns true if successful.
    static bool alterSchema(std::string database, std::string name, std::string schema);
    // Insert a new tuple in the table
    static bool insert(std::string database, std::string name, std::vector<std::string> tuple);
    // Replace the contents of the table with a new vector of tuples
    static bool replace(std::string database, std::string name, std::vector<std::string> lines);
};