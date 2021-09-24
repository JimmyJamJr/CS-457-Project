#include "Table.h"
#include <fstream>
#include <iostream>

Table::Table(std::string _folder_path, std::string _name) {
    name = _name;
    std::fstream file;
    file.open(_folder_path + _name, std::fstream::app);
}