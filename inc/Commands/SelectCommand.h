// Jimson Huang
// CS457
// 9/29/2021
// Updated 10/19/2021
// Select command for selecting attributes from a table, supports WHERE condition

#pragma once

#include "ICommand.h"
#include <fstream>

class SelectCommand : public ICommand {
    // Check command prefix
    virtual bool match(std::string input) {
        return to_upper(first_word(input)) == "SELECT";
    };

    // void inner_join(std::vector<std::string> parms, std::string database);
    // void outer_join(std::vector<std::string> parms, std::string database);

    // Execute the command
    virtual std::string execute(std::string input, std::string database) {
        std::vector<std::string> parms = split(input);

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

        // Check keywords for joins and deal with separately
        if (input.find(",") != std::string::npos) {
            // Inner join
            inner_join(parms, database);
            return "";
        }
        if (to_upper(input).find("INNER JOIN") != std::string::npos) {
            // Inner join
            inner_join(parms, database);
            return "";
        }
        if (to_upper(input).find("OUTER JOIN") != std::string::npos) {
            // Outer join
            outer_join(parms, database);
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
                    std::cout << (count > 0 ? "|" : "") << remove_quotes(row[i]);
                    count++;
                }
            }
            std::cout << std::endl;
        }

        file.close();
        return "";
    };

    // Function for handling inner joins
    void inner_join(std::vector<std::string> parms, std::string database) {
        int fromIndex = -1;

        std::string attribute_left;
        std::string attribute_right;
        std::string table_left;
        std::string left_var = "";
        std::string table_right;
        std::string right_var = "";

        // Find the indexes of the tables and variables
        for (int i = 0; i < parms.size(); i++) {
            if (to_upper(parms[i]) == "FROM") {
                fromIndex = i;
                // If short-hand inner join
                if (parms[i+2].find(",") != std::string::npos) {
                    table_left = parms[i+1];
                    left_var = parms[i+2].substr(0, parms[i+2].length() - 1);
                    table_right = parms[i+3];
                    right_var = parms[i+4];
                }
                // If full inner join syntax
                else if (to_upper(parms[i+3]) == "INNER" &&  to_upper(parms[i+4]) == "JOIN") {
                    table_left = parms[i+1];
                    left_var = parms[i+2];
                    table_right = parms[i+5];
                    right_var = parms[i+6];
                }
                else {
                    std::cout << "!SELECT command failed. INNER JOIN syntax error." << std::endl;
                    return;
                }
            }
            // Get the attributes being compared
            if (left_var != "" && right_var != "") {
                if (parms[i].find(left_var + ".") != std::string::npos) {
                    attribute_left = parms[i].substr(left_var.length() + 1, parms[i].size() - left_var.length() - 1);
                }
                if (parms[i].find(right_var + ".") != std::string::npos) {
                    attribute_right = parms[i].substr(right_var.length() + 1, parms[i].size() - right_var.length() - 1);
                }
            }
        }
        // If FROM keyword doesn't exist
        if (fromIndex == -1) {
            std::cout << "!SELECT command failed. FROM keyword not found." << std::endl;
            return;
        }
        // If no attributes are given for the join
        if (attribute_right == "" || attribute_left == "") {
            std::cout << "!SELECT command failed. Attributes for INNER JOIN not specified/found." << std::endl;
            return;
        }

        // Schemas for both tables
        std::vector<std::string> schema_left = Table::getSchema(database, table_left);
        std::vector<std::string> schema_right = Table::getSchema(database, table_right);
        if (schema_left.size() == 0 || schema_right.size() == 0) {
            std::cout << "!Failed to query INNER JOIN because one or more tables do not exist." << std::endl;
            return;
        }

        int selected_attribute_left = -1;
        int selected_attribute_right = -1;

        // Find the location in the schmeas of the attributes in the join
        for (int i = 0 ; i < schema_left.size(); i++) {
            if (split(schema_left[i], " ")[0] == attribute_left) {
                selected_attribute_left = i;
            }
        }
        for (int i = 0 ; i < schema_right.size(); i++) {
            if (split(schema_right[i], " ")[0] == attribute_right) {
                selected_attribute_right = i;
            }
        }

        // If attribute not in either schema
        if (selected_attribute_left == -1 || selected_attribute_right == -1) {
            std::cout << "!SELECT command failed. INNER JOIN condition attribute is not in schema." << std::endl;
            return;
        }

        // Read the table files into two vectors
        std::vector<std::vector<std::string>> file_left;
        std::vector<std::vector<std::string>> file_right;
        
        std::string line;
        std::ifstream file = Table::getFile(database, table_left);
        while (getline(file, line)) {
            file_left.push_back(split(line, " | "));
        }
        file.close();
        file = Table::getFile(database, table_right);
        while (getline(file, line)) {
            file_right.push_back(split(line, " | "));
        }
        file.close();

        // Print out the combined schemas of the two tabes
        for (int i = 0; i < schema_left.size(); i++) {
            if (i != 0) {
                std::cout << "|";
            }
            std::cout << schema_left[i];
        }
        for (int i = 0; i < schema_right.size(); i++) {
            std::cout << "|";
            std::cout << schema_right[i];
        }
        std::cout << "\n";

        // For each tuple in the left table, check each tuple in the right tuple. If the attributes are equal, print out 
        // a combined tuple with attributes from both tables
        for (int i = 1; i < file_left.size(); i++) {
            for (int j = 1; j < file_right.size(); j++) {
                if (file_left[i][selected_attribute_left] == file_right[j][selected_attribute_right]) {
                    for (int k = 0; k < file_left[i].size(); k++) {
                        if (k > 0) {
                            std::cout << "|";
                        }
                        std::cout << remove_quotes(file_left[i][k]);
                    }
                    for (int k = 0; k < file_right[i].size(); k++) {
                        std::cout << "|";
                        std::cout << remove_quotes(file_right[j][k]);
                    }
                    std::cout << std::endl;
                }
            }
        }

    };

    // Function for handling left outer joins
    void outer_join(std::vector<std::string> parms, std::string database) {
        int fromIndex = -1;
        std::string attribute_left;
        std::string attribute_right;
        std::string table_left;
        std::string left_var = "";
        std::string table_right;
        std::string right_var = "";

        // Find the indexes of keywords, table names, and variables
        for (int i = 0; i < parms.size(); i++) {
            if (to_upper(parms[i]) == "FROM") {
                fromIndex = i;
                if (to_upper(parms[i+3]) == "LEFT" &&  to_upper(parms[i+4]) == "OUTER" && to_upper(parms[i+5]) == "JOIN") {
                    table_left = parms[i+1];
                    left_var = parms[i+2];
                    table_right = parms[i+6];
                    right_var = parms[i+7];
                }
                else {
                    std::cout << "!SELECT command failed. OUTER JOIN syntax error." << std::endl;
                    return;
                }
            }
            // Find the attributes to be compared
            if (left_var != "" && right_var != "") {
                if (parms[i].find(left_var + ".") != std::string::npos) {
                    attribute_left = parms[i].substr(left_var.length() + 1, parms[i].size() - left_var.length() - 1);
                }
                if (parms[i].find(right_var + ".") != std::string::npos) {
                    attribute_right = parms[i].substr(right_var.length() + 1, parms[i].size() - right_var.length() - 1);
                }
            }
        }
        // If missing the FROM keyword
        if (fromIndex == -1) {
            std::cout << "!SELECT command failed. FROM keyword not found." << std::endl;
            return;
        }
        // If attributes not specified for the join
        if (attribute_right == "" || attribute_left == "") {
            std::cout << "!SELECT command failed. Attributes for OUTER JOIN not specified/found." << std::endl;
            return;
        }

        // Get schema of both tables
        std::vector<std::string> schema_left = Table::getSchema(database, table_left);
        std::vector<std::string> schema_right = Table::getSchema(database, table_right);
        if (schema_left.size() == 0 || schema_right.size() == 0) {
            std::cout << "!Failed to query OUTER JOIN because one or more tables do not exist." << std::endl;
            return;
        }

        // Find the position in the schema of the slected attributes
        int selected_attribute_left = -1;
        int selected_attribute_right = -1;

        for (int i = 0 ; i < schema_left.size(); i++) {
            if (split(schema_left[i], " ")[0] == attribute_left) {
                selected_attribute_left = i;
            }
        }
        for (int i = 0 ; i < schema_right.size(); i++) {
            if (split(schema_right[i], " ")[0] == attribute_right) {
                selected_attribute_right = i;
            }
        }
        // If join attribute not in schema
        if (selected_attribute_left == -1 || selected_attribute_right == -1) {
            std::cout << "!SELECT command failed. OUTER JOIN condition attribute is not in schema." << std::endl;
            return;
        }


        // Read both table files into vectors
        std::vector<std::vector<std::string>> file_left;
        std::vector<std::vector<std::string>> file_right;

        std::string line;
        std::ifstream file = Table::getFile(database, table_left);
        while (getline(file, line)) {
            file_left.push_back(split(line, " | "));
        }
        file.close();
        file = Table::getFile(database, table_right);
        while (getline(file, line)) {
            file_right.push_back(split(line, " | "));
        }
        file.close();

        // Print out combined schema
        for (int i = 0; i < schema_left.size(); i++) {
            if (i != 0) {
                std::cout << "|";
            }
            std::cout << schema_left[i];
        }
        for (int i = 0; i < schema_right.size(); i++) {
            std::cout << "|";
            std::cout << schema_right[i];
        }
        std::cout << "\n";

        // For each tuple in the left table, look through all tuples in the right table. If attributes are equal, print out combined tuple
        // with attributes of both tables. If no mathces are found, print out the left tuple anyways with null values for the attributes of the
        // right table.
        for (int i = 1; i < file_left.size(); i++) {
            int matches = 0;
            for (int j = 1; j < file_right.size(); j++) {
                if (file_left[i][selected_attribute_left] == file_right[j][selected_attribute_right]) {
                    matches++;
                    for (int k = 0; k < file_left[i].size(); k++) {
                        if (k > 0) {
                            std::cout << "|";
                        }
                        std::cout << remove_quotes(file_left[i][k]);
                    }
                    for (int k = 0; k < file_right[i].size(); k++) {
                        std::cout << "|";
                        std::cout << remove_quotes(file_right[j][k]);
                    }
                    std::cout << std::endl;
                }
            }
            if (matches == 0) {
                for (int k = 0; k < file_left[i].size(); k++) {
                    if (k > 0) {
                        std::cout << "|";
                    }
                    std::cout << remove_quotes(file_left[i][k]);
                }
                for (int k = 0; k < schema_right.size(); k++) {
                    std::cout << "|";
                }
                std::cout << std::endl;
            }
        }
    };
};