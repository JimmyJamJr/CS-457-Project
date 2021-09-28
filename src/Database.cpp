#include "Database.h"
#include <filesystem>
#include <iostream>

Database::Database(std::string name) {
    // if (!std::filesystem::exists(std::filesystem::current_path().generic_string() + "/" + name + "/")) {
    //     std::filesystem::create_directory(std::filesystem::current_path().generic_string() + "/" + name + "/");
    //     std::cout << "Folder created " << std::filesystem::current_path().generic_string() << "/" << name << "/\n";
    // }
    // else {
    //     std::cout << "Folder exists " << std::filesystem::current_path().generic_string() << "/" << name << "/\n";
    // }
}

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