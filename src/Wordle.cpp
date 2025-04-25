#include "../include/Wordle.hpp"

Wordle::Wordle() : _p(new Parser("./words/words.txt")), _totalGuesses(0)
{
    parsing();
    loop();
}

void Wordle::parsing(void)
{
    for (size_t i = 0; i < _guesses.size(); i++)
    {
        _guesses[i] = "_____";
    }

    this->_wordsDictionary = _p->getAllWords();
    std::cout << "Total amount of words: " << this->_wordsDictionary.size() << "\n" << std::endl;
    // printDictionary();
    setCurrentWord();
    // printCurrentWord();
}

void Wordle::loop(void)
{
    std::string input;

    // printAllGuesses();
    std::cout << "input: ";
    while (std::getline(std::cin, input))
    {
        std::cout << std::endl;
        if (input == "quit" || input == "QUIT")
        {
            std::cout << "Thank you for playing!" << std::endl; 
            return ;
        }
            if (!isValidInput(input) || !isWordInDictionary(input))
        {
            std::cout << RED << "Invalid input" << RESET << std::endl;
            std::cout << "input: ";
            continue ;
        }

        if (isWordCurrentWord(input))
        {
            printAllGuesses();
            std::cout << "Congratulations you won!" << std::endl;
            return ;
        }
        _guesses[_totalGuesses] = doesWordHaveSameCharacters(input);
        _totalGuesses++;
        printAllGuesses();
        if (_totalGuesses == 5)
        {
            std::cout << RED << "GAME OVER !" << RESET << std::endl;
            return;
        }
        std::cout << "input: ";
    }
}

Wordle::~Wordle()
{
}

void Wordle::printAllGuesses(void)
{
    for (auto& guess : _guesses)
    {
        std::cout << guess << std::endl;
    }
    std::cout << std::endl;
}

bool Wordle::isValidInput(const std::string &input)
{
    try
    {
        _p->validWord(input);
    }
    catch (const std::exception &e)
    {
        return false;
    }
    return true;
}


bool Wordle::isWordCurrentWord(const std::string& word)
{
    if (_currentWord != word) { return false;}
    
    _guesses[_totalGuesses] = GREEN + word + RESET;
    return true;
}

std::string Wordle::doesWordHaveSameCharacters(const std::string& word)
{
    std::string guess;
    for (size_t i = 0; i < word.size(); i++)
    {
        if (_currentWord[i] == word[i])
        {
            guess += GREEN + std::string(1, word[i]) + RESET;
        }
        else if (_currentWord.find(word[i]) != std::string::npos)
        {
            guess += YELLOW + std::string(1, word[i]) + RESET;
        }
        else
            guess += word[i];
    }
    return guess;
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
    std::cout << "Current word: " << _currentWord << std::endl;
}

void Wordle::printDictionary(void)
{
    for (auto &word : _wordsDictionary)
    {
        std::cout << word << std::endl;
    }
}