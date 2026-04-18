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

void ScalarConverter::convert(std::string& str)
{
    std::cout << "string to int     : " << std::stoi(str) << "\n";
    std::cout << "string to doubl   : " << std::stod(str) << "\n";
    std::cout << "string to float   : " << std::stof(str) << "\n";
}