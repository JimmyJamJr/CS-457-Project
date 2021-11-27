#pragma once

#include <vector>
#include <string>
#include <utility>

class Transaction {
    private:
    std::vector<std::pair<std::string, std::string>> modified_tables;

    public:
    void addModification(std::string table, std::string contents);
    std::vector<std::pair<std::string, std::string>> getModifications();
};