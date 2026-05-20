#include "ScalarConverter.hpp"

#include <cmath>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <cerrno>
#include <cctype>

enum possibleTypes
{
    TYPE_INVALID,
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_PSEUDO
};

static bool isPseudoStr(const std::string &str)
{
    return (str == "nan" || str == "+inf" || str == "-inf"
         || str == "nanf" || str == "+inff" || str == "-inff");
}

static bool isCharStr(const std::string &str)
{
    return (str.size() == 1 && !std::isdigit(str[0]));
}

static bool isDecimalStr(const std::string &str)
{
    size_t i = 0;
    size_t strSize = str.size();
    bool Digit = false;
    bool Dot = false;

    if (str.empty())
        return false;
    if (str[i] == '+' || str[i] == '-')
        ++i;
    if (i == strSize)
        return false;
    for (; i < strSize; ++i)
    {
        if (str[i] == '.')
        {
            if (Dot)
                return false;
            Dot = true;
        }
        else if (std::isdigit(str[i]))
            Digit = true;
        else
            return false;
    }
    return (Digit && Dot);
}

static bool isIntStr(const std::string &str)
{
    size_t i = 0;
    size_t strSize = str.size();

    if (str.empty())
        return false;
    if (str[i] == '+' || str[i] == '-')
        ++i;
    if (i == strSize)
        return false;
    for (; i < strSize; ++i)
    {
        if (!std::isdigit(str[i]))
            return false;
    }
    return true;
}

static bool isFloatStr(const std::string &str)
{
    size_t strSize = str.size();
    if (strSize < 2 || str[strSize - 1] != 'f')
        return false;
    std::string numberOnly = str.substr(0, strSize - 1);
    return (isDecimalStr(numberOnly) || isIntStr(numberOnly));
}

static bool isDoubleStr(const std::string &str)
{
    return isDecimalStr(str);
}

static possibleTypes detectType(const std::string &str)
{
    if (isPseudoStr(str))
        return TYPE_PSEUDO;
    if (isCharStr(str))
        return TYPE_CHAR;
    if (isIntStr(str))
        return TYPE_INT;
    if (isFloatStr(str))
        return TYPE_FLOAT;
    if (isDoubleStr(str))
        return TYPE_DOUBLE;
    return TYPE_INVALID;
}


static std::string formatDoubleOrFloat(double value, char currType)
{
    std::ostringstream oss;

    if (std::isnan(value))
        return (currType == 'd' ? "nan" : "nanf");
    if (std::isinf(value))
        return (currType == 'd'
            ? (value < 0.0 ? "-inf" : "+inf")
            : (value < 0.0 ? "-inff" : "+inff"));

    double integerPart;
    if (std::modf(value, &integerPart) == 0.0)
        oss << std::fixed << std::setprecision(1) << value;
    else
        oss << value;
    if (currType == 'f')
        oss << 'f';

    return oss.str();
}

static void printChar(double value)
{
    std::cout << "char: ";
    if (std::isnan(value) || std::isinf(value) || value < 0.0 || value > 127.0)
    {
        std::cout << "impossible\n";
        return;
    }
    char c = static_cast<char>(value);
    if (c < 32 || c > 126)
        std::cout << "Non displayable\n";
    else
        std::cout << '\'' << c << '\'' << "\n";
}

static void printInt(double value)
{
    std::cout << "int: ";
    if (std::isnan(value) || std::isinf(value)
        || value < static_cast<double>(std::numeric_limits<int>::min())
        || value > static_cast<double>(std::numeric_limits<int>::max()))
    {
        std::cout << "impossible\n";
        return;
    }
    std::cout << static_cast<int>(value) << "\n";
}

static void printFloat(double value)
{
    std::cout << "float: ";
    if (std::isnan(value))
    {
        std::cout << "nanf\n";
        return;
    }
    if (std::isinf(value))
    {
        std::cout << (value < 0.0 ? "-inff" : "+inff") << "\n";
        return;
    }
    if (value < static_cast<double>(-std::numeric_limits<float>::max())
        || value > static_cast<double>(std::numeric_limits<float>::max()))
    {
        std::cout << "impossible\n";
        return;
    }
    std::cout << formatDoubleOrFloat(static_cast<float>(value), 'f') << "\n";
}

static void printDouble(double value)
{
    std::cout << "double: ";
    if (std::isnan(value))
    {
        std::cout << "nan\n";
        return;
    }
    if (std::isinf(value))
    {
        std::cout << (value < 0.0 ? "-inf" : "+inf") << "\n";
        return;
    }
    std::cout << formatDoubleOrFloat(value, 'd') << "\n";
}

static void printPseudoStr(const std::string &str)
{
    std::cout << "char: impossible\n";
    std::cout << "int: impossible\n";
    if (str == "nan" || str == "nanf")
    {
        std::cout << "float: nanf\n";
        std::cout << "double: nan\n";
        return;
    }
    if (str == "+inf" || str == "inf" || str == "+inff" || str == "inff")
    {
        std::cout << "float: +inff\n";
        std::cout << "double: +inf\n";
        return;
    }
    std::cout << "float: -inff\n";
    std::cout << "double: -inf\n";
}


void ScalarConverter::convert(const std::string &str)
{
    possibleTypes type = detectType(str);

    if (type == TYPE_INVALID)
    {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: impossible\n";
        std::cout << "double: impossible\n";
    }

    if (type == TYPE_PSEUDO)
        printPseudoStr(str);

    double value = 0.0;
    if (type == TYPE_CHAR)
        value = static_cast<double>(str[0]);
    else if (type == TYPE_INT)
        value = std::strtod(str.c_str(), NULL);
    else if (type == TYPE_FLOAT)
    {
        std::string core = str.substr(0, str.size() - 1);
        value = std::strtod(core.c_str(), NULL);
    }
    else if (type == TYPE_DOUBLE)
        value = std::strtod(str.c_str(), NULL);

    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value);
}
