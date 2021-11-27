#include "Transaction.h"

void Transaction::addModification(std::string table, std::string contents) {
    modified_tables.push_back({table, contents});
}

std::vector<std::pair<std::string, std::string>> Transaction::getModifications() {
    return modified_tables;
}