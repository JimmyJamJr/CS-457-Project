// Jimson Huang
// CS457
// 9/29/2021
// Updated 10/19/2021
// See header for description.

#include "Util.h"
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>

std::vector<std::string> split(std::string str, std::string token) {
    std::vector<std::string> result;
    while (str.size()) {
        // Gets the substring up until the first occurance of the token, then
        // ff the substring is not blankspace, add it to the output vector
        // and remove it from the input string. Repeat until the input
        // string is empty.
        int index = str.find(token);
        if (index != std::string::npos){
            std::string sub = str.substr(0,index);
            if (sub != "" && sub != "\n")
                result.push_back(str.substr(0, index));
            str = str.substr(index+token.size());
            if (str.size() == 0) result.push_back(str);
        }
        else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

std::vector<std::string> split(std::string const &input) { 
    std::istringstream buffer(input);
    std::vector<std::string> vec((std::istream_iterator<std::string>(buffer)), 
                                 std::istream_iterator<std::string>());
    return vec;
}

std::string first_word(std::string input) {
    std::string word = "";
    int start = 0;
    // Skip all whitespace in the begging of the input
    for (; start < input.length() && (input[start] == ' ' || input[start] == '\n'); start++);
    // Add letters to output string until a space is reached
    for (int i = start; i < input.length() && input[i] != ' '; i++) {
        word += input[i];
    }
    return word;
} 

std::string to_upper(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    return input;
}

std::string to_lower(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

std::string remove_semicolon(std::string input) {
    if (input.back() == ';') {
        input.pop_back();
    }
    return input;
}

std::string remove_quotes(std::string input) {
    std::string output = "";
    for (char c : input) {
        if (c != '\'') {
            output += c;
        }
    }
    return output;
}

std::string remove_ws(std::string input) {
    // Skips over spaces in the begining then append the rest to output string
    int i = 0;
    for (; i < input.length(); i++) {
        if (!isspace(input[i])) break;
    }
    return input.substr(i, input.length() - i);
}

std::string remove_comments(std::string input) {
    // Check for comments at the begining
    if (input[0] == '-' && input[1] == '-') {
        int cmdStart = -1;
        // Find the start of the actual command
        for (int i = 0; i < input.length() - 1; i++) {
            if (input[i] == '\n') {
                cmdStart = i + 1;
            }
        }
        if (cmdStart != -1) {  
            return input.substr(cmdStart, input.length() - cmdStart);
        }
        else {
            return "";
        }
        
    }
    else {
        return input;
    }
}

std::string remove_parenthesis(std::string input) {
    std::string output = "";
    for (char c : input) {
        if (c != '(' && c != ')') {
            output += c;
        }
    }
    return output;
}

std::string remove_all_comments(std::string input) {
    std::string output = "";
    std::vector<std::string> lines = split(input, "\n");
    for (auto line : lines) {
        if (line[0] == '-' && line[1] == '-') {
            continue;
        }
        output += line + "\n";
    }
    return output;
}