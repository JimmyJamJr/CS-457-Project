#pragma once

#include "ICommand.h"

class UseCommand : public ICommand {
    virtual bool match(std::string input) {
        return to_upper(get_command(input)) == "USE";
    };

    virtual std::string execute(std::string input, std::string database) {
        std::string parms = get_parameters(input);
        std::string db = Database::getDatabase(parms);
        if (db == "") {
            std::cout << "!Failed to use " << input << " because it does not exist.\n";
        }
        else {
            std::cout << "Using database " << input << ".\n";
        }

        return db;
    };
};