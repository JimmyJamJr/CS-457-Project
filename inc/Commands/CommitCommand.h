// Jimson Huang
// CS457
// 12/8/2021
// Command for commiting a transaction

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

        // Error if no transactions being used
        if (transaction == nullptr) {
            std::cout << "!COMMIT command failed, no ongoing transaction." << std::endl;
            return default_return;
        }

        // Abort if no modifications were done during the transaction
        if (transaction->getModifications().size() == 0) {
            std::cout << "Transaction abort." << std::endl;
            return default_return;
        }

        // Write all the modifications in the transcation to disk
        for (auto modification : transaction->getModifications()) {
            std::string db = std::get<0>(modification);
            std::string table = std::get<1>(modification);
            std::vector<std::string> contents = std::get<2>(modification);

            // Unlock the table so it can be used by another process
            Table::release(database, table);
            Table::replace(database, table, contents);
        }

        std::cout << "Transaction committed!" << std::endl;

        return default_return;
    };
};