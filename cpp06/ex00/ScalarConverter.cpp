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

void stringToChar(std::string& currStr)
{
    int s = (currStr[0]);
    if (s < 32 || s > 126)
    {
        if (s > 127 || s < 0)
            std::cout << "impossible\n";
        else
            std::cout << "Non displayable\n";
    }
    else
        std::cout << char(s) << "\n";
}

void stringToInt(std::string& currStr)
{
    if (currStr[1])
        std::cout << std::stoi(currStr) << "\n";
    else
        std::cout << int(currStr[0]) << "\n";
}

void stringToDouble(std::string& currStr)
{
    
    std::cout << std::fixed << std::setprecision(1) << std::stod(currStr) << "\n";
}

void stringToFloat(std::string& currStr)
{
    
    std::cout << std::fixed << std::setprecision(1) << std::stof(currStr) << "f\n";
}

void invalidInput(std::string& currStr)
{
    std::cout << currStr << " input is not valid\n";
}

int strparse(std::string& str)
{
    int fdtracker = 0;
    int numtracker = 0;
    int strsize = str.size();

    if (strsize==1 && std::isalpha(str[0]))
        return (1);

    if (str[0] == '.' || str[strsize-1]=='.' || str[0]=='f')
        return(0);

    if (str[0] == '+' || str[0] == '-')
        numtracker++;

    for (int i = 0; i < strsize;i++)
    {
        if (std::isdigit(str[i]))
            numtracker++;
        if ((str[i] == '.'))
            fdtracker++;
    }

    if (numtracker == strsize)
        return (2);
    if (fdtracker == 1 && numtracker == strsize -1)
        return (3);
    if (fdtracker == 1 && numtracker == strsize -2 
            && str[strsize-1]=='f' && str[strsize-2]!='.')
        return (4);

    return(0);
}


void ScalarConverter::convert(std::string& str)
{
    int exactype = strparse(str);
    void (*ptrToMemberFunc[])(std::string& currStr)={
        &invalidInput,
        &stringToChar,
        &stringToInt,
        &stringToDouble,
        &stringToFloat
    };
    try
    {
        if (exactype != 0)
        {
            ptrToMemberFunc[1](str);
            ptrToMemberFunc[2](str);
            ptrToMemberFunc[3](str);
            ptrToMemberFunc[4](str);
        }
        else
            ptrToMemberFunc[exactype](str);
    }
    catch(const std::overflow_error& e)
    {
        std::cerr << e.what() << " overflow_error" << '\n';
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << " out_of_range" << '\n';
    }
}