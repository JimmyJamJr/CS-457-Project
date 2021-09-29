// Jimson Huang
// CS457
// 9/29/2021
// Interface implemented by all Command classes.

#pragma once

#include <string>
#include <algorithm>
#include <iostream>
#include "Database.h"
#include "Util.h"

class ICommand {
    public:
    // Returns true if the input string contains the prefix for a command.
    virtual bool match(std::string input) = 0;
    // Execution of a command, returns a database folder path if the command 
    // changes the database currently being used.
    virtual std::string execute(std::string input, std::string database = "") = 0;
    // Default destructor
    virtual ~ICommand() = default;
};