#pragma once

#include <string>
#include <algorithm>
#include <iostream>
#include "Database.h"
#include "Util.h"

class ICommand {
    public:
    virtual bool match(std::string input) = 0;
    virtual std::string execute(std::string input, std::string database = "") = 0;
};