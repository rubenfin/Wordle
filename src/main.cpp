#include "../include/Parser.hpp"
#include "../include/Wordle.hpp"
int main(void)
{
    try
    {
        Wordle wordle;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return FAILURE;
    }
    
    return SUCCES;
}