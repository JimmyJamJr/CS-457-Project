#pragma once

#include <queue>
#include <string>

class Transaction {
    private:
    std::queue<std::string> commands;

    public:
    void add(std::string command);
    std::queue<std::string> getCommands();
};