#include "Transaction.h"

void Transaction::addModification(std::string db, std::string table, std::vector<std::string> contents) {
    modified_tables.push_back({db, table, contents});
}

std::vector<std::tuple<std::string, std::string, std::vector<std::string>>> Transaction::getModifications() {
    return modified_tables;
}