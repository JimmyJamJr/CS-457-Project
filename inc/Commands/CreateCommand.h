#pragma once

#include "ICommand.h"

class CreateCommand : public ICommand {
    public:
    virtual bool match(std::string input) {
        return to_upper(get_command(input)) == "CREATE";
    };

    virtual std::string execute(std::string input, std::string database) {
        input = remove_semicolon(input);
        std::string parms = get_parameters(input);
        std::string type = to_upper(get_command(parms));
        std::string name = get_parameters(parms);
        if (type == "DATABASE") {
            bool success = Database::createDatabase(name);
            std::cout << (success ? "Database " + name + " created." : "!Failed to create database " + name + " because it already exists.") << "\n";
        }
        else if (type == "TABLE") {
            std::string schema = get_parameters(name);
            name = get_command(name);
            
            if (database == "") {
                std::cout << "!Failed to create table " + name + " because no database is being used.\n";
                return "";
            }

            if (!schemaCheck(schema)) {
                std::cout << "!Failed to create table " + name + " because the shcema format is incorrect.\n";
                return "";
            }
            
            bool success = Table::createTable(database, name, schema);
            std::cout << (success ? "Table " + name + " created." : "!Failed to create table " + name + " because it already exists.") << "\n";
        }
        else {
            std::cout << "!CREATE command failed, invalid object type " + type + ".\n";
        }

        return "";
    };

    private:
    bool schemaCheck(std::string schema) {
        if (schema == "") return false;
        if (schema.front() != '(' || schema.back() != ')') return false;
        if (schema.find(' ') == std::string::npos) return false;
        return true;
    }
};