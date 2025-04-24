#ifndef PARSER_HPP
#define PARSER_HPP

#include "Wordle.hpp"
#include <iostream>
#include <string>

class Parser
{
private:
    std::vector<std::string> _words;
    std::string _filename;

protected:
    Parser(const std::string &filename);
    ~Parser();
    bool validWord(std::string word);    
    std::vector<std::string> getAllWords();
};


#endif