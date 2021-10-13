#pragma once

#include "ICommand.h"
#include <fstream>

class UpdateCommand : public ICommand {
    // Check command prefix
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "UPDATE";
    };

    // Execute the command
    virtual std::string execute(std::string input, std::string database) {
        std::vector<std::string> parms = split(input, " ");

        // Command formatting check
        if (parms.size() < 10 || to_upper(parms[2]) != "SET" || to_upper(parms[6]) != "WHERE") {
            std::cout << "!DELETE command failed. Bad syntax." << std::endl;
            return "";
        }

        if (database == "") {
            std::cout << "!DELETE command failed. No database is being used." << std::endl;
            return "";
        }

        std::string table = parms[1];
        std::string set_attribute = parms[3];
        std::string set_op = parms[4];
        std::string set_operand = parms[5];
        std::string where_attribute = parms[7];
        std::string where_op = parms[8];
        std::string where_operand = parms[9];

        std::vector<std::string> schema = Table::getSchema(database, table);
        if (schema.size() == 0) {
            std::cout << "!Failed to delete from " + table + " because it does not exist." << std::endl;
            return "";
        }

        int set_att_index = -1;
        int where_att_index = -1;
        for (int i = 0 ; i < schema.size(); i++) {
            if (split(schema[i], " ")[0] == set_attribute) {
                set_att_index = i;
            }
            if (split(schema[i], " ")[0] == where_attribute) {
                where_att_index = i;
            }

        }

        if (set_att_index == -1 || where_att_index == -1) {
            std::cout << "!UPDATE command failed. Attribute is not in schema." << std::endl;
            return "";
        }

        std::ifstream file = Table::getFile(database, table);
        std::string line;
        int modified_count = 0;
        int line_count = 0;
        std::vector<std::string> lines;
        while (getline(file, line)) {
            line_count++;
            if (line_count != 1) {
                std::vector<std::string> row = split(line, " | ");
                bool modify = false;
                if (where_op == "=") {
                    modify = row[where_att_index] == where_operand;
                }
                else if (where_op == "<") {
                    modify = std::stof(row[where_att_index]) < std::stof(where_operand);
                }
                else if (where_op == ">") {
                    modify = std::stof(row[where_att_index]) < std::stof(where_operand);
                }

                if (modify) {
                    modified_count++;
                    row[set_att_index] = set_operand;
                    std::string new_line = "";
                    for (int i = 0; i < row.size(); i++) {
                        new_line += (i > 0 ? " | " : "") + row[i];
                    }
                    lines.push_back(new_line);
                }
                else {
                    lines.push_back(line);
                }
            }
            else {
                lines.push_back(line);
            }
        }

        Table::replace(database, table, lines);
        std::cout << modified_count << " record" << (modified_count > 1 ? "s modified." : " modified.") << std::endl;

        return "";
    };
};