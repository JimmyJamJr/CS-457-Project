#pragma once

#include "ICommand.h"

class CreateCommand : public ICommand {
    public:
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "CREATE";
    };

    virtual std::string execute(std::string input, std::string database) {
        std::vector<std::string> parms = split(input, " ");

        if (parms.size() < 3) {
            std::cout << "!CREATE command failed, requires type and name of object." << std::endl;
            return "";
        }

        std::string type = to_upper(parms[1]);
        std::string name = parms[2];
        if (type == "DATABASE") {
            bool success = Database::createDatabase(name);
            std::cout << (success ? "Database " + name + " created." : "!Failed to create database " + name + " because it already exists.") << std::endl;
        }
        else if (type == "TABLE") {
            std::vector<std::string> schema_vec = {parms.begin() + 3, parms.end()};
            std::string schema = create_schema(schema_vec);
            
            if (database == "") {
                std::cout << "!Failed to create table " + name + " because no database is being used." << std::endl;
                return "";
            }

            if (schema == "") {
                std::cout << "!Failed to create table " + name + " because the schema format is incorrect." << std::endl;
                return "";
            }
            
            bool success = Table::createTable(database, name, schema);
            std::cout << (success ? "Table " + name + " created." : "!Failed to create table " + name + " because it already exists.") << std::endl;
        }
        else {
            std::cout << "!CREATE command failed, invalid object type " + type + "." << std::endl;
        }

        return "";
    };

    private:
    std::string create_schema(std::vector<std::string> schema_vec) {
        if (schema_vec.size() < 2 || schema_vec.size() % 2 != 0) return "";

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