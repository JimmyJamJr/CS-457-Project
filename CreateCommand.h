#pragma once

#include "ICommand.h"

class CreateCommand : public ICommand {
    virtual bool match(std::string input) {
        return false;
    };

    virtual bool execute(std::string input) {
        return false;
    };
};