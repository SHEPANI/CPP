#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <iomanip>

class ScalarConverter
{
    public:
        static void convert(const std::string &str);

    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter &);
        ScalarConverter &operator=(const ScalarConverter &);
        ~ScalarConverter();
};

#endif