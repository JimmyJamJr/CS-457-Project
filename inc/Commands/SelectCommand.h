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

        if (database == "") {
            std::cout << "!SELECT command failed. No database is being used." << std::endl;
            return "";
        }

        int fromIndex = -1;
        for (int i = 0; i < parms.size(); i++) {
            if (to_upper(parms[i]) == "FROM") {
                fromIndex = i;
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