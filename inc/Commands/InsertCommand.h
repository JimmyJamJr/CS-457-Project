#pragma once

#include "ICommand.h"

class InsertCommand : public ICommand {
    // Check command prefix
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "INSERT";
    };

    // Execute the command
    virtual std::string execute(std::string input, std::string database) {
        std::vector<std::string> parms = split(input, " ");

        // Command formatting check
        if (parms.size() < 4 || to_upper(parms[1]) != "INTO" || to_upper(parms[3].substr(0, 7)) != "VALUES(" || remove_semicolon(parms[parms.size()-1]).back() != ')') {
            std::cout << "!INSERT command failed. Bad syntax." << std::endl;
            return "";
        }

        if (database == "") {
            std::cout << "!INSERT command failed. No database is being used." << std::endl;
            return "";
        }

        std::string table = parms[2];

        std::string tuple;
        for (int i = 3; i < parms.size(); i++) {
            if (i == 3) {
                tuple += parms[i].substr(7, parms[i].length() - 7);
            }
            else if (i == parms.size() - 1) {
                tuple += parms[i].substr(0, parms[i].length() - 2);
            }
            else {
                tuple += parms[i];
            }
        }
        std::vector<std::string> tuple_vec = split(tuple, ",");

        bool success;
        try {
            success = Table::insert(database, table, tuple_vec);
        }
        catch (const char * e) {
            std::cout << "!INSERT command failed. Tuple does not fit the table schema." << std::endl;
            return "";
        }

        if (!success) {
            std::cout << "!INSERT command failed. Table does not exist." << std::endl;
            return "";
        }

        std::cout << "1 new record inserted." << std::endl;

        return "";
    };
};