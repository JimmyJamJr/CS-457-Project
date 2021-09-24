#include "ICommand.h"

std::string ICommand::to_upper(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(), toupper);
    return input;
}

std::string ICommand::get_command(std::string input) {
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

std::string ICommand::get_parameters(std::string input) {
    int index = 0;
    while (index < input.length() && input[index] != ' ') {
        index++;
    }

    if (index >= input.length()) {
        return "";
    }
    return input.substr(index + 1);
}