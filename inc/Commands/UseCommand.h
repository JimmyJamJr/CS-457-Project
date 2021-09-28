#pragma once

#include "ICommand.h"

class UseCommand : public ICommand {
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "USE";
    };

    virtual std::string execute(std::string input, std::string database) {
        std::vector<std::string> parms = split(input, " ");

        if (parms.size() < 2) {
            std::cout << "!USE command failed, requires name of database." << std::endl;
            return "";
        }

        std::string db = Database::getDatabase(parms[1]);
        if (db == "") {
            std::cout << "!Failed to use " << parms[1] << " because it does not exist." << std::endl;
        }
        else {
            std::cout << "Using database " << parms[1] << "." << std::endl;
        }

        return db;
    };
};