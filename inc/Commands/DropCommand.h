#pragma once

#include "ICommand.h"

class DropCommand : public ICommand {
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "DROP";
    };

    virtual std::string execute(std::string input, std::string database) {
        std::vector<std::string> parms = split(input, " ");

        if (parms.size() < 3) {
            std::cout << "!DROP command failed, requires type and name of object." << std::endl;
            return "";
        }

        std::string type = to_upper(parms[1]);
        std::string name = parms[2];
        if (type == "DATABASE") {
            bool success = Database::deleteDatabase(name);
            std::cout << (success ? "Database " + name + " deleted." : "!Failed to delete " + name + " because it does not exist.") << std::endl;
        }
        else if (type == "TABLE") {
            if (database == "") {
                std::cout << "!Failed to delete " + name + " because no database is being used." << std::endl;
                return "";
            }

            bool success = Table::deleteTable(database, name);
            std::cout << (success ? "Table " + name + " deleted." : "!Failed to delete " + name + " because it does not exist.") << std::endl;
        }
        else {
            std::cout << "!CREATE command failed, invalid object type " + type + "." << std::endl;
        }

        return "";
    };
};