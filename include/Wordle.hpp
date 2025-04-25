# ifndef WORDLE_HPP
# define WORDLE_HPP

#include "Parser.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <random>

class Wordle
{
private:
    std::string _currentWord;
    std::unordered_set<std::string> _wordsDictionary;
    std::shared_ptr<Parser> p; 
    void parsing(void);
    void loop(void);
public:
    Wordle();
    ~Wordle();

    bool isValidInput(const std::string &input);
    void setCurrentWord(void);
    bool isWordCurrentWord(const std::string& word);
    bool isWordInDictionary(const std::string& word);
    void printDictionary(void);
    void printCurrentWord(void);
};

# endif 