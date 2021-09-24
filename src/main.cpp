#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include "Database.h"

#include "CreateCommand.h"

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
    do {
        std::string input;
        std::cout << "# ";
        getline(std::cin, input);
        
        std::string command = to_upper(get_command(input));
        std::string parms = get_parameters(input);

        // std::cout << parms << "\n";

        if (command == ".EXIT") {
            std::cout << "All done.\n";
            quit = true;
        }
        else if (command == "CREATE") {
            std::string type = to_upper(get_command(parms));
            std::string name = get_parameters(parms);
            if (type == "DATABASE") {
                bool success = Database::createDatabase(name);
                std::cout << (success ? "Database " + name + " created." : "!Failed to create database " + name + " because it already exists.") << "\n";
            }
            else if (type == "TABLE") {

            }
            else {
                std::cout << "!CREATE command failed, invalid object type " + type + ".\n";
            }
        }
        else if (command == "DROP") {
            std::string type = to_upper(get_command(parms));
            std::string name = get_parameters(parms);
            if (type == "DATABASE") {
                bool success = Database::deleteDatabase(name);
                std::cout << (success ? "Database " + name + " deleted." : "!Failed to delete database " + name + " because it does not exist.") << "\n";
            }
            else if (type == "TABLE") {

            }
            else {
                std::cout << "!CREATE command failed, invalid object type " + type + ".\n";
            }
        }
        else if (command == "SELECT") {
            
        }
        else if (command == "ALTER") {
            
        }
        else if (command == "USE") {
            
        }
        else {
            std::cout << "Command not recongnized.\n";
        }
    } while (!quit);
}