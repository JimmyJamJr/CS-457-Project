// Jimson Huang
// CS457
// 9/29/2021
// Interface implemented by all Command classes.

#pragma once

#include <string>
#include <algorithm>
#include <iostream>
#include <utility>
#include "Database.h"
#include "Util.h"

class ICommand {
    public:
    const std::pair<std::string, std::shared_ptr<Transaction>> default_return;
    ICommand() : default_return("", nullptr) {};
    
    // Returns true if the input string contains the prefix for a command.
    virtual bool match(std::string input) = 0;
    // Execution of a command, returns a database folder path if the command 
    // changes the database currently being used. Also returns a pointer to a transaction
    // if the command starts an new transaction.
    virtual std::pair<std::string, std::shared_ptr<Transaction>> execute(std::string input, std::string database = "", std::shared_ptr<Transaction> transaction = nullptr) = 0;
    // Default destructor
    virtual ~ICommand() = default;
};