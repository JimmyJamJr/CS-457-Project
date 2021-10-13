#pragma once

#include "ICommand.h"
#include <fstream>

class DeleteCommand : public ICommand {
    // Check command prefix
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "DELETE";
    };

    // Execute the command
    virtual std::string execute(std::string input, std::string database) {
        std::vector<std::string> parms = split(input, " ");

        // Command formatting check
        if (parms.size() < 7 || to_upper(parms[1]) != "FROM" || to_upper(parms[3]) != "WHERE") {
            std::cout << "!DELETE command failed. Bad syntax." << std::endl;
            return "";
        }

        if (database == "") {
            std::cout << "!DELETE command failed. No database is being used." << std::endl;
            return "";
        }

        std::string table = parms[2];
        std::string attribute = parms[4];
        std::string op = parms[5];
        std::string operand = parms[6];

        std::vector<std::string> schema = Table::getSchema(database, table);
        if (schema.size() == 0) {
            std::cout << "!Failed to delete from " + table + " because it does not exist." << std::endl;
            return "";
        }

        int attribute_selected = -1;
        for (int i = 0 ; i < schema.size(); i++) {
            if (split(schema[i], " ")[0] == attribute) {
                attribute_selected = i;
            }
        }

        if (attribute_selected == -1) {
            std::cout << "!DELETE command failed. Attribute is not in schema." << std::endl;
            return "";
        }

        std::ifstream file = Table::getFile(database, table);
        std::string line;
        int deleted_count = 0;
        int line_count = 0;
        std::vector<std::string> lines;
        while (getline(file, line)) {
            line_count++;
            if (line_count != 1) {
                std::vector<std::string> row = split(line, " | ");
                if (op == "=") {
                    if (operand != row[attribute_selected]) {
                        lines.push_back(line);
                    }
                    else {
                        deleted_count++;
                    }
                }
            }
            else {
                lines.push_back(line);
            }
        }

        Table::replace(database, table, lines);\
        std::cout << deleted_count << " record" << (deleted_count > 1 ? "s deleted." : " deleted.") << std::endl;

        return "";
    };
};