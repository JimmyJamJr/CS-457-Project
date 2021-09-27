#pragma once

#include <string>
#include <algorithm>
#include <iostream>
#include "Database.h"

class ICommand {
    protected:
    static std::string to_upper(std::string input);
    static std::string get_command(std::string input);
    static std::string get_parameters(std::string input);
    static std::string remove_semicolon(std::string input);

    public:
    virtual bool match(std::string input) = 0;
    virtual std::string execute(std::string input, std::string database = "") = 0;
};