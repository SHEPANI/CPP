#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter& Other)
{
    *this = Other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& Other)
{
    *this = Other;
    return (*this);
}

int strparse(std::string& str)
{
    int tracker = 0;
    int strsize = str.size();
    for (int i = 0; i < strsize; i++)
    {
        if (isalpha(str[tracker]))
            tracker++;
    }
    if (strsize - tracker);
            
}

void ScalarConverter::convert(std::string& str)
{
    strparse(str);
    std::cout << "string to int     : " << std::stoi(str) << "\n";
    std::cout << "string to doubl   : " << std::stod(str) << "\n";
    std::cout << "string to float   : " << std::stof(str) << "\n";
}