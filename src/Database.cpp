#include "Database.h"
#include <filesystem>
#include <iostream>

std::string Database::getDatabaseFolder() {
    return std::filesystem::current_path().generic_string() + "/";
}

std::string Database::getDatabase(std::string name) {
    if (std::filesystem::exists(getDatabaseFolder() + name + "/")) {
        return getDatabaseFolder() + name + "/";
    }
    return "";
}

bool Database::createDatabase(std::string name) {
    if (std::filesystem::exists(getDatabaseFolder() + name + "/")) {
        return false;
    }
    std::filesystem::create_directory(getDatabaseFolder() + name + "/");
    return true;
}

bool Database::deleteDatabase(std::string name) {
    if (std::filesystem::exists(getDatabaseFolder() + name + "/")) {
        std::filesystem::remove_all(getDatabaseFolder() + name + "/");
        return true;
    }
    return false;
}