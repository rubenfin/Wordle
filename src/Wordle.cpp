#include "../include/Wordle.hpp"

Wordle::Wordle() : _p(new Parser("./words/words.txt")), _totalGuesses(0)
{
    std::cout << "W   W    OOO    RRRR    DDDD   L      EEEEE\n";
    std::cout << "W   W   O   O   R   R   D   D  L      E    \n";
    std::cout << "W W W   O   O   RRRR    D   D  L      EEEE \n";
    std::cout << "WW WW   O   O   R  R    D   D  L      E    \n";
    std::cout << "W   W    OOO    R   R   DDDD   LLLLL  EEEEE\n";
    std::cout << "\n\n" << std::endl;
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
        try {
         _p->validWord(input);
         isWordInDictionary(input);
        }
        catch (const std::exception &e)
        {
            std::cerr << RED << e.what() << RESET << std::endl;
            std::cout <<  "input: ";
            continue ;
        }
        if (isWordCurrentWord(input))
        {
            printAllGuesses();
            std::cout << "Congratulations you found the word: " << _currentWord << " in " << _totalGuesses + 1 << " guesses!"<< std::endl;
            return ;
        }
        _guesses[_totalGuesses] = doesWordHaveSameCharacters(input);
        _totalGuesses++;
        printAllGuesses();
        if (_totalGuesses == 5)
        {
            std::cout << RED << "GAME OVER ! The word was: "<< _currentWord << RESET << std::endl;
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

bool Wordle::isWordCurrentWord(const std::string& word)
{
    if (_currentWord != word) { return false;}
    
    _guesses[_totalGuesses] = GREEN + word + RESET;
    return true;
}

std::string Wordle::doesWordHaveSameCharacters(const std::string& word)
{
    std::vector<std::string> guess(5, "_");
    std::vector<bool> matched(_currentWord.size(), false);
    
    for (size_t i = 0; i < word.size(); i++)
    {
        if (word[i] == _currentWord[i])
        {
            guess[i] = GREEN + std::string(1, word[i]) + RESET;
            matched[i] = true;
        }
    }

    for (size_t i = 0; i < word.size(); i++)
    {
        if (guess[i] != "_") continue;
        bool found = false;

        for (size_t j = 0; j < _currentWord.size(); j++)
        {
            if (!matched[j] && word[i] == _currentWord[j])
            {
                found = true;
                matched[j] = true;
            }
        }
        if (found)
            guess[i] = YELLOW + std::string(1, word[i]) + RESET;
        else
            guess[i] = std::string(1, word[i]);
    }
    std::string total;
    for (auto &s : guess)
    {
        total += s;
    }
    return (total);
}

void Wordle::isWordInDictionary(const std::string& word)
{
    _wordsDictionary.count(word) ? 0 : throw std::runtime_error("This word is not in the dictionary");
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