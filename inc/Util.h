// Jimson Huang
// CS457
// 9/29/2021
// Utility header with functions mostly needed for easier string manipulation.

#pragma once

#include <vector>
#include <string>

// Splits a string into a vector of strings given a token as delimitor.
std::vector<std::string> split(std::string str, std::string token);
// Returns all characters of a string until the first space.
std::string first_word(std::string);
// Changes all lower case letters to upper case in a string.
std::string to_upper(std::string input);
// Remove a trailing semicolon in a string, if it exists.
std::string remove_semicolon(std::string input);