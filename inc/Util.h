// Jimson Huang
// CS457
// 9/29/2021
// Updated 10/19/2021
// Utility header with functions mostly needed for easier string manipulation.

#pragma once

#include <vector>
#include <string>

// Splits a string into a vector of strings given a token as delimitor.
std::vector<std::string> split(std::string str, std::string token);
// Splits a string into a vector of strings by whitespace
std::vector<std::string> split(std::string const &input);
// Returns all characters of a string until the first space.
std::string first_word(std::string);
// Changes all lower case letters to upper case in a string.
std::string to_upper(std::string input);
// Changes all upper case letters to lower case in a string.
std::string to_lower(std::string input);
// Remove a trailing semicolon in a string, if it exists.
std::string remove_semicolon(std::string input);
// Remove quotes surrounding a string, if it exists
std::string remove_quotes(std::string input);
// Removes all whitespace at the begining of a string
std::string remove_ws(std::string input);
// Removes all comments at the begining of a string
std::string remove_comments(std::string input);
// Removes all '(' and ')' characters from a string
std::string remove_parenthesis(std::string input);