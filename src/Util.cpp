#include "Util.h"
#include <vector>
#include <string>

std::vector<std::string> split(std::string str, std::string token) {
    std::vector<std::string> result;
    while (str.size()) {
        int index = str.find(token);
        if (index != std::string::npos){
            std::string sub = str.substr(0,index);
            if (sub != "" && sub != "\n")
                result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if (str.size()==0) result.push_back(str);
        }
        else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

std::string first_word(std::string input) {
    std::string word = "";
    int start = 0;
    for (; start < input.length() && (input[start] == ' ' || input[start] == '\n'); start++);
    for (int i = start; i < input.length() && input[i] != ' '; i++) {
        word += input[i];
    }
    return word;
} 

std::string to_upper(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(), toupper);
    return input;
}

std::string remove_semicolon(std::string input) {
    if (input.back() == ';') {
        input.pop_back();
    }
    return input;
}