#include "../include/Parser.hpp"

Parser::Parser(const std::string &filename)
{
    std::cout << "Created parser" << std::endl;
}

Parser::~Parser()
{
    std::cout << "Destructed parser" << std::endl;
}

bool Parser::validWord(std::string word)
{
    size_t length = 0;
    for (auto it = word.begin(); it != word.end(); it++)
    {
        if (!isalpha(*it))
        {
            std::cerr << RED << "The word: " << word << "contains a non-alphabetic character" << RESET << std::endl;
            return false;
        }
        length ++;
    }
    if (length != 5)
    {
        std::cerr << RED << "Length of word: " << word << " - is not equal to 5" << RESET << std::endl;
        return false;
    }
    return true;
}

void 