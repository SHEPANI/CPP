#include "ScalarConverter.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <float.h>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}

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

    if (value != value)
        return (currType == 'd' ? "nan" : "nanf");
    double inf = 1.0/0.0;
    if (value == inf || value == -inf)
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

    return (oss.str());
}

static void printChar(char c, bool impossible)
{
    std::cout << "char: ";
    if (impossible)
    {
        std::cout << "impossible\n";
        return;
    }
    if (c < 32 || c > 126)
        std::cout << "Non displayable\n";
    else
        std::cout << '\'' << c << '\'' << "\n";
}

static void printInt(int i, bool impossible)
{
    std::cout << "int: ";
    if (impossible)
    {
        std::cout << "impossible\n";
        return;
    }
    std::cout << i << "\n";
}

static void printFloat(float f, bool impossible)
{
    std::cout << "float: ";
    if (impossible)
    {
        std::cout << "impossible\n";
        return;
    }
    std::cout << formatDoubleOrFloat(static_cast<double>(f), 'f') << "\n";
}

static void printDouble(double d, bool impossible)
{
    std::cout << "double: ";
    if (impossible)
    {
        std::cout << "impossible\n";
        return;
    }
    std::cout << formatDoubleOrFloat(d, 'd') << "\n";
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
        std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n";
        return;
    }

    if (type == TYPE_PSEUDO)
    {
        printPseudoStr(str);
        return;
    }

    if (type == TYPE_CHAR)
    {
        char c = str[0];
        printChar(c, false);
        printInt(static_cast<int>(c), false);
        printFloat(static_cast<float>(c), false);
        printDouble(static_cast<double>(c), false);
    }
    else if (type == TYPE_INT)
    {
        std::stringstream ss(str);
        int i;
        if (!(ss >> i))
        {
            printChar(0, true);
            printInt(0, true);
            printFloat(0.0f, true);
            printDouble(0.0, true);
        }
        else
        {
            printChar(static_cast<char>(i), (i < 0 || i > 127));
            printInt(i, false);
            printFloat(static_cast<float>(i), false);
            printDouble(static_cast<double>(i), false);
        }

    }
    else if (type == TYPE_FLOAT)
    {
        std::string strWithoutF = str.substr(0, str.size() - 1);
        std::stringstream ss(strWithoutF);
        float f;
        if (!(ss >> f))
        {
            printChar(0, true);
            printInt(0, true);
            printFloat(0.0f, true);
            printDouble(0.0, true);
        }
        else
        {
            printChar(static_cast<char>(f), (f != f || f < 0.0f || f > 127.0f));
            bool intImp = (f != f || f < static_cast<float>(INT_MIN) || f > static_cast<float>(INT_MAX));
            printInt(static_cast<int>(f), intImp);
            printFloat(f, false);
            printDouble(static_cast<double>(f), false);
        }
    }
    else if (type == TYPE_DOUBLE)
    {
        std::stringstream ss(str);
        double d;        
        if (!(ss >> d))
        {
            printChar(0, true);
            printInt(0, true);
            printFloat(0.0f, true);
            printDouble(0.0, true);
        }
        else
        {
            printChar(static_cast<char>(d), (d != d || d < 0.0 || d > 127.0));
            bool intImp = (d != d || d < static_cast<double>(INT_MIN) || d > static_cast<double>(INT_MAX));
            printInt(static_cast<int>(d), intImp);
            bool floatImp = (d < -FLT_MAX || d > FLT_MAX);
            printFloat(static_cast<float>(d), floatImp);
            printDouble(d, false);
        }
    }
}