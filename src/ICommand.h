#pragma once

#include <string>

class ICommand {
    protected:
    static std::string to_upper(std::string input) {
        std::transform(input.begin(), input.end(), input.begin(), toupper);
        return input;
    };

    static std::string get_command(std::string input) {
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
    };

    static std::string get_parameters(std::string input) {
        int index = 0;
        while (index < input.length() && input[index] != ' ') {
            index++;
        }

        if (index >= input.length()) {
            return "";
        }
        return input.substr(index + 1);
    }

    public:
    virtual bool match(std::string input) = 0;
    virtual bool execute(std::string input) = 0;
};