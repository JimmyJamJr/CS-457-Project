// Jimson Huang
// CS457
// 9/29/2021
// Create command for creating new tables or databases.

#pragma once

#include "ICommand.h"

class CreateCommand : public ICommand {
    // Check command prefix
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "CREATE";
    };

    // Execute the command
    virtual std::pair<std::string, std::shared_ptr<Transaction>> execute(std::string input, std::string database, std::shared_ptr<Transaction> transaction) {
        std::vector<std::string> parms = split(input, " ");

        // Command conditions check
        if (parms.size() < 3) {
            std::cout << "!CREATE command failed, requires type and name of object." << std::endl;
            return default_return;
        }

        std::string type = to_upper(parms[1]);
        std::string name = split(parms[2], "(")[0];
        // Create a new database
        if (type == "DATABASE") {
            bool success = Database::createDatabase(name);
            std::cout << (success ? "Database " + name + " created." : "!Failed to create database " + name + " because it already exists.") << std::endl;
        }
        // Create a new table
        else if (type == "TABLE") {
            // Get schema from input string
            int schema_start_i;
            // Find the position of the '(' character which indicates the start of the schema
            for (schema_start_i = 0; schema_start_i < input.size() && input[schema_start_i] != '('; schema_start_i++);
            std::string schema_str = input.substr(schema_start_i, input.length() - schema_start_i);
            std::vector<std::string> schema_vec = split(schema_str, " ");
            std::string schema = create_schema(schema_vec);
            
            // Comamnd fails if no database being used or schema format incorrect.
            if (database == "") {
                std::cout << "!Failed to create table " + name + " because no database is being used." << std::endl;
                return default_return;
            }

            if (schema == "") {
                std::cout << "!Failed to create table " + name + " because the schema format is incorrect." << std::endl;
                return default_return;
            }
            
            // Try to create the new table
            bool success = Table::createTable(database, name, schema);
            std::cout << (success ? "Table " + name + " created." : "!Failed to create table " + name + " because it already exists.") << std::endl;
        }
        else {
            std::cout << "!CREATE command failed, invalid object type " + type + "." << std::endl;
        }

        return default_return;
    };

    private:
    // Create table schema string given a vector of attributes, types
    std::string create_schema(std::vector<std::string> schema_vec) {
        if (schema_vec.size() < 2 || schema_vec.size() % 2 != 0) return "";

        // Create schema in the format of name, type | ...
        std::string schema = "";
        int i = 0;
        for (std::string word : schema_vec) {
            if (i == 0) {
                if (word[0] != '(') {
                    return "";
                }
                schema += word.substr(1, word.length() - 1) + " ";
            }
            else if (i == schema_vec.size() - 1) {
                if (word[word.length() - 1] != ')') {
                    return "";
                }
                schema += word.substr(0, word.length() - 1);
            }
            else {
                schema += i % 2 == 0 ? word + " " : word.substr(0, word.length() - 1) + " | ";
            }
            i++;
        }

        return schema;
    }
};