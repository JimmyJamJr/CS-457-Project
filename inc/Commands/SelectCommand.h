// Jimson Huang
// CS457
// 9/29/2021
// Select command for selecting attributes from a table.

#pragma once

#include "ICommand.h"
#include <fstream>

class SelectCommand : public ICommand {
    // Check command prefix
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "SELECT";
    };

    // Execute the command
    virtual std::string execute(std::string input, std::string database) {
        std::vector<std::string> parms = split(input, " ");

        // Command formatting check
        if (parms.size() < 4) {
            std::cout << "!SELECT command failed. Bad syntax." << std::endl;
            return "";
        }

        // Command fails if no database in use
        if (database == "") {
            std::cout << "!SELECT command failed. No database is being used." << std::endl;
            return "";
        }

        int fromIndex = -1;

        // attribute and condition of the WHERE keyword
        int whereIndex = -1;
        std::string attribute;
        int attribute_selected;
        std::string op;
        std::string operand;

        // Find the indexes of FROM and WHERE keyword in input
        for (int i = 0; i < parms.size(); i++) {
            if (to_upper(parms[i]) == "FROM") {
                fromIndex = i;
            }
            if (to_upper(parms[i]) == "WHERE") {
                whereIndex = i;
                attribute = parms[i+1];
                op = parms[i+2];
                operand = parms[i+3];
            }
        }
        if (fromIndex == -1) {
            std::cout << "!SELECT command failed. FROM keyword not found." << std::endl;
            return "";
        }

        // Get schema of the table after FROM keyword
        std::string table = parms[fromIndex + 1];
        std::vector<std::string> schema = Table::getSchema(database, table);
        if (schema.size() == 0) {
            std::cout << "!Failed to query " + table + " because it does not exist." << std::endl;
            return "";
        }


        // If the WHERE keyword exists in the command input, get the 
        // schema index of the WHERE attribute
        if (whereIndex != -1) {
            attribute_selected = -1;
            for (int i = 0 ; i < schema.size(); i++) {
                if (split(schema[i], " ")[0] == attribute) {
                    attribute_selected = i;
                }
            }

            if (attribute_selected == -1) {
                std::cout << "!SELECT command failed. Attribute is not in schema." << std::endl;
                return "";
            }
        }

        // Create a list of indexes of the attibutes in the schema that is being selected
        // If * is used, selects all attributes in the schema
        std::string output = "";
        std::vector<std::string> attribute_names = {parms.begin() + 1, parms.begin() + fromIndex};
        std::vector<int> selected_indexes;
        for (std::string attribute : attribute_names) {
            if (attribute[attribute.length() - 1] == ',') {
                attribute = attribute.substr(0, attribute.length() - 1);
            }

            if (attribute == "*") {
                for (int i = 0; i < schema.size(); i++) {
                    selected_indexes.push_back(i);
                }
            }
            else {
                for (int i = 0 ; i < schema.size(); i++) {
                    if (split(schema[i], " ")[0] == attribute) {
                        selected_indexes.push_back(i);
                    }
                }
            }
        }
        
        // Open the txt file associated with the table and read through each line,
        // Printing out the columns corresponding to the attributes that are in selected_index
        std::ifstream file = Table::getFile(database, table);
        std::string line;
        while (getline(file, line)) {
            int count = 0;
            std::vector<std::string> row = split(line, " | ");
            // If the WHERE keyword is used, skip tuples that don't meet its condition
            if (whereIndex != -1) {
                if (op == "=") {
                    if (operand != row[attribute_selected]) {
                        continue;
                    }
                }
                else if (op == "!=") {
                    if (operand == row[attribute_selected]) {
                        continue;
                    }
                }
                else if (op == ">") {
                    float op_int = std::stof(operand);
                    float at_int = std::stof(row[attribute_selected]);
                    if (op_int > at_int) {
                        continue;
                    }
                }
                else if (op == "<") {
                    float op_int = std::stof(operand);
                    float at_int = std::stof(row[attribute_selected]);
                    if (op_int < at_int) {
                        continue;
                    }
                }
            }

            // Print out the tuples and attibrutes that are selected
            for (int i = 0; i < row.size(); i++) {
                if (std::find(selected_indexes.begin(), selected_indexes.end(), i) != selected_indexes.end()) {
                    std::cout << (count > 0 ? " | " : "") << remove_quotes(row[i]);
                    count++;
                }
            }
            std::cout << std::endl;
        }

        file.close();
        return "";
    };
};