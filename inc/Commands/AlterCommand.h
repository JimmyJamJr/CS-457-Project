// Jimson Huang
// CS457
// 9/29/2021
// Alter command for changing the schema of a table.

#pragma once

#include "ICommand.h"
#include <fstream>

class AlterCommand : public ICommand {
    // Check command prefix
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "ALTER";
    };

    // Execute the command
    virtual std::string execute(std::string input, std::string database) {
        std::vector<std::string> parms = split(input, " ");

        // Command formatting check
        if (parms.size() < 6) {
            std::cout << "!ALTER command failed. Bad syntax." << std::endl;
            return "";
        }

        if (database == "") {
            std::cout << "!ALTER command failed. No database is being used." << std::endl;
            return "";
        }

        int addIndex = -1;
        for (int i = 0; i < parms.size(); i++) {
            if (to_upper(parms[i]) == "ADD") {
                addIndex = i;
            }
        }
        if (addIndex == -1) {
            std::cout << "!ALTER command failed. ADD keyword not found." << std::endl;
            return "";
        }

        std::string type = to_upper(parms[1]);
        std::string name = parms[2];


        // Altering a table
        if (type == "TABLE") {
            std::vector<std::string> schema = Table::getSchema(database, name);
            if (schema.size() == 0) {
                std::cout << "!Failed to alter " + name + " because it does not exist." << std::endl;
                return "";
            }

            // Add back existing attributes into new schema
            std::string altered_schema_str = "";
            for (int i = 0; i < schema.size(); i++) {
                altered_schema_str += (i != 0 ? " | " : "") + schema[i];
            }


            // Add new attributes into new schema
            for (int i = addIndex + 1; i < parms.size(); i++) {
                altered_schema_str += ((i - addIndex - 1) % 2 == 0 ? " | " : " ") + parms[i];
            }
            Table::alterSchema(database, name, altered_schema_str);
            std::cout << "Table " << name << " modified." << std::endl;
        }

        return "";
    };
};