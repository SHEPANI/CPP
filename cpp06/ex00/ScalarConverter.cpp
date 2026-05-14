#include "ScalarConverter.hpp"

#include <cmath>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <cerrno>
#include <cctype>

enum eLiteralType
{
    TYPE_INVALID,
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_PSEUDO
};

static bool isPseudoLiteral(const std::string &literal)
{
    return (literal == "nan" || literal == "+inf" || literal == "-inf" || literal == "inf"
         || literal == "nanf" || literal == "+inff" || literal == "-inff" || literal == "inff");
}

static bool isCharLiteral(const std::string &literal)
{
    return literal.size() == 1 && !std::isdigit(literal[0]);
}

static bool isDecimalLiteral(const std::string &literal)
{
    std::string::size_type i = 0;
    bool hasDigit = false;
    bool hasDot = false;

    if (literal.empty())
        return false;
    if (literal[i] == '+' || literal[i] == '-')
        ++i;
    if (i == literal.size())
        return false;
    for (; i < literal.size(); ++i)
    {
        if (literal[i] == '.')
        {
            if (hasDot)
                return false;
            hasDot = true;
        }
        else if (std::isdigit(literal[i]))
            hasDigit = true;
        else
            return false;
    }
    return hasDigit && hasDot;
}

static bool isIntLiteral(const std::string &literal)
{
    std::string::size_type i = 0;

    if (literal.empty())
        return false;
    if (literal[i] == '+' || literal[i] == '-')
        ++i;
    if (i == literal.size())
        return false;
    for (; i < literal.size(); ++i)
    {
        if (!std::isdigit(literal[i]))
            return false;
    }
    return true;
}

static bool isFloatLiteral(const std::string &literal)
{
    if (literal.size() < 2 || literal[literal.size() - 1] != 'f')
        return false;
    std::string core = literal.substr(0, literal.size() - 1);
    return isDecimalLiteral(core) || isIntLiteral(core);
}

static bool isDoubleLiteral(const std::string &literal)
{
    return isDecimalLiteral(literal);
}

static eLiteralType detectType(const std::string &literal)
{
    if (isPseudoLiteral(literal))
        return TYPE_PSEUDO;
    if (isCharLiteral(literal))
        return TYPE_CHAR;
    if (isIntLiteral(literal))
        return TYPE_INT;
    if (isFloatLiteral(literal))
        return TYPE_FLOAT;
    if (isDoubleLiteral(literal))
        return TYPE_DOUBLE;
    return TYPE_INVALID;
}

// static std::string formatFloat(float value)
// {
//     std::ostringstream oss;

//     if (std::isnan(value))
//         return "nanf";
//     if (std::isinf(value))
//         return (value < 0.0f ? "-inff" : "+inff");
//     {
//         double integerPart;
//         if (std::modf(value, &integerPart) == 0.0)
//             oss << std::fixed << std::setprecision(1) << value << "f";
//         else
//             oss << value << "f";
//     }
//     return oss.str();
// }

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

static void printPseudoLiterals(const std::string &literal)
{
    std::cout << "char: impossible\n";
    std::cout << "int: impossible\n";
    if (literal == "nan" || literal == "nanf")
    {
        std::cout << "float: nanf\n";
        std::cout << "double: nan\n";
        return;
    }
    if (literal == "+inf" || literal == "inf" || literal == "+inff" || literal == "inff")
    {
        std::cout << "float: +inff\n";
        std::cout << "double: +inf\n";
        return;
    }
    std::cout << "float: -inff\n";
    std::cout << "double: -inf\n";
}


void ScalarConverter::convert(const std::string &literal)
{
    eLiteralType type = detectType(literal);
    if (type == TYPE_INVALID)
    {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: impossible\n";
        std::cout << "double: impossible\n";
        return;
    }
    if (type == TYPE_PSEUDO)
    {
        printPseudoLiterals(literal);
        return;
    }

    double value = 0.0;
    if (type == TYPE_CHAR)
        value = static_cast<double>(literal[0]);
    else if (type == TYPE_INT)
        value = std::strtod(literal.c_str(), NULL);
    else if (type == TYPE_FLOAT)
    {
        std::string core = literal.substr(0, literal.size() - 1);
        value = std::strtod(core.c_str(), NULL);
    }
    else if (type == TYPE_DOUBLE)
        value = std::strtod(literal.c_str(), NULL);

    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value);
}
