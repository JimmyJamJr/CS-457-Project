#include "Transaction.h"

void Transaction::add(std::string command) {
    commands.push(command);
}

std::queue<std::string> Transaction::getCommands() {
    return commands;
}