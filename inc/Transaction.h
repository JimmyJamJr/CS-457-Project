#pragma once

#include <vector>
#include <string>
#include <tuple>

class Transaction {
    private:
    std::vector<std::tuple<std::string, std::string, std::vector<std::string>>> modified_tables;

    public:
    void addModification(std::string db, std::string table, std::vector<std::string> contents);
    std::vector<std::tuple<std::string, std::string, std::vector<std::string>>> getModifications();
};