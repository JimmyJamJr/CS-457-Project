#pragma once

#include <string>
#include <algorithm>

class ICommand {
    protected:
    static std::string to_upper(std::string input);
    static std::string get_command(std::string input);
    static std::string get_parameters(std::string input);

    public:
    virtual bool match(std::string input) = 0;
    virtual bool execute(std::string input) = 0;
};