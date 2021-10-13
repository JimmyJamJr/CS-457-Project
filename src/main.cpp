// Jimson Huang
// CS457
// 9/29/2021
// Main file of the program, accepts command line input or
// .sql file.

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <filesystem>
#include "Database.h"

#include "Commands.h"

int main(int ac, char** av) {
    bool quit = false;

    // Create list of commands currently support by the program
    std::shared_ptr<ICommand> commands[] = {
        std::make_shared<CreateCommand>(),
        std::make_shared<DropCommand>(),
        std::make_shared<UseCommand>(),
        std::make_shared<SelectCommand>(),
        std::make_shared<AlterCommand>(),
        std::make_shared<InsertCommand>(),
        std::make_shared<DeleteCommand>()
    };

    // Current database being used
    std::string current_database = "";

    // Check the command line argument for file input
    std::ifstream sql;
    if (ac > 1) {
        std::string filename(av[1]);
        if (std::filesystem::exists(filename)) {
            sql = std::ifstream(filename);
        }
        else {
            std::cout << "!Can't open file " << filename << " because it doens't exist." << std::endl;
            return 1;
        }
    }

    // Repeat until program exit command is encountered
    do {
        std::string input = "";
        if (ac > 1 && getline(sql, input)) {

        }
        else {
            std::cout << "SQLit> ";
            // Skip whitespace lines
            while (std::all_of(input.begin(), input.end(), isspace))
                getline(std::cin, input);
        }

        // Split input by ; into a list of commands
        std::vector<std::string> input_vec = split(input, ";");
        for (std::string entry : input_vec) {
            // Skip comments and blank lines
            if (std::all_of(entry.begin(), entry.end(), isspace)) {
                continue;
            }
            if (entry.substr(0, 2) == "--") continue;

            // Check for exit condition
            if (entry.find(".exit") != std::string::npos || entry.find(".EXIT") != std::string::npos) {
                std::cout << "All done.\n";
                quit = true;
            }
            else {
                bool recongnized = false;
                // Iterate through commands and look for a matching command to execute
                for (std::shared_ptr<ICommand> cmd : commands) {
                    if (cmd->match(entry)) {
                        std::string output = cmd->execute(entry, current_database);
                        if (output != "") {
                            current_database = output;
                        }
                        recongnized = true;
                        break;
                    }
                }

                if (!recongnized) {
                    std::cout << "Command not recongnized.\n";
                }
            }
        }
        

    } while (!quit);
    
    // Close sql file if opened
    if (ac > 1) {
        sql.close();
    }
}