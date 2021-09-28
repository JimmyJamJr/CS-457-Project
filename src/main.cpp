#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include "Database.h"

#include "Commands/CreateCommand.h"
#include "Commands/DropCommand.h"
#include "Commands/UseCommand.h"

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
        std::vector<std::string> input_vec = split(input, ";");

        for (std::string entry : input_vec) {
            if (entry == " " || entry == "\n" || entry == "") continue;
            if (entry.substr(0, 2) == "--") continue;
            if (entry == ".exit" || entry == ".EXIT") {
                std::cout << "All done.\n";
                quit = true;
            }
            else {
                bool recongnized = false;
                for (ICommand * cmd : commands) {
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
}