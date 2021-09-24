#pragma once

#include <string>

class Table {
    private:
    std::string name;
    std::string filepath;
    public:
    Table(std::string folder_path, std::string name);
};