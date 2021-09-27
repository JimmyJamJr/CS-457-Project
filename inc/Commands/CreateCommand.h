#pragma once

#include "ICommand.h"

class CreateCommand : public ICommand {
    virtual bool match(std::string input) {
        return to_upper(get_command(input)) == "CREATE";
    };

    virtual std::string execute(std::string input, std::string database) {
        std::string parms = get_parameters(input);
        std::string type = to_upper(get_command(parms));
        std::string name = get_parameters(parms);
        if (type == "DATABASE") {
            bool success = Database::createDatabase(name);
            std::cout << (success ? "Database " + name + " created." : "!Failed to create database " + name + " because it already exists.") << "\n";
        }
        else if (type == "TABLE") {

        }
        else {
            std::cout << "!CREATE command failed, invalid object type " + type + ".\n";
        }

        return "";
    };
};