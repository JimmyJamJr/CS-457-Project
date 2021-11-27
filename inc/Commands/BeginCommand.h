#pragma once

#include "ICommand.h"

class BeginCommand : public ICommand {
    // Check command prefix
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "BEGIN";
    };

    // Execute the command
    virtual std::pair<std::string, std::shared_ptr<Transaction>> execute(std::string input, std::string database, std::shared_ptr<Transaction> transaction) {
        std::vector<std::string> parms = split(input, " ");

        // Command formatting check
        if (parms.size() < 2 || to_upper(parms[1]) != "TRANSACTION") {
            std::cout << "!BEGIN command failed, format incorrect." << std::endl;
            return default_return;
        }

        // Attempt to select a database and return its folder path back to main
        std::shared_ptr<Transaction> new_transaction = std::make_shared<Transaction>();

        return {"", new_transaction};
    };
};