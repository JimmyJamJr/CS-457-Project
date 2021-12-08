// Jimson Huang
// CS457
// 12/8/2021
// Transaction class for the purposes of storing infomraiton about the current transactions

#pragma once

#include <vector>
#include <string>
#include <tuple>

class Transaction {
    private:
    // Vector for storing a list of tables modified during the transactions and its contents
    std::vector<std::tuple<std::string, std::string, std::vector<std::string>>> modified_tables;

    public:
    // Add a new modification to the modifications list
    void addModification(std::string db, std::string table, std::vector<std::string> contents);
    // Getter for modified_tables
    std::vector<std::tuple<std::string, std::string, std::vector<std::string>>> getModifications();
};