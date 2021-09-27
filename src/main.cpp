#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include "Database.h"

#include "Commands/CreateCommand.h"
#include "Commands/DropCommand.h"
#include "Commands/UseCommand.h"

std::string get_command(std::string input) {
    std::string command = "";
    for (char c : input) {
        if (c != ' ') {
            command += c;
        }
        else {
            return command;
        }
    }
    return command;
}

std::string get_parameters(std::string input) {
    int index = 0;
    while (index < input.length() && input[index] != ' ') {
        index++;
    }

    if (index >= input.length()) {
        return "";
    }
    return input.substr(index + 1);
}

std::string to_upper(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(), toupper);
    return input;
}

int main() {
    bool quit = false;

    ICommand * commands[] = {
        new CreateCommand(),
        new DropCommand(),
        new UseCommand()
    };

    std::string current_database = "";

    do {
        std::string input;
        std::cout << "# ";
        getline(std::cin, input);
    
        if (input == ".exit" || input == ".EXIT") {
            std::cout << "All done.\n";
            quit = true;
        }
        else {
            bool recongnized = false;
            for (ICommand * cmd : commands) {
                if (cmd->match(input)) {
                    std::string output = cmd->execute(input, current_database);
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

    } while (!quit);
}