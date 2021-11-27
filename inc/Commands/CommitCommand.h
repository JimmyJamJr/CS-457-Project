#pragma once

#include "ICommand.h"

class CommitCommand : public ICommand {
    // Check command prefix
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "COMMIT";
    };

    // Execute the command
    virtual std::pair<std::string, std::shared_ptr<Transaction>> execute(std::string input, std::string database, std::shared_ptr<Transaction> transaction) {
        std::vector<std::string> parms = split(input, " ");

        if (transaction == nullptr) {
            std::cout << "!COMMIT command failed, no ongoing transaction." << std::endl;
            return default_return;
        }

        if (transaction->getModifications().size() == 0) {
            std::cout << "Transaction abort." << std::endl;
            return default_return;
        }

        for (auto modification : transaction->getModifications()) {
            std::string db = std::get<0>(modification);
            std::string table = std::get<1>(modification);
            std::vector<std::string> contents = std::get<2>(modification);

            Table::release(database, table);
            Table::replace(database, table, contents);
        }

        std::cout << "Transaction committed!" << std::endl;

        return default_return;
    };
};