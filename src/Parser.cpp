#include "../include/Parser.hpp"

Parser::Parser(const std::string &filename)
{
    std::cout << "Created parser" << std::endl;
    if (!std::filesystem::exists(filename))
        throw std::runtime_error("The file: " + filename + " doesn't exist.");
    _filename = filename;
    openFile();
}

Parser::~Parser()
{
    std::cout << "Destructed parser" << std::endl;
}

bool Parser::validWord(const std::string &word)
{
    size_t length = 0;
    for (auto it = word.begin(); it != word.end(); it++)
    {
        if (!isalpha(*it))
        {
            error("The word: " + word + " - contains a non-alphabetic character");
        }
        length ++;
    }
    if (length != 5)
    {
        error("Length of word: " + word + " - is not equal to 5");
    }
    return true;
}

void Parser::openFile()
{
    _file.open(_filename, std::ios_base::in);
    if (!_file.is_open())
        error("File couldn't be opened");
}


std::unordered_set<std::string> Parser::getAllWords()
{
    std::string line;
    std::unordered_set<std::string> allWords;
    while (std::getline(_file, line))
    {
        try
        {
            validWord(line);
            allWords.insert(line);
        }
        catch (const std::exception &e)
        {
        }
    }
    return allWords;
}

void Parser::error(const std::string &msg)
{
    std::cerr << RED << msg << RESET << std::endl;
    throw std::runtime_error(msg);
}
