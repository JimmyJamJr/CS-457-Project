#pragma once

#include "ICommand.h"

class DropCommand : public ICommand {
    virtual bool match(std::string input) {
        return to_upper(get_command(input)) == "DROP";
    };

    virtual std::string execute(std::string input, std::string database) {
        std::string parms = get_parameters(input);
        std::string type = to_upper(get_command(parms));
        std::string name = get_parameters(parms);
        if (type == "DATABASE") {
            bool success = Database::deleteDatabase(name);
            std::cout << (success ? "Database " + name + " deleted." : "!Failed to delete database " + name + " because it does not exist.") << "\n";
        }
        else if (type == "TABLE") {

        }
        else {
            std::cout << "!CREATE command failed, invalid object type " + type + ".\n";
        }

        return "";
    };
};