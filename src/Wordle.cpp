#include "../include/Wordle.hpp"

Wordle::Wordle() : p(new Parser("./words/words.txt"))
{
    parsing();
}

void Wordle::parsing(void)
{
    this->_wordsDictionary = p->getAllWords();
    // printDictionary();
    setCurrentWord();
    printCurrentWord();
}

void Wordle::loop(void)
{
    std::string input;

    while (std::getline(std::cin, input))
    {
        if (!isValidInput(input) || !isWordInDictionary(input))
        {
            std::cout << RED << "Invalid input" << RESET << std::endl;
        }
        
    }
}

Wordle::~Wordle()
{
}

bool Wordle::isValidInput(const std::string &input)
{
    try
    {
        p->validWord(input);
    }
    catch (const std::exception &e)
    {
        return false;
    }
    return true;
}

bool Wordle::isWordCurrentWord(const std::string& word)
{
    return (_currentWord == word);
}

bool Wordle::isWordInDictionary(const std::string& word)
{
    return (_wordsDictionary.count(word));
}

void Wordle::setCurrentWord(void)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, _wordsDictionary.size() - 1);

    size_t random = dist(gen);
    auto it = _wordsDictionary.begin();
    std::advance(it, random);
    _currentWord = *it;
}

void Wordle::printCurrentWord(void)
{
    std::cout << _currentWord << std::endl;
}

void Wordle::printDictionary(void)
{
    for (auto &word : _wordsDictionary)
    {
        std::cout << word << std::endl;
    }
}