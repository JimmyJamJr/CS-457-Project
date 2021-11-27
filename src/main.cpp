// Jimson Huang
// CS457
// 9/29/2021
// Updated 10/19/2021
// Main file of the program, accepts command line input or
// .sql file.

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <filesystem>
#include "Database.h"
#include "Transaction.h"

#include "Commands.h"

// Create list of commands currently support by the program
std::shared_ptr<ICommand> commands[] = {
    std::make_shared<CreateCommand>(),
    std::make_shared<DropCommand>(),
    std::make_shared<UseCommand>(),
    std::make_shared<SelectCommand>(),
    std::make_shared<AlterCommand>(),
    std::make_shared<InsertCommand>(),
    std::make_shared<DeleteCommand>(),
    std::make_shared<UpdateCommand>(),
    std::make_shared<BeginCommand>(),
    std::make_shared<CommitCommand>()
};

// Fuction to check a string for possible commands or exit, returns true if exit condition reached
bool processString(std::string entry, std::string & current_database, std::shared_ptr<Transaction> & current_transaction) {
    // Skip comments and blank lines
    if (std::all_of(entry.begin(), entry.end(), ::isspace)) {
        return false;
    }
    if (entry.substr(0, 2) == "--") return false;

    // Check for exit condition
    if (entry.find(".exit") != std::string::npos || entry.find(".EXIT") != std::string::npos) {
        std::cout << "All done.\n";
        return true;
    }
    else {
        bool recongnized = false;
        // Iterate through commands and look for a matching command to execute
        for (std::shared_ptr<ICommand> cmd : commands) {
            if (cmd->match(entry)) {
                std::pair<std::string, std::shared_ptr<Transaction>> output = cmd->execute(entry, current_database, current_transaction);
                if (output.first != "") {
                    current_database = output.first;
                }
                if (output.second != nullptr) {
                    current_transaction = output.second;
                }
                recongnized = true;
                break; // Stop looking once command is found
            }
        }

        if (!recongnized) {
            std::cout << "Command \"" + entry + "\" not recongnized.\n";
        }
    }
    return false;
}

int main(int ac, char** av) {
    bool quit = false;

    // Current database being used
    std::string current_database = "";

    std::shared_ptr<Transaction> current_transaction = nullptr;

    // Handling the case of an entire .sql file
    if (ac > 1) {
        std::ifstream sql;
        std::string filename(av[1]);
        // Check the existence of the sql file
        if (std::filesystem::exists(filename)) {
            sql = std::ifstream(filename);
        }
        else {
            std::cout << "!Can't open file " << filename << " because it doens't exist." << std::endl;
            return 1;
        }
        // Read entire file into content string
        std::string content((std::istreambuf_iterator<char>(sql)), (std::istreambuf_iterator<char>()));
        // Split input by ; into a list of commands
        std::vector<std::string> input_vec = split(remove_all_comments(content), ";");
        for (std::string entry : input_vec) {
            // Process the string after removing leading comments and whitespace
            processString(remove_ws(remove_comments(remove_ws(entry))), current_database, current_transaction);
        }

        sql.close();
    }
    // Handling the case of manually entered commands
    else {
        // Repeat until program exit command is encountered
        do {
            std::string input = "";
            
            std::cout << "SQLit> ";
            // Skip whitespace lines
            while (std::all_of(input.begin(), input.end(), isspace))
                getline(std::cin, input);

            // Split input by ; into a list of commands
            std::vector<std::string> input_vec = split(input, ";");
            for (std::string entry : input_vec) {
                // Process the string after removing leading comments and whitespace
                quit = processString(remove_comments(remove_ws(entry)), current_database, current_transaction);
            }
            

        } while (!quit);
    }
}