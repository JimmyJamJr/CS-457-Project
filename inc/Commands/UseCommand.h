// Jimson Huang
// CS457
// 9/29/2021
// Use command for choosing a specific database to be used.

#pragma once

#include "ICommand.h"

class UseCommand : public ICommand {
    // Check command prefix
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "USE";
    };

    // Execute the command
    virtual std::pair<std::string, std::shared_ptr<Transaction>> execute(std::string input, std::string database, std::shared_ptr<Transaction> transaction) {
        std::vector<std::string> parms = split(input, " ");

        // Command formatting check
        if (parms.size() < 2) {
            std::cout << "!USE command failed, requires name of database." << std::endl;
            return default_return;
        }

        // Attempt to select a database and return its folder path back to main
        std::string db = Database::getDatabase(parms[1]);
        if (db == "") {
            std::cout << "!Failed to use " << parms[1] << " because it does not exist." << std::endl;
        }
        else {
            std::cout << "Using database " << parms[1] << "." << std::endl;
        }

        return {db, nullptr};
    };
};