// Jimson Huang
// CS457
// 9/29/2021
// Drop command for deleting tables or databases.
#pragma once

#include "ICommand.h"

class DropCommand : public ICommand {
    // Check command prefix
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "DROP";
    };

    // Execute the command
    virtual std::pair<std::string, std::shared_ptr<Transaction>> execute(std::string input, std::string database, std::shared_ptr<Transaction> transaction) {
        std::vector<std::string> parms = split(input, " ");

        // Command formatting check
        if (parms.size() < 3) {
            std::cout << "!DROP command failed, requires type and name of object." << std::endl;
            return default_return;
        }

        std::string type = to_upper(parms[1]);
        std::string name = parms[2];
        // Delete a database
        if (type == "DATABASE") {
            bool success = Database::deleteDatabase(name);
            std::cout << (success ? "Database " + name + " deleted." : "!Failed to delete " + name + " because it does not exist.") << std::endl;
        }
        // Delete a table
        else if (type == "TABLE") {
            if (database == "") {
                std::cout << "!Failed to delete " + name + " because no database is being used." << std::endl;
                return default_return;
            }

            bool success = Table::deleteTable(database, name);
            std::cout << (success ? "Table " + name + " deleted." : "!Failed to delete " + name + " because it does not exist.") << std::endl;
        }
        else {
            std::cout << "!CREATE command failed, invalid object type " + type + "." << std::endl;
        }

        return default_return;
    };
};