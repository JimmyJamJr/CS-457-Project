#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <filesystem>
#include "Database.h"

#include "Commands/CreateCommand.h"
#include "Commands/DropCommand.h"
#include "Commands/UseCommand.h"
#include "Commands/SelectCommand.h"
#include "Commands/AlterCommand.h"

int main(int ac, char** av) {
    bool quit = false;

    ICommand * commands[] = {
        new CreateCommand(),
        new DropCommand(),
        new UseCommand(),
        new SelectCommand(),
        new AlterCommand()
    };

    std::string current_database = "";

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

    do {
        std::string input;
        if (ac > 1 && getline(sql, input)) {

        }
        else {
            std::cout << "SQLit> ";
            getline(std::cin, input);
        }

        std::vector<std::string> input_vec = split(input, ";");
        for (std::string entry : input_vec) {
            if (entry.substr(0, 2) == "--") continue;
            if (entry == " " || entry == "\n" || entry == "" || entry == "\r") continue;
            if (entry.find(".exit") != std::string::npos || entry.find(".EXIT") != std::string::npos) {
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

    if (ac > 1) {
        sql.close();
    }
}