#ifndef PARSER_HPP
#define PARSER_HPP

#include "Macros.hpp"
#include <iostream>
#include <string>
#include <filesystem>
#include <unordered_set>
#include <fstream>
class Parser
{
private:
    std::string _filename;
    std::fstream _file;

    void openFile();
    void error(const std::string &msg);

public:
    Parser(const std::string &filename);
    ~Parser();
    Parser(const Parser &other) = delete;
    Parser operator=(const Parser &other) = delete;

    std::unordered_set<std::string> getAllWords();
    bool validWord(const std::string &word);    

};


#endif