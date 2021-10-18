// Jimson Huang
// CS457
// 10/18/2021
// Delete command for deleting tuples from a table, supports conditions
// using the WHERE keyword.

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

        // Command fails if no database is selected.
        if (database == "") {
            std::cout << "!DELETE command failed. No database is being used." << std::endl;
            return "";
        }

        std::string table = parms[2];
        // Attribute and condition of the WHERE keyword
        std::string attribute = parms[4];
        std::string op = parms[5];
        std::string operand = parms[6];

        std::vector<std::string> schema = Table::getSchema(database, table);
        // Command fails if the table does not exist
        if (schema.size() == 0) {
            std::cout << "!Failed to delete from " + table + " because it does not exist." << std::endl;
            return "";
        }


        // Find the schema index of the WHERE attribute
        int attribute_selected = -1;
        for (int i = 0 ; i < schema.size(); i++) {
            if (split(schema[i], " ")[0] == attribute) {
                attribute_selected = i;
            }
        }

        // If the WHERE attribute is not in the schema
        if (attribute_selected == -1) {
            std::cout << "!DELETE command failed. Attribute is not in schema." << std::endl;
            return "";
        }


        // Go through each tuple of the table file, iterate each attribute in the tuple, if the attribute of the tuple
        // matches the WHERE condition, mark the tuple to be deleted. Then, if the tuple if marked to be deleted,
        // delete the tuple.
        std::ifstream file = Table::getFile(database, table);
        std::string line;
        int deleted_count = 0;
        int line_count = 0;
        std::vector<std::string> lines;
        while (getline(file, line)) {
            line_count++;
            if (line_count != 1) {
                std::vector<std::string> row = split(line, " | ");
                // Check the condition of the WHERE keyword, don't add the tuple in the updated table if the 
                // condition fits
                if (op == "=") {
                    if (operand != row[attribute_selected]) {
                        lines.push_back(line);
                    }
                    else {
                        deleted_count++;
                    }
                }
                else if (op == ">") {
                    float op_int = std::stof(operand);
                    float at_int = std::stof(row[attribute_selected]);
                    if (op_int > at_int) {
                        lines.push_back(line);
                    }
                    else {
                        deleted_count++;
                    }
                }
                else if (op == "<") {
                    float op_int = std::stof(operand);
                    float at_int = std::stof(row[attribute_selected]);
                    if (op_int < at_int) {
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


        // Update table file with new modified table
        Table::replace(database, table, lines);\
        std::cout << deleted_count << " record" << (deleted_count > 1 ? "s deleted." : " deleted.") << std::endl;

        return "";
    };
};